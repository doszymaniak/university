package wyrazenia;

public class Log extends Wyrazenie {
    private final Wyrazenie podstawa;
    private final Wyrazenie argument;

    public Log(Wyrazenie p, Wyrazenie a) {
        this.podstawa = p;
        this.argument = a;
    }

    @Override
    public double oblicz() {
        double res = Math.log(argument.oblicz()) /
                Math.log(podstawa.oblicz());
        if (!Double.isFinite(res))
            throw new ArithmeticException("Niepoprawny wynik!");
        return res;
    }

    @Override
    public String toString() {
        return "log(" + podstawa + ", " + argument + ")";
    }

    @Override
    protected int priorytet() {
        return 4;
    }
}