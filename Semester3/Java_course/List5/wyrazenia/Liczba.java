package wyrazenia;

public class Liczba extends Wyrazenie {
    private final double wartosc;

    public static final Liczba ZERO = new Liczba(0.0);
    public static final Liczba JEDEN = new Liczba(1.0);

    public Liczba(double wartosc) {
        this.wartosc = wartosc;
    }

    @Override
    public double oblicz() {
        return wartosc;
    }

    @Override
    public String toString() {
        return Double.toString(wartosc);
    }

    @Override
    protected int priorytet() {
        return 5;
    }
}
