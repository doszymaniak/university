package wyrazenia;

public class Pomnoz extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;

    public Pomnoz(Wyrazenie l, Wyrazenie p) {
        this.lewy = l;
        this.prawy = p;
    }

    @Override
    public double oblicz() {
        return lewy.oblicz() * prawy.oblicz();
    }

    @Override
    public String toString() {
        return nawiasy(lewy, false) + " * " + nawiasy(prawy, true);
    }

    @Override
    protected int priorytet() {
        return 2;
    }
}