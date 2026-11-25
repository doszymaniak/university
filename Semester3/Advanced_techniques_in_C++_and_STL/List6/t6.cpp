#include <iostream>

using namespace std;

class Person {
public:
    string name, surname;
    int age, weight;
    double height;

    Person(string name, string surname, int age, int weight, double height) : name(name),
        surname(surname), age(age), weight(weight), height(height) {};
};

tuple<string, int, double> fun1(Person &person)
{
    string initials = "";
    initials += person.name[0];
    initials += person.surname[0];
    double bmi = person.weight / (person.height * person.height);
    return make_tuple(initials, person.age, bmi);
}

tuple<int, int, double> fun2(Person &person)
{
    return make_tuple(person.age, person.weight, person.height);
}

tuple<string, string, int> fun3(Person &person)
{
    return make_tuple(person.name, person.surname, person.age);
}

int main()
{
    Person p("Jan", "Kowalski", 25, 80, 1.80);

    auto [initials, age, bmi] = fun1(p);

    cout << "FIRST FUNCTION\n";
    cout << "Initials: " << initials << '\n';
    cout << "Age: " << age << '\n';
    cout << "BMI: " << bmi << '\n';

    cout << "\nSECOND FUNCTION\n";
    auto tup1 = fun2(p);
    cout << get<0>(tup1) << '\n';
    cout << get<1>(tup1) << '\n';
    cout << get<2>(tup1) << '\n';

    cout << "\nTHIRD FUNCTION\n";
    auto tup2 = fun3(p);
    cout << get<0>(tup2) << '\n';
    cout << get<1>(tup2) << '\n';
    cout << get<2>(tup2) << '\n';
    return 0;
}