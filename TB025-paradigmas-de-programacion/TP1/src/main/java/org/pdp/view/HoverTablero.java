package org.pdp.view;

import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;

public class HoverTablero {
    private final int sizeCelda;
    private final GridPane gridTablero;
    private StackPane hoverPane;

    public HoverTablero(GridPane gridTablero, int sizeCelda) {
        this.gridTablero = gridTablero;
        this.sizeCelda = sizeCelda;
    }

    private void borrarHover() {
        if (hoverPane != null) {
            gridTablero.getChildren().remove(hoverPane);
            hoverPane = null;
        }
    }

    private void mostrarHover(int x, int y) {
        borrarHover();
        hoverPane = new StackPane();
        hoverPane.setPrefSize(sizeCelda,sizeCelda);
        hoverPane.setStyle(
                "-fx-background-color: rgba(255,255,0,0.3);" +
                        "-fx-border-color: yellow; -fx-border-width: 2;"
        );
        GridPane.setColumnIndex(hoverPane, x);
        GridPane.setRowIndex(hoverPane, y);
        gridTablero.getChildren().add(hoverPane);
    }

    public void activarHover() {
        gridTablero.setOnMouseMoved(evt -> {
            int x = (int)(evt.getX() / sizeCelda);
            int y = (int)(evt.getY() / sizeCelda);
            mostrarHover(x, y);
        });
    }

    public void desactivarHover() {
        gridTablero.setOnMouseMoved(null);
        gridTablero.setOnMouseClicked(null);
        borrarHover();
    }

}
