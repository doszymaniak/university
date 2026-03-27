#include "variable.h"
#include <iostream>

using namespace std;

int main()
{
    Variable var1("var1", 5);
    var1.print_var("CONSTRUCTOR WITH NAME AND VALUE:");

    Variable var2;
    var2.print_var("DEFAULT CONSTRUCTOR:");

    Variable var3(var1);
    var3.print_var("COPY CONSTRUCTOR:");

    var1.set_value(6);
    var1.print_var("AFTER SETTING VALUE TO 6:");

    var1.set_value(7);
    var1.print_var("AFTER SETTING VALUE TO 7:");

    var1.set_value(8);
    var1.print_var("AFTER SETTING VALUE TO 8 (the oldest value is discarded):");

    var1.undo();
    var1.print_var("AFTER FIRST UNDO:");

    var1.undo();
    var1.print_var("AFTER SECOND UNDO:");

    var1.undo();
    var1.print_var("AFTER THIRD UNDO (no change):");

    var1.redo();
    var1.print_var("AFTER FIRST REDO:");

    var1.redo();
    var1.print_var("AFTER SECOND REDO:");

    var1.redo();
    var1.print_var("AFTER THIRD REDO (no change):");

    var1.change_sign();
    var1.print_var("AFTER CHANGING SIGN:");

    var1.reverse();
    var1.print_var("AFTER REVERSING:");

    Variable var4(move(var1));
    var4.print_var("MOVE CONSTRUCTOR:");

    var2.set_value(10);
    var3 = var2;
    var3.print_var("COPY ASSIGNMENT:");

    var2 = move(var3);
    var2.print_var("MOVE ASSIGNMENT:");
    return 0;
}