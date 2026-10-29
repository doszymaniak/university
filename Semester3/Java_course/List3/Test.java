import calc.*;

public class Test {
    public static void main(String[] args) {
        System.out.println("VAR TEST");
        Var v1 = new Var("x");
        Var v2 = new Var("y", 10.0);
        System.out.println("Var with default value: " + v1);
        System.out.println("Var with specified value: " + v2);
        v1.setValue(5.0);
        System.out.println("Updated value of v1: " + v1.getValue());
        System.out.println("Value of v2: " + v2.getValue());
        System.out.println("Are v1 and v2 equal? " + v1.equals(v2));

        System.out.println("\nVARIABLES TEST");
        Variables vars = new Variables(5);
        vars.insert(v1);
        vars.insert(v2);
        System.out.println("Variables collection: " + vars);
        System.out.println("Does the collection contain v1? " + vars.contains(v1));
        vars.delete(v1);
        System.out.println("Variables collection after deleting v1: " + vars);
        vars.clear();
        System.out.println("Variables collection after clearing: " + vars);
    }
}