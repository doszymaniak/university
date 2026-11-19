package wyrazenia;

public class Cos extends Wyrazenie {
    private final Wyrazenie w;

    public Cos(Wyrazenie w) {
        this.w = w;
    }

    @Override
    public double oblicz() {
        return Math.cos(w.oblicz());
    }

    @Override
    public String toString() {
        return "cos(" + w.toString() + ")";
    }

    @Override
    protected int priorytet() {
        return 4;
    }
}