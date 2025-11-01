from abc import ABC, abstractmethod
from itertools import product

class Formula(ABC):
    @abstractmethod
    def calculate(self, var_values):
        pass

    @abstractmethod
    def __str__(self):
        pass

    def __add__(self, other):
        return Or(self, other)
    
    def __mul__(self, other):
        return And(self, other)
    
    def var_values(self):
        return set()
    
    def is_tautology(self):
        variables = list(self.var_values())
        # Przechodzimy po iloczynach kartezjanskich i generujemy wszystkie mozliwe wartosciowania
        for values in product([True, False], repeat=len(variables)):
            assignment = dict(zip(variables, values))
            if not self.calculate(assignment):
                return False
        return True
    
    @abstractmethod
    def simplify(self):
        pass
   
class Cons(Formula):
    def __init__(self, bool_val):
        self.bool_val = bool_val
    
    def calculate(self, var_values):
        return self.bool_val
    
    def __str__(self):
        return f"{self.bool_val}"
    
    def var_values(self):
        return set()
    
    def simplify(self):
        return self
    
class Variable(Formula):
    def __init__(self, var):
        self.var = var 
    
    def calculate(self, var_values):
        # Szukamy zmiennej w slowniku i zwracamy jej wartosc
        if self.var in var_values:
            return var_values[self.var]
        raise KeyError(f"Zmiennej {self.var} nie znaleziono w slowniku!")
    
    def __str__(self):
        return f"{self.var}"
    
    def var_values(self):
        return {self.var}
    
    def simplify(self):
        return self
    
class Or(Formula):
    def __init__(self, left, right):
        self.left = left
        self.right = right
    
    def calculate(self, var_values):
        return self.left.calculate(var_values) or self.right.calculate(var_values)
    
    def __str__(self):
        return "(" + str(self.left) + " v " + str(self.right) + ")"
    
    def var_values(self): 
        # Laczymy zmienne lewej formuly ze zmiennymi prawej formuly
        return (self.left.var_values()).union(self.right.var_values())

    def simplify(self):
        # Upraszczamy wg zasad:
        # p v false = p
        # p v true = true
        left = self.left.simplify()
        right = self.right.simplify()
        if isinstance(left, Cons):
            if left.bool_val == False:
                return right
            if left.bool_val == True:
                return Cons(True)
        if isinstance(right, Cons):
            if right.bool_val == False:
                return left
            if right.bool_val == True:
                return Cons(True)
        return Or(left, right)

class And(Formula):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def calculate(self, var_values):
        return self.left.calculate(var_values) and self.right.calculate(var_values)

    def __str__(self):
        return "(" + str(self.left) + " ∧ " + str(self.right) + ")"
    
    def var_values(self):
        return (self.left.var_values()).union(self.right.var_values())
    
    def simplify(self):
        # Upraszczamy wg zasady: p ∧ false = false
        left = self.left.simplify()
        right = self.right.simplify()
        if isinstance(left, Cons):
            if left.bool_val == False:
                return Cons(False)
            return right
        if isinstance(right, Cons):
            if right.bool_val == False:
                return Cons(False)
            else:
                return left
        return And(left, right)
    
class Not(Formula):
    def __init__(self, formula):
        self.formula = formula 

    def calculate(self, var_values):
        return not (self.formula.calculate(var_values))
    
    def __str__(self):
        return "¬" + str(self.formula)
    
    def var_values(self):
        return self.formula.var_values()
    
    # Upraszczamy wg zasad:
    # ¬(¬p) = p
    # ¬False = True
    def simplify(self):
        if isinstance(self.formula, Not):
            return self.formula.formula
        elif isinstance(self.formula, Cons):
            if self.formula.bool_val == True:
                return Cons(False)
            else:
                return Cons(True)
        return self

    
f1 = Or(Variable("p"), Not(Variable("p")))
print(f"FORMULA 1: {f1}")

f2 = Or(Not(And(Variable("p"), Variable ("q"))), And(Not(Variable ("p")), Not(Variable ("q"))))
print(f"FORMULA 2: {f2}")

f3 = Or(Not(Variable ("x")), Or(Variable("y"), Cons(True)))
print(f"FORMULA 3: {f3}\n")
print(f"CZY FORMULA 3 JEST TAUTOLOGIA: {f3.is_tautology()}\n")

f4 = (And(Variable("p"), Cons(False)))
print(f"FORMULA DO UPROSZCZENIA: {f4}")
print(f"UPROSZCZONA: {f4.simplify()}\n")

f5 = (Or(Cons(False), Variable("p")))
print(f"FORMULA DO UPROSZCZENIA: {f5}")
print(f"UPROSZCZONA: {f5.simplify()}\n")

f6 = Not(Cons(False))
print(f"FORMULA DO UPROSZCZENIA: {f6}")
print(f"UPROSZCZONA: {f6.simplify()}\n")

f7 = And(Variable ("q"), And(Variable ("p"), Cons(True)))
print(f"FORMULA DO UPROSZCZENIA: {f7}")
print(f"UPROSZCZONA: {f7.simplify()}\n")

f8 = Not(Not(Variable ("p")))
print(f"FORMULA DO UPROSZCZENIA: {f8}")
print(f"UPROSZCZONA: {f8.simplify()}")