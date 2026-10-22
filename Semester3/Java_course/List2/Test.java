import figury.*;

public class Test {
    public static void main(String[] args) {
        // Punkt
        System.out.println("TEST PUNKT");
        Punkt p1 = new Punkt(1.0, 5.0);
        Punkt p2 = new Punkt(4.0, 10.0);
        System.out.println("punkt P1: " + p1);
        System.out.println("punkt P2: " + p2);

        Wektor w1 = new Wektor(3.0, 4.5);
        System.out.println("wektor w1: " + w1);

        p1.przesun(w1);
        System.out.println("P1 przesuniety o w1: " + p1);

        p2.obroc(new Punkt(0, 0), Math.PI / 2);
        System.out.println("P2 obrocony wzgledem srodka ukladu o 90 stopni: " + p2);

        Prosta g = new Prosta(3, 4, 7);
        System.out.println("prosta g: " + g);

        Prosta y = new Prosta(1, 0, 0);
        System.out.println("oś Y: " + y);

        Punkt p1OdbityG = new Punkt(p1);
        p1OdbityG.odbij(g);
        System.out.println("P1 odbity wzgledem prostej g: " + p1OdbityG);

        Punkt p1OdbityY = new Punkt(p1);
        p1OdbityY.odbij(y);
        System.out.println("P1 odbity wzgledem osi Y: " + p1OdbityY);

        System.out.println("porownanie punktow p1 i p2: " + Punkt.porownaj(p1, p2));

        // Odcinek
        System.out.println("\nTEST ODCINEK");
        Odcinek ab = new Odcinek(p1, p2);
        System.out.println("odcinek AB: " + ab);

        ab.przesun(w1);
        System.out.println("AB przesuniety o wektor w1: " + ab);

        ab.obroc(new Punkt(0, 0), Math.PI / 2);
        System.out.println("AB obrocony wzgledem srodka ukladu o 90 stopni: " + ab);

        ab.odbij(g);
        System.out.println("AB odbity wzgledem prostej g: " + ab);

        ab.odbij(y);
        System.out.println("AB odbity wzgledem osi Y: " + ab);

        // Trojkat
        System.out.println("\nTEST TROJKAT");
        Trojkat abc = new Trojkat(new Punkt(1, 4), new Punkt(6, 7), new Punkt(4, 8));
        System.out.println("trojkat ABC: " + abc);

        abc.przesun(w1);
        System.out.println("ABC przesuniety o w1: " + abc);

        abc.obroc(new Punkt(0, 0), Math.PI / 2);
        System.out.println("ABC obrocony wzgledem srodka ukladu o 90 stopni: " + abc);

        abc.odbij(g);
        System.out.println("ABC odbity wzgledem prostej g: " + abc);

        abc.odbij(y);
        System.out.println("ABC odbity wzgledem osi Y: " + abc);

        System.out.println("\nTEST WEKTOR");
        Wektor w2 = new Wektor(10, 6);
        System.out.println("wektor w2: " + w2);

        System.out.println("zlozenie w1 i w2: " + Wektor.zloz(w1, w2));

        System.out.println("\nTEST PROSTA");
        Prosta p = new Prosta(4, -3, 0);
        System.out.println("prosta p: " + p);

        System.out.println("czy prostopadla do g (tak): " + Prosta.czy_prostopadle(p, g));

        System.out.println("czy rownolegla do g (nie): " + Prosta.czy_rownolegle(p, g));

        System.out.println("przesunieta o w1: " + Prosta.przesun(w1, p));

        System.out.println("punkt przeciecia y i g: " + Prosta.punkt_przeciecia(y, g));
    }
}
