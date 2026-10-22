package figury;

public class Trojkat {
    private Punkt a, b, c;

    public Trojkat(Punkt a, Punkt b, Punkt c) {
        if (Punkt.porownaj(a, b) || Punkt.porownaj(b, c) || Punkt.porownaj(c, a))
            throw new IllegalArgumentException("Points cannot be equal!");

        double w = (b.zwroc_x() - a.zwroc_x()) * (c.zwroc_y() - a.zwroc_y()) -
                (b.zwroc_y() - a.zwroc_y()) * (c.zwroc_x() - a.zwroc_x());

        if (Math.abs(w) < 1e-9) {
            throw new IllegalArgumentException("Points cannot be collinear!");
        }

        this.a = a;
        this.b = b;
        this.c = c;
    }

    public void przesun(Wektor v) {
        a.przesun(v);
        b.przesun(v);
        c.przesun(v);
    }

    public void obroc(Punkt p, double kat) {
        a.obroc(p, kat);
        b.obroc(p, kat);
        c.obroc(p, kat);
    }

    public void odbij(Prosta p) {
        a.odbij(p);
        b.odbij(p);
        c.odbij(p);
    }

    @Override
    public String toString() {
        return String.format("A = %s, B = %s, C = %s", a.toString(), b.toString(), c.toString());
    }
};