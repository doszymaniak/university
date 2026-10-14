#include <iostream>

using namespace std;

int main()
{
    string address = R"(Instytut Informatyki Uniwersytetu Wrocławskiego
Fryderyka Joliot-Curie 15
50-300 Wrocław)";
    string filepath = R"(C:\Users\Public\Documents)";
    string seq1 = R"("))";
    string seq2 = R"(((((""""("))))";
    string seq3 = R"((((""")))())";
    cout << address << "\n\n";
    cout << filepath << "\n\n";
    cout << seq1 << "\n\n";
    cout << seq2 << "\n\n";
    cout << seq3 << '\n';
}