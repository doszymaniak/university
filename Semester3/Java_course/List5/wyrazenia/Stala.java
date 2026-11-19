package wyrazenia;

public class Stala extends Wyrazenie {
    private final String nazwa;
    private final double wartosc;

    public static final Stala E = new Stala("e", Math.E);

    public static final Stala Pi = new Stala("π", Math.PI);

    public Stala(String nazwa, double wartosc) {
        this.nazwa = nazwa;
        this.wartosc = wartosc;
    }

    @Override
    public double oblicz() {
        return wartosc;
    }

    @Override
    public String toString() {
        return nazwa;
    }

    @Override
    protected int priorytet() {
        return 5;
    }
}
