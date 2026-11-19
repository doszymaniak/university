import wyrazenia.*;

public class Test {

    public static void wyswietl(Wyrazenie w, int nr) {

        System.out.println("\nWYRAZENIE " + nr + ":");
        System.out.println(w);
        System.out.println("WYNIK: " + w.oblicz());
    }

    public static void main(String[] args) {
        Zmienna.set("x", 0.618);
        Wyrazenie x = new Zmienna("x");

        // 1. 7 + 5 * x - 3
        Wyrazenie w1 = new Odejmij(
                new Dodaj(
                        new Liczba(7),
                        new Pomnoz(
                                new Liczba(5),
                                x)),
                new Liczba(3));

        // 2. ~(2 - x) * e
        Wyrazenie w2 = new Pomnoz(
                new Przeciwna(
                        new Odejmij(
                                new Liczba(2),
                                x)),
                Stala.E);

        // 3. 3 * (π - 1) / (!x + 2)
        Wyrazenie w3 = new Podziel(
                new Pomnoz(
                        new Liczba(3),
                        new Odejmij(
                                Stala.Pi,
                                Liczba.JEDEN)),
                new Dodaj(
                        new Odwrotna(x),
                        new Liczba(2)));

        // 4. sin((x + 13) * π / (19 - x))
        Wyrazenie w4 = new Sin(
                new Podziel(
                        new Pomnoz(
                                new Dodaj(
                                        x,
                                        new Liczba(13)),
                                Stala.Pi),
                        new Odejmij(
                                new Liczba(19),
                                x)));

        // 5. exp(17) + x * log(e, x + 11)
        Wyrazenie w5 = new Dodaj(
                new Exp(
                        new Liczba(17)),
                new Pomnoz(
                        x,
                        new Log(
                                Stala.E,
                                new Dodaj(
                                        x,
                                        new Liczba(11)))));

        wyswietl(w1, 1);
        wyswietl(w2, 2);
        wyswietl(w3, 3);
        wyswietl(w4, 4);
        wyswietl(w5, 5);

        System.out.println("\nSUMA: " +
                Wyrazenie.suma(w1, w2, w3, w4, w5));

        System.out.println("ILOCZYN: " +
                Wyrazenie.iloczyn(w1, w2, w3, w4, w5));
    }
}
