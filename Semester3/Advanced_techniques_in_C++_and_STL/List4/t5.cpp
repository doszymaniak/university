#include <iostream>
#include <vector>
#include <functional> 
#include <stdexcept>   
#include <utility>    

using namespace std;

int main()
{
    vector<pair<int, int>> n_k = {{6, 3}, {4, 3}, {4, 2}, {5, 4}, {-8, 4}};

    function<long long(int, int)> C;
    C = [&C](int n, int k) -> long long {
        if (n < 0 || k < 0)
            throw invalid_argument("n and k must be greater than or equal to zero!");
        if (k > n)
            return 0;
        if (k == 0 || k == n)
            return 1;
        return C(n - 1, k - 1) + C(n - 1, k);
    };

    for (const auto& [n, k] : n_k) 
    {
        try 
        {
            auto res = C(n, k);
            cout << "C(" << n << ", " << k << ") = " << res << '\n';
        }
        catch (const invalid_argument& e) 
        {
            cout << "Error for (" << n << ", " << k << "): " << e.what() << '\n';
        }
    }
    return 0;
}