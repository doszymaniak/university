import java.awt.*;

public class Kreska {
    protected Point poczatek, koniec;
    protected Color kolor;

    public Kreska(Point pocz, Point kon, Color kol) {
        poczatek = new Point(pocz);
        koniec = new Point(kon);
        kolor = kol;
    }

    public void rysuj(Graphics gr) {
        gr.setColor(kolor);
        gr.drawLine(poczatek.x, poczatek.y, koniec.x, koniec.y);
    }
}
