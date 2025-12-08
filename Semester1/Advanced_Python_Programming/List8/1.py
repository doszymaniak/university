import private
import asyncio
import aiohttp
import matplotlib.pyplot as plt

async def get_nbp_api_helper(session, url):
    async with session.get(url) as response:
        data = await response.json()
        days = [(item["effectiveDate"], item["mid"]) for item in data["rates"]]
        month_sum = {}
        month_cnt = {}
        for date, mid in days:
            curr_year, curr_month, _ = date.split("-")
            key = (int(curr_year), int(curr_month))
            month_sum[key] = month_sum.get(key, 0) + mid
            month_cnt[key] = month_cnt.get(key, 0) + 1
        month_average = {key: month_sum[key] / month_cnt[key] for key in month_sum}
        return month_average

async def get_nbp_api(session):
    url1 = "https://api.nbp.pl/api/exchangerates/rates/A/USD/2023-01-01/2023-12-31"
    url2 = "https://api.nbp.pl/api/exchangerates/rates/A/USD/2024-01-01/2024-12-31"
    fst_dict = get_nbp_api_helper(session, url1)
    snd_dict = get_nbp_api_helper(session, url2)
    fst_dict, snd_dict = await asyncio.gather(fst_dict, snd_dict)
    return fst_dict | snd_dict
    
async def get_massive_api(session):
    url = "https://api.massive.com/fed/v1/inflation"
    params = {
        "apiKey": private.KEY,
        "date.gte": "2023-01-01",
        "date.lte": "2024-12-31"
    }
    async with session.get(url, params=params) as response:
        data = await response.json()
        days = [(item["date"], item["cpi_year_over_year"]) for item in data["results"]]
        dict = {}
        for date, res in days:
            curr_year, curr_month, _ = date.split("-")
            key = (int(curr_year), int(curr_month))
            dict[key] = dict.get(key, 0) + res
        return dict
    
def draw_two_series(ax, months, first, second):
    ax.plot(months, first, marker="o", label="USD exchange rate")
    ax.plot(months, second, marker="s", label="CPI in the USA (%)")
    ax.set_xlabel("Month")
    ax.set_ylabel("Value")
    ax.set_xticks(months)
    ax.yaxis.set_major_locator(plt.MaxNLocator(20))
    ax.legend()

def print_year_chart_on_ax(ax, exchange_rates, inflation, year):
    months = []
    usd_vals = []
    inflation_vals = []
    for (curr_year, curr_month) in exchange_rates.keys():
        rate_curr_val = exchange_rates[(curr_year, curr_month)]
        if curr_year == year:
            months.append(curr_month)
            usd_vals.append(rate_curr_val)
            inflation_vals.append(inflation.get((curr_year, curr_month), None))
    ax.set_title(f"Monthly data - {year}")
    draw_two_series(ax, months, usd_vals, inflation_vals)

def make_forecast(data):
    forecast = []
    for month in range(1, 13):
        val = 0
        if (2023, month) in data:
            val += data[(2023, month)]
        if (2024, month) in data:
            val += data[(2024, month)]
        val /= 2
        forecast.append(val)
    return forecast

def print_forecast_chart(ax, rates, inflation):
    months = [i for i in range(1, 13)]
    draw_two_series(ax, months, rates, inflation)
    ax.set_title(f"2025 forecast")

async def main():
    exchange_rates = {}
    inflation = {}
    async with aiohttp.ClientSession() as session:
        exchange_rates = get_nbp_api(session)
        inflation = get_massive_api(session)
        exchange_rates, inflation = await asyncio.gather(exchange_rates, inflation)

    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 10))
    print_year_chart_on_ax(ax1, exchange_rates, inflation, 2023)
    print_year_chart_on_ax(ax2, exchange_rates, inflation, 2024)

    rates_forecast = make_forecast(exchange_rates)
    inflation_forecast = make_forecast(inflation)
    print_forecast_chart(ax3, rates_forecast, inflation_forecast)

    plt.tight_layout(pad=3.0)
    plt.show()

if __name__ == "__main__":
    asyncio.run(main())