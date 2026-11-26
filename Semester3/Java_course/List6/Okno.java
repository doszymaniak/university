import java.awt.*;
import java.awt.event.*;

public class Okno extends Frame {
    protected Powierzchnia powierzchnia;

    public Okno() {
        powierzchnia = new Powierzchnia();

        add(powierzchnia, BorderLayout.CENTER);

        List listaKolorow = new List();
        listaKolorow.add("Czarny");
        listaKolorow.add("Czerwony");
        listaKolorow.add("Niebieski");
        listaKolorow.add("Zielony");
        listaKolorow.select(0);
        add(listaKolorow, BorderLayout.EAST);

        Color[] kolory = { Color.BLACK, Color.RED, Color.BLUE, Color.GREEN };
        powierzchnia.akt_kol = kolory[0];

        listaKolorow.addItemListener(e -> {
            int idx = listaKolorow.getSelectedIndex();
            if (idx >= 0 && idx < kolory.length)
                powierzchnia.akt_kol = kolory[idx];
        });

        KeyAdapter klawisze = new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                int klawisz = e.getKeyCode();
                if (klawisz == KeyEvent.VK_BACK_SPACE)
                    powierzchnia.usunWszystkie();
                else if (klawisz == KeyEvent.VK_F)
                    powierzchnia.usunPierwsza();
                else if (klawisz == KeyEvent.VK_B || klawisz == KeyEvent.VK_L)
                    powierzchnia.usunOstatnia();
            }
        };

        powierzchnia.addKeyListener(klawisze);
        listaKolorow.addKeyListener(klawisze);

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

        setSize(800, 600);
        setVisible(true);
    }

    public static void main(String[] args) {
        new Okno();
    }
}
