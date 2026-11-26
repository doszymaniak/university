import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class Powierzchnia extends Canvas {
    protected ArrayList<Kreska> kreski = new ArrayList<>();
    protected Point akt_pocz, akt_kon;
    protected Color akt_kol = Color.BLACK;
    boolean poza;

    public Powierzchnia() {
        setBackground(Color.WHITE);

        addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                int x = e.getX();
                int y = e.getY();
                akt_pocz = new Point(x, y);
                akt_kon = new Point(x, y);
                poza = (x < 0 || y < 0 || x >= getWidth() || y >= getHeight());
            }

            public void mouseReleased(MouseEvent e) {
                if (akt_pocz == null || akt_kon == null)
                    return;
                int x = e.getX();
                int y = e.getY();
                akt_kon = new Point(x, y);
                poza = (x < 0 || y < 0 || x >= getWidth() || y >= getHeight());
                if (!poza)
                    kreski.add(new Kreska(akt_pocz, akt_kon, akt_kol));
                akt_pocz = null;
                akt_kon = null;
                repaint();
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent e) {
                int x = e.getX();
                int y = e.getY();
                poza = (x < 0 || y < 0 || x >= getWidth() || y >= getHeight());
                akt_kon = new Point(x, y);
                repaint();
            }
        });
    }

    public void paint(Graphics gr) {
        for (Kreska k : kreski) {
            k.rysuj(gr);
        }
        if (akt_pocz != null && akt_kon != null && !poza) {
            gr.setColor(Color.gray);
            gr.drawLine(akt_pocz.x, akt_pocz.y, akt_kon.x, akt_kon.y);
        }
    }

    public void usunWszystkie() {
        kreski.clear();
        repaint();
    }

    public void usunPierwsza() {
        if (!kreski.isEmpty()) {
            kreski.remove(0);
            repaint();
        }
    }

    public void usunOstatnia() {
        if (!kreski.isEmpty()) {
            kreski.remove(kreski.size() - 1);
            repaint();
        }
    }
}