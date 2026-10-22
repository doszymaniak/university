package figury;

public final class Odcinek {
    private Punkt a, b;

    public Odcinek(Punkt a, Punkt b) {
        if (Punkt.porownaj(a, b))
            throw new IllegalArgumentException("Points cannot be equal!");
        this.a = a;
        this.b = b;
    }

    public void przesun(Wektor v) {
        a.przesun(v);
        b.przesun(v);
    }

    public void obroc(Punkt p, double kat) {
        a.obroc(p, kat);
        b.obroc(p, kat);
    }

    public void odbij(Prosta p) {
        a.odbij(p);
        b.odbij(p);
    }

    @Override
    public String toString() {
        return String.format("A = %s, B = %s", a.toString(), b.toString());
    }
};