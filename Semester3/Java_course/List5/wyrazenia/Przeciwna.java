package wyrazenia;

public class Przeciwna extends Wyrazenie {
    private final Wyrazenie w;

    public Przeciwna(Wyrazenie w) {
        this.w = w;
    }

    @Override
    public double oblicz() {
        return -w.oblicz();
    }

    @Override
    public String toString() {
        return "~" + nawiasy(w, false);
    }

    @Override
    protected int priorytet() {
        return 3;
    }
}