package figury;

public class Punkt {
    private double x, y;

    public Punkt(double a, double b) {
        x = a;
        y = b;
    }

    public Punkt(Punkt a) {
        this.x = a.x;
        this.y = a.y;
    }

    public void przesun(Wektor v) {
        x += v.dx;
        y += v.dy;
    }

    public void obroc(Punkt srodek, double kat) {
        double cos = Math.cos(kat);
        double sin = Math.sin(kat);

        double temp_x = x - srodek.x;
        double temp_y = y - srodek.y;

        double obrot_x = temp_x * cos - temp_y * sin;
        double obrot_y = temp_x * sin + temp_y * cos;

        x = obrot_x + srodek.x;
        y = obrot_y + srodek.y;
    }

    public double zwroc_x() {
        return x;
    }

    public double zwroc_y() {
        return y;
    }

    public void odbij(Prosta p) {
        if (p.a == 0.0 && p.b == 0.0)
            throw new IllegalArgumentException("A and B must be non-zero!");
        double m = (p.a * x + p.b * y + p.c) / (p.a * p.a + p.b * p.b);

        x = x - 2.0 * p.a * m;
        y = y - 2.0 * p.b * m;
    }

    public static boolean porownaj(Punkt a, Punkt b) {
        return a.x == b.x && a.y == b.y;
    }

    @Override
    public String toString() {
        return String.format("(%.2f, %.2f)", x, y);
    }
};