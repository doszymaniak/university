import asyncio
import aiohttp
from private import KEY

# Calling this function does not immediately produce a result
# Only using 'await' guarantees that the function runs and returns the result
async def get_public(session):
    url = "https://bored-api.appbrewery.com/random"
    async with session.get(url) as response:
        try:
            data = await response.json()
        except aiohttp.ContentTypeError:
            print("The API returned HTML instead of JSON")
            return None
        return [data["activity"], data["type"], data["participants"]]

async def get_private(session):
    url = "https://calendarific.com/api/v2/holidays"
    params = {
        "api_key": KEY,
        "country": "PL",
        "year": 2025
    }
    async with session.get(url, params=params) as response:
        try:
            data = await response.json()
        except aiohttp.ContentTypeError:
            print("The API returned HTML instead of JSON")
            return None
        data = data["response"]["holidays"]
        return [[h["name"], h["description"], h["date"]["iso"]] for h in data[:3]]
    
async def main():
    # Creates an HTTP session and automatically closes it
    async with aiohttp.ClientSession() as session:
        holidays = get_private(session)
        activity = get_public(session)
        # Runs both tasks concurrently and waits for them to finish
        holidays, activity = await asyncio.gather(holidays, activity)
        print("DATA FETCHED FROM A PRIVATE API:")
        if holidays is None:
            print("No data available")
        else:
            for name, description, date in holidays:
                print(f"Holiday: {name}")
                print(f"Date: {date}")
                print(f"Description: {description}")
                print()
            print()

        print("DATA FETCHED FROM A PUBLIC API:")
        if activity is None:
            print("No data available")
        else:
            name, activity_type, participants = activity
            print(f"Activity name: {name}")
            print(f"Activity type: {activity_type}")
            print(f"Number of participants: {participants}")

if __name__ == "__main__":
    asyncio.run(main())