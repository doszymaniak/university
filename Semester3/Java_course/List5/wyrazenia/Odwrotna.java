package wyrazenia;

public class Odwrotna extends Wyrazenie {
    private final Wyrazenie w;

    public Odwrotna(Wyrazenie w) {
        this.w = w;
    }

    @Override
    public double oblicz() {
        if (w.oblicz() == 0)
            throw new IllegalArgumentException("Nie mozna dzielic przez zero!");
        return 1.0 / w.oblicz();
    }

    @Override
    public String toString() {
        return "!" + nawiasy(w, false);
    }

    @Override
    protected int priorytet() {
        return 3;
    }
}