package wyrazenia;

public class Potega extends Wyrazenie {
    private final Wyrazenie podstawa;
    private final Wyrazenie wykladnik;

    public Potega(Wyrazenie p, Wyrazenie w) {
        this.podstawa = p;
        this.wykladnik = w;
    }

    @Override
    public double oblicz() {
        return Math.pow(podstawa.oblicz(), wykladnik.oblicz());
    }

    @Override
    public String toString() {
        return "pow(" + podstawa + ", " + wykladnik + ")";
    }

    @Override
    protected int priorytet() {
        return 4;
    }
}