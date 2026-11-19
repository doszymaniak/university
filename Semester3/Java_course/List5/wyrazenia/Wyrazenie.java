package wyrazenia;

public abstract class Wyrazenie implements Obliczalny {
    protected abstract int priorytet();

    protected String nawiasy(Wyrazenie w, boolean prawa) {
        if (w.priorytet() < priorytet() ||
                (prawa && w.priorytet() == priorytet())) {
            return "(" + w.toString() + ")";
        }

        return w.toString();
    }

    public static double suma(Wyrazenie... wyr) {
        double wyn = 0.0;
        for (Wyrazenie w : wyr)
            wyn += w.oblicz();
        return wyn;
    }

    public static double iloczyn(Wyrazenie... wyr) {
        double wyn = 1.0;
        for (Wyrazenie w : wyr)
            wyn *= w.oblicz();
        return wyn;
    }
}
