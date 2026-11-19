package wyrazenia;

public class Zmienna extends Wyrazenie {
    private final String nazwa;

    private final static java.util.TreeMap<String, Double> zmienne = new java.util.TreeMap<>();

    public Zmienna(String nazwa) {
        if (nazwa == null || !nazwa.matches("[a-z][a-z0-9]*"))
            throw new IllegalArgumentException("Niepoprawna nazwa zmiennej");
        this.nazwa = nazwa;
    }

    public static void set(String naz, double wart) {
        if (naz == null || !naz.matches("[a-z][a-z0-9]*"))
            throw new IllegalArgumentException("Niepoprawna nazwa zmiennej");
        zmienne.put(naz, wart);
    }

    public static double get(String naz) {
        if (naz == null)
            throw new IllegalArgumentException("Niepoprawna nazwa zmiennej");
        return zmienne.get(naz);
    }

    public static void remove(String naz) {
        if (naz == null)
            throw new IllegalArgumentException("Niepoprawna nazwa zmiennej");
        zmienne.remove(naz);
    }

    public static void clear() {
        zmienne.clear();
    }

    @Override
    public double oblicz() {
        return get(nazwa);
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
