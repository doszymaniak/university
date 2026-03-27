#include "variable.h"
#include <stdexcept>
#include <iostream>

using namespace std;

Variable::Variable(const string &name, double new_val) : val(new_val), name(name),
history_n(1), val_idx(0), start(0)
{
    history = new double[history_size];
    history[0] = val;
}

Variable::Variable() : Variable("x", 0)
{}

Variable::Variable(const Variable &other) : Variable(other.name, other.val)
{};

Variable::Variable(Variable &&other) : val(other.val), name(other.name),
history(other.history), history_n(other.history_n), val_idx(other.val_idx), start(other.start)
{
    other.history = nullptr;
    other.history_n = 0;
    other.start = 0;
}

Variable::~Variable()
{
    delete[] history;
    history = nullptr;
    history_n = 0;
    val_idx = 0;
    start = 0;
}

Variable &Variable::operator=(const Variable &other)
{
    if (this == &other) return *this;
    val = other.val;
    add_to_history(val);
    return *this;
}

Variable &Variable::operator=(Variable &&other)
{
    if (this == &other) return *this;
    delete[] history;
    history = other.history;
    history_n = other.history_n;
    start = other.start;
    
    val = other.val;
    add_to_history(val);

    other.history = nullptr;
    other.history_n = 0;
    other.start = 0;
    
    return *this;
}

void Variable::add_to_history(double new_val)
{
    int new_idx = (start + 1) % history_size;
    history[new_idx] = new_val;
    if (history_n < history_size) history_n++;
    start = new_idx;
    val_idx = start;
}

void Variable::undo()
{
    if (history_n <= 1) return;
    if (val_idx == (start - history_n + 1 + history_size) % history_size) return;
    val_idx = (val_idx - 1 + history_size) % history_size;
    val = history[val_idx];
}

void Variable::redo()
{
    if (val_idx == start) return;
    val_idx = (val_idx + 1) % history_size;
    val = history[val_idx];
}

void Variable::change_sign()
{
    val = -val;
    add_to_history(val);
}

void Variable::reverse()
{
    if (val == 0.0) throw invalid_argument("Could not reverse 0!");
    val = 1.0 / val;
    add_to_history(val);
}

void Variable::print_var(const string &label)
{
    cout << label << '\n';
    cout << "Name: " << name << '\n';
    cout << "Current value: " << val << '\n';
    cout << "History (most recent first):\n";
    for (int i = 0; i < history_n; i++)
    {
        int idx = ((start - i) + history_size) % history_size;
        cout << history[idx];
        if (idx == val_idx) cout << "  <--- current";
        cout << '\n';
    }
    cout << "\n\n";
}

void Variable::set_value(double new_val)
{
    val = new_val;
    add_to_history(val);
}