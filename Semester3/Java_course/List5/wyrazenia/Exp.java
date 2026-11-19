package wyrazenia;

public class Exp extends Wyrazenie {
    private final Wyrazenie w;

    public Exp(Wyrazenie w) {
        this.w = w;
    }

    @Override
    public double oblicz() {
        return Math.exp(w.oblicz());
    }

    @Override
    public String toString() {
        return "exp(" + w.toString() + ")";
    }

    @Override
    protected int priorytet() {
        return 4;
    }
}