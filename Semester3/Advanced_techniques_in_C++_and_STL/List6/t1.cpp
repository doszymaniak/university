#include <string>
#include <deque>
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

class Person {
public:
    string name;
    string surname;
    int age;
    int weight;
    double height;

    Person(const string &name, const string &surname, int age, int weight, double height) :
        name(name), surname(surname), age(age), weight(weight), height(height) {}

    double bmi() const
    {
        return weight / pow(height / 100, 2);
    }
};

void print_people(deque<Person> &people)
{
    int i = 1;
    for (auto &person : people)
    {
        cout << "PERSON " << i << "\n";
        cout << "name: " << person.name << '\n';
        cout << "surname: " << person.surname << '\n';
        cout << "age: " << person.age << '\n';
        cout << "weight: " << person.weight << '\n';
        cout << "height: " << person.height << '\n';
        cout << "bmi: " << person.bmi() << '\n';
        cout << "\n";
        i++;
    }
}

void sort_by_bmi(deque<Person> &people)
{
    cout << "---- SORTED BY BMI ----\n";
    sort(people.begin(), people.end(), [](Person &a, Person &b){
        return a.bmi() < b.bmi();
    });
    print_people(people);
}

void losing_weight(deque<Person> &people)
{
    cout << "---- EACH PERSON LOSES 10\% OF THEIR BODY WEIGHT ----\n";
    for_each(people.begin(), people.end(), [](Person &person){
        person.weight -= person.weight * 0.1;
    });
    print_people(people);
}

void partition(deque<Person> &people)
{
    cout << "---- PARTITIONING BY WEIGHT ----\n";
    deque<Person> lowest, highest;
    for_each(people.begin(), people.end(), [&lowest, &highest](Person &person){
        if (person.weight <= 100)
            lowest.push_front(person);
        else highest.push_front(person);
    });
    cout << "<= 100 KILOGRAMS:\n";
    print_people(lowest);
    cout << "> 100 KILOGRAMS:\n";
    print_people(highest);
}

void youngest_oldest(deque<Person> &people)
{
    cout << "---- YOUNGEST AND OLDEST PERSON ----\n";
    Person *youngest = &people.front();
    Person *oldest = &people.front();
    for_each(people.begin() + 1, people.end(), [&youngest, &oldest](Person &person){
        if (person.age > oldest->age)
            oldest = &person;
        if (person.age < youngest->age)
            youngest = &person;
    });
    deque<Person> d1, d2;
    d1.push_front(*youngest);
    d2.push_front(*oldest);
    cout << "YOUNGEST:\n";
    print_people(d1);
    cout << "OLDEST:\n";
    print_people(d2);
}

int main()
{
    deque<Person> people;

    Person person1 = Person("Marcin", "Kowalski", 45, 70, 172.5);
    Person person2 = Person("Anna", "Nowak", 30, 55, 162);
    Person person3 = Person("Grzegorz", "Wroblewski", 58, 75, 180.5);
    Person person4 = Person("Piotr", "Wisniewski", 25, 82, 185.0);
    Person person5 = Person("Katarzyna", "Kaminska", 35, 60, 168.0);
    Person person6 = Person("Tomasz", "Lewandowski", 42, 114, 178.5);
    Person person7 = Person("Marta", "Zielinska", 22, 52, 165.0);
    Person person8 = Person("Pawel", "Szymanski", 50, 105, 175.0);
    Person person9 = Person("Agnieszka", "Dabrowska", 28, 58, 170.0);
    Person person10 = Person("Michal", "Wozniak", 33, 101, 182.0);
    Person person11 = Person("Julia", "Kozlowska", 19, 50, 160.5);
    Person person12 = Person("Jakub", "Jankowski", 39, 120, 190.0);

    people.push_front(person1);
    people.push_front(person2);
    people.push_front(person3);
    people.push_front(person4);
    people.push_front(person5);
    people.push_front(person6);
    people.push_front(person7);
    people.push_front(person8);
    people.push_front(person9);
    people.push_front(person10);
    people.push_front(person11);
    people.push_front(person12);

    sort_by_bmi(people);

    losing_weight(people);

    partition(people);

    youngest_oldest(people);
    return 0;
}