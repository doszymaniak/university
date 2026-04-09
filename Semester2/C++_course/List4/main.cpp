#include "tabbit.hpp"
#include <iostream>

int main()
{
    cout << "-- CONSTRUCTORS --" << '\n';
    Tabbit tab1(5);
    tab1.print_tabbit("tab1 - initialized with given length: ");
    uint64_t pattern = 0b1101101100;
    Tabbit tab2(pattern);
    tab2.print_tabbit("tab2 - initialized with given pattern: ");
    pattern = 0b1011110000;
    Tabbit tab3(pattern);
    tab3.print_tabbit("tab3 - initialized with given pattern: ");
    Tabbit tab4(tab3);
    tab4.print_tabbit("tab4 - copy constructed from tab3: ");
    Tabbit tab5(move(tab3));
    tab5.print_tabbit("tab5 - move constructed from tab3: ");
    tab3.print_tabbit("tab3 after move operation (should be empty): ");

    cout << "\n-- COPY ASSIGNMENT --" << '\n';
    tab1 = tab5;
    tab1.print_tabbit("tab1 after copy assignment from tab5: ");

    cout << "\n-- MOVE ASSIGNMENT --" << '\n';
    tab3 = move(tab1);
    tab3.print_tabbit("tab3 after move assignment from tab1: ");

    cout << "\n-- INDEXING --" << '\n';
    tab3[0] = 1;
    tab3.print_tabbit("tab3 after changing bit number 0 to 1: ");
    cout << "Bit number 2 in tab3: " << tab3[2] << "\n\n";

    tab3[2] = tab2[2];
    tab3.print_tabbit("tab3 after changing bit number 2 to tab2[2] (1): ");

    cout << "\n-- BITWISE OPERATORS --" << '\n';
    tab3.print_tabbit("tab3 before operations: ");
    tab2.print_tabbit("tab2 before operations: ");

    Tabbit or_tab = tab3 | tab2;
    or_tab.print_tabbit("tab3 | tab2: ");

    Tabbit and_tab = tab3 & tab2;
    and_tab.print_tabbit("tab3 & tab2: ");

    Tabbit xor_tab = tab3 ^ tab2;
    xor_tab.print_tabbit("tab3 ^ tab2: ");

    Tabbit neg_tab3 = !tab3;
    neg_tab3.print_tabbit("!tab3: ");
    return 0;
}