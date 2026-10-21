#include <iostream>
#include <memory>
#include <vector>
#include <set>

using namespace std;

enum Gender {
    Male,
    Female,
    Unknown
};

class llama {
private:
    const string name;
    Gender gender;
    shared_ptr<llama> mother;
    shared_ptr<llama> father;
    vector<weak_ptr<llama>> children;
public:
    static shared_ptr<llama> noname;
    llama(const string &name, Gender gender, shared_ptr<llama> mother, shared_ptr<llama> father) :
        name(name), gender(gender), mother(mother ? mother : noname), father(father ? father : noname)
    {
        cout << name << " is created!\n";
    }

    ~llama()
    {
        cout << name << " is deleted!\n";
    }

    void add_child(shared_ptr<llama> child)
    {
        if (child)
            children.push_back(child);
    }

    const string& get_name() const { return name; }
};

struct Comparator
{
    bool operator()(const shared_ptr<llama> &llama1, const shared_ptr<llama> &llama2) const
    {
        return llama1->get_name() < llama2->get_name();
    }
};

class herd {
private:
    set<shared_ptr<llama>, Comparator> llamas;
public:
    bool name_exists(const string &name)
    {
        for (auto &llama : llamas)
        {
            if (llama->get_name() == name) 
                return true;
        }
        return false;
    }

    bool add_llama(const shared_ptr<llama> &llama)
    {
        const string &name = llama->get_name();
        if (name_exists(name))
        {
            cout << "Llama with the name " << name << " already exists in the herd!\n";
            return false;
        }
        llamas.insert(llama);
        return true;
    }

    void buy_llama(const string &name, Gender gender)
    {
        auto new_llama = make_shared<llama>(name, gender, llama::noname, llama::noname);
        if (add_llama(new_llama))
            cout << "New llama bought!\n";
    }

    shared_ptr<llama> birth(const shared_ptr<llama> &mother, const shared_ptr<llama> &father, const string &name, Gender gender)
    {
        if (name_exists(name))
        {
            cout << "Llama with this name already exists!\n";
            return nullptr;
        }
        if (!mother || mother == llama::noname || !(name_exists(mother->get_name())))
        {
            cout << "Mother must belong to the herd!\n";
            return nullptr;
        }
        if (father && father != llama::noname && !name_exists(father->get_name()))
        {
            cout << "Father must belong to the herd!\n";
            return nullptr;
        }
        auto child = make_shared<llama>(name, gender, mother, father);
        if (!add_llama(child))
        {
            cout << "Could not add the newly born llama!\n";
            return nullptr;
        }
        mother->add_child(child);
        if (father && father != llama::noname)
            father->add_child(child);
        return child;
    }

    void sell_llama(const shared_ptr<llama> &llama)
    {
        if (!llama || llama == llama::noname)
            return;
        const string &name = llama->get_name();
        for (auto it = llamas.begin(); it != llamas.end(); it++)
        {
            if ((*it)->get_name() == name)
            {
                llamas.erase(it);
                cout << "Llama with the name " << name << " sold!\n";
                return;
            }
        }
        return;
    }

    shared_ptr<llama> get_llama(const string &name)
    {
        for (auto it = llamas.begin(); it != llamas.end(); it++)
        {
            if ((*it)->get_name() == name)
                return *it;
        }
        return nullptr;
    }
};

shared_ptr<llama> llama::noname = make_shared<llama>("unknown", Gender::Unknown, nullptr, nullptr);

int main()
{
    herd h;
    h.buy_llama("Llama1", Female);
    h.buy_llama("Llama2", Male);

    auto mother = h.get_llama("Llama1");
    auto father = h.get_llama("Llama2");

    auto child = h.birth(mother, father, "Llama3", Female);

    weak_ptr<llama> weak_child = child;

    h.sell_llama(child);

    cout << "Before deleting llama3: " << weak_child.expired() << '\n';
    cout << "Deleting llama3: ";
    child.reset();
    cout << "After reset: " << weak_child.expired() << '\n';
    return 0;
}