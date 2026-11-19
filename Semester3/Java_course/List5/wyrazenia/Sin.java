package wyrazenia;

public class Sin extends Wyrazenie {
    private final Wyrazenie w;

    public Sin(Wyrazenie w) {
        this.w = w;
    }

    @Override
    public double oblicz() {
        return Math.sin(w.oblicz());
    }

    @Override
    public String toString() {
        return "sin(" + w.toString() + ")";
    }

    @Override
    protected int priorytet() {
        return 4;
    }
}