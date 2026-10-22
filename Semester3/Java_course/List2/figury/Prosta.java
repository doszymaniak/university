package figury;

public final class Prosta {
    public final double a, b, c;

    public Prosta(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public static Prosta przesun(Wektor w, Prosta p) {
        // A (x - dx) + B (y - dy) + C = 0
        return new Prosta(p.a, p.b, p.c - (p.a * w.dx) - (p.b * w.dy));
    }

    public static boolean czy_rownolegle(Prosta p1, Prosta p2) {
        // A1 * B2 - A2 * B1 = 0;
        return p1.a * p2.b - p2.a * p1.b == 0;
    }

    public static boolean czy_prostopadle(Prosta p1, Prosta p2) {
        // A1 * A2 + B1 * B2 = 0;
        return p1.a * p2.a + p1.b * p2.b == 0;
    }

    public static Punkt punkt_przeciecia(Prosta p1, Prosta p2) {
        double w = p1.a * p2.b - p2.a * p1.b;
        if (w == 0)
            return null;

        double w_x = (-p1.c) * p2.b - p1.b * (-p1.c);
        double w_y = p1.a * (-p2.c) - (-p1.c) * p2.a;

        return new Punkt(w_x / w, w_y / w);
    }

    @Override
    public String toString() {
        return String.format("A = %.2f, B = %.2f, C = %.2f", a, b, c);
    }
};
