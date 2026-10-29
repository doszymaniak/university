package calc;

/**
 * Class representing a collection of variables with a fixed capacity
 */
public class Variables {
    /**
     * The array to store the variables
     */
    private final Var[] arr;
    /**
     * The current number of variables in the collection
     */
    private int size;

    /**
     * Creates a new Variables collection with the specified capacity
     */
    public Variables(int capacity) {
        if (capacity <= 0)
            throw new IllegalArgumentException("Capacity must be positive");
        arr = new Var[capacity];
        size = 0;
    }

    /**
     * Checks if the variable can be inserted into the collection
     */
    private boolean can_insert(Var v) {
        for (int i = 0; i < size; i++)
            if (arr[i].equals(v))
                return false;
        return true;
    }

    /**
     * Inserts a new variable into the collection if there is space and it doesn't
     * already exist
     */
    public void insert(Var v) {
        if (size >= arr.length)
            throw new IllegalStateException("Variables array is full");
        if (!can_insert(v))
            throw new IllegalArgumentException("Variable already exists");
        arr[size++] = v;
    }

    /**
     * Checks if the collection contains the specified variable
     */
    public boolean contains(Var v) {
        for (int i = 0; i < size; i++)
            if (arr[i].equals(v))
                return true;
        return false;
    }

    /**
     * Removes the specified variable from the collection
     */
    public void delete(Var v) {
        for (int i = 0; i < size; i++) {
            if (arr[i].equals(v)) {
                arr[i] = arr[size - 1];
                arr[size - 1] = null;
                size--;
                break;
            }
        }
    }

    /**
     * Clears the collection by setting all elements to null and resetting the size
     * to 0
     */
    public void clear() {
        for (int i = 0; i < size; i++)
            arr[i] = null;
        size = 0;
    }

    /**
     * Returns a string representation of the collection
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size; i++) {
            sb.append(arr[i].toString());
            if (i < size - 1)
                sb.append(", ");
        }
        return sb.toString();
    }
}
