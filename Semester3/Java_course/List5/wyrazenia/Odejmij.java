package wyrazenia;

public class Odejmij extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;

    public Odejmij(Wyrazenie l, Wyrazenie p) {
        this.lewy = l;
        this.prawy = p;
    }

    @Override
    public double oblicz() {
        return lewy.oblicz() - prawy.oblicz();
    }

    @Override
    public String toString() {
        return nawiasy(lewy, false) + " - " + nawiasy(prawy, true);
    }

    @Override
    protected int priorytet() {
        return 1;
    }
}