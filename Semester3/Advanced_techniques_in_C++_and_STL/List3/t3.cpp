#include <iostream>
#include <ratio>

using namespace std;

template<typename R>
void print_ratio()
{
    cout << R::num << " / " << R::den << '\n';
}

int main()
{
    using h1 = ratio<1, 1>;
    using h2 = ratio_add<h1, ratio<1, 2>>;
    using h3 = ratio_add<h2, ratio<1, 3>>;
    using h4 = ratio_add<h3, ratio<1, 4>>;
    using h5 = ratio_add<h4, ratio<1, 5>>;
    using h6 = ratio_add<h5, ratio<1, 6>>;
    using h7 = ratio_add<h6, ratio<1, 7>>;
    using h8 = ratio_add<h7, ratio<1, 8>>;
    using h9 = ratio_add<h8, ratio<1, 9>>;
    using h10 = ratio_add<h9, ratio<1, 10>>;
    using h11 = ratio_add<h10, ratio<1, 11>>;
    using h12 = ratio_add<h11, ratio<1, 12>>;
    using h13 = ratio_add<h12, ratio<1, 13>>;
    using h14 = ratio_add<h13, ratio<1, 14>>;
    using h15 = ratio_add<h14, ratio<1, 15>>;
    using h16 = ratio_add<h15, ratio<1, 16>>;
    using h17 = ratio_add<h16, ratio<1, 17>>;
    using h18 = ratio_add<h17, ratio<1, 18>>;
    using h19 = ratio_add<h18, ratio<1, 19>>;
    using h20 = ratio_add<h19, ratio<1, 20>>;
    using h21 = ratio_add<h20, ratio<1, 21>>;
    using h22 = ratio_add<h21, ratio<1, 22>>;
    using h23 = ratio_add<h22, ratio<1, 23>>;
    using h24 = ratio_add<h23, ratio<1, 24>>;
    using h25 = ratio_add<h24, ratio<1, 25>>;
    using h26 = ratio_add<h25, ratio<1, 26>>;
    using h27 = ratio_add<h26, ratio<1, 27>>;
    using h28 = ratio_add<h27, ratio<1, 28>>;
    using h29 = ratio_add<h28, ratio<1, 29>>;
    using h30 = ratio_add<h29, ratio<1, 30>>;
    using h31 = ratio_add<h30, ratio<1, 31>>;
    using h32 = ratio_add<h31, ratio<1, 32>>;
    using h33 = ratio_add<h32, ratio<1, 33>>;
    using h34 = ratio_add<h33, ratio<1, 34>>;
    using h35 = ratio_add<h34, ratio<1, 35>>;
    using h36 = ratio_add<h35, ratio<1, 36>>;
    using h37 = ratio_add<h36, ratio<1, 37>>;
    using h38 = ratio_add<h37, ratio<1, 38>>;
    using h39 = ratio_add<h38, ratio<1, 39>>;
    using h40 = ratio_add<h39, ratio<1, 40>>;
    using h41 = ratio_add<h40, ratio<1, 41>>;
    using h42 = ratio_add<h41, ratio<1, 42>>;
    using h43 = ratio_add<h42, ratio<1, 43>>;
    using h44 = ratio_add<h43, ratio<1, 44>>;
    using h45 = ratio_add<h44, ratio<1, 45>>;
    using h46 = ratio_add<h45, ratio<1, 46>>;
    

    print_ratio<h1>();
    print_ratio<h2>();
    print_ratio<h3>();
    print_ratio<h4>();
    print_ratio<h5>();
    print_ratio<h6>();
    print_ratio<h7>();
    print_ratio<h8>();
    print_ratio<h9>();
    print_ratio<h10>();
    print_ratio<h11>();
    print_ratio<h12>();
    print_ratio<h13>();
    print_ratio<h14>();
    print_ratio<h15>();
    print_ratio<h16>();
    print_ratio<h17>();
    print_ratio<h18>();
    print_ratio<h19>();
    print_ratio<h20>();
    print_ratio<h21>();
    print_ratio<h22>();
    print_ratio<h23>();
    print_ratio<h24>();
    print_ratio<h25>();
    print_ratio<h26>();
    print_ratio<h27>();
    print_ratio<h28>();
    print_ratio<h29>();
    print_ratio<h30>();
    print_ratio<h31>();
    print_ratio<h32>();
    print_ratio<h33>();
    print_ratio<h34>();
    print_ratio<h35>();
    print_ratio<h36>();
    print_ratio<h37>();
    print_ratio<h38>();
    print_ratio<h39>();
    print_ratio<h40>();
    print_ratio<h41>();
    print_ratio<h42>();
    print_ratio<h43>();
    print_ratio<h44>();
    print_ratio<h45>();
    print_ratio<h46>();
    return 0;
}