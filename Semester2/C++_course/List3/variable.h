#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using namespace std;

class Variable {
private:
    double val;
    const string name;
    static const int history_size = 3;
    double *history;
    int history_n;
    int val_idx;
    int start;
    void add_to_history(double new_val);

public:
    Variable(const string &name, double val);
    Variable();
    Variable(const Variable &other);
    Variable(Variable &&other);
    ~Variable();
    Variable &operator=(const Variable &other);
    Variable &operator=(Variable &&other);
    void undo();
    void redo();
    void change_sign();
    void reverse();
    void print_var(const string &label);
    void set_value(double val);
};

#endif