#include <iostream>
#include <cstdint>

using namespace std;

enum class Name : uint16_t {
    Ania,
    Maciej,
    Kasia,
    Maja,
    Tomek,
    Marcin,
    Jakub
};

void print_message(string message, Name name)
{
    switch(name)
    {
        case Name::Ania:
            cout << "Ania, " << message << '\n';
            break;
        case Name::Maciej:
            cout << "Maciej, " << message << '\n';
            break;
        case Name::Kasia:
            cout << "Kasia, " << message << '\n';
            break;
        case Name::Maja:
            cout << "Maja, " << message << '\n';
            break;
        case Name::Tomek:
            cout << "Tomek, " << message << '\n';
            break;
        case Name::Marcin:
            cout << "Marcin, " << message << '\n';
            break;
        case Name::Jakub:
            cout << "Jakub, " << message << '\n';
            break;
    }
}

int main()
{
    print_message("how are you?", Name::Jakub);
    print_message("good luck!", Name::Maja);
    return 0;
}