#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <ostream>

using namespace std;

class Person {
private:
    string name;
    string surname;
    int year;

public:
    Person(string name, string surname, int year) : name(name), surname(surname), year(year) {};

    friend bool operator<(const Person &p1, const Person &p2)
    {
        return tie(p1.surname, p1.name, p1.year) < tie(p2.surname, p2.name, p2.year);
    }

    friend ostream &operator<<(ostream &out, const Person &p)
    {
        out << p.name << " " << p.surname << " " << p.year << '\n';
        return out;
    }
};

int main()
{
    vector<Person> people = {
        Person("Jan", "Kowalski", 1990),
        Person("Anna", "Nowak", 1985),
        Person("Adam", "Kowalski", 2006),
        Person("Jan", "Kowalski", 1985),
        Person("Piotr", "Adamski", 1995)
    };

    sort(people.begin(), people.end());

    for (auto &p : people)
        cout << p;
    return 0;
}