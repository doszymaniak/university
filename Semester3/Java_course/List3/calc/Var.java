package calc;

import java.util.Objects;

/**
 * Class representing a variable with a name and a value
 */
public class Var {
    /**
     * The name of the variable, should consist of letters only and cannot be empty
     */
    public final String name;
    /**
     * The value of the variable, initialized to 0.0
     */
    private double value;

    /**
     * Checks if the provided name is not null, not empty and consists only of
     * letters
     */
    private boolean is_name_valid(String name) {
        if (name == null || name.isEmpty())
            return false;
        for (int i = 0; i < name.length(); i++) {
            char c = name.charAt(i);
            if (!Character.isLetter(c))
                return false;
        }
        return true;
    }

    /**
     * Creates a new variable with the given name and initializes its value to 0.0
     */
    public Var(String name) {
        this(name, 0.0);
    }

    /**
     * Creates a new variable with the given name and value
     */
    public Var(String name, double value) {
        if (!is_name_valid(name))
            throw new IllegalArgumentException("Invalid variable name: " + name);
        this.name = name;
        this.value = value;
    }

    /**
     * Returns the value of the variable
     */
    public final double getValue() {
        return value;
    }

    /**
     * Sets the value of the variable
     */
    public void setValue(double value) {
        this.value = value;
    }

    /**
     * Returns a string representation of the variable
     */
    public String toString() {
        return name + " = " + value;
    }

    /**
     * Checks if two variables are equal based on their names
     */
    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass())
            return false;
        Var var = (Var) o;
        return Objects.equals(name, var.name);
    }
};