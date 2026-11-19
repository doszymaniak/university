package wyrazenia;

public class Podziel extends Wyrazenie {
    private final Wyrazenie lewy;
    private final Wyrazenie prawy;

    public Podziel(Wyrazenie l, Wyrazenie p) {
        this.lewy = l;
        this.prawy = p;
    }

    @Override
    public double oblicz() {
        if (prawy.oblicz() == 0)
            throw new IllegalArgumentException("Nie mozna dzielic przez zero!");
        return lewy.oblicz() / prawy.oblicz();
    }

    @Override
    public String toString() {
        return nawiasy(lewy, false) + " / " + nawiasy(prawy, true);
    }

    @Override
    protected int priorytet() {
        return 2;
    }
}