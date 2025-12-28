package org.pdp.view;

import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;


public class VistaTablero {
    private static final int SIZECELDA = 32;
    private final GridPane gridTablero;
    private final HoverTablero hoverTablero;

    public VistaTablero(GridPane gridTablero) {
        this.gridTablero = gridTablero;
        this.hoverTablero = new HoverTablero(gridTablero, SIZECELDA);
    }

    public void generarTableroGUI(int ancho, int alto) {
        gridTablero.getChildren().clear();  // Se borra el GridPane anterior
        gridTablero.setGridLinesVisible(false);

        for (int fila = 0; fila < alto; fila++) {
            for (int col = 0; col < ancho; col++) {

                StackPane celda = new StackPane();
                celda.setPrefSize(SIZECELDA, SIZECELDA);
                celda.setOpacity(0.7);

                // Alternar color como ajedrez
                if ((fila + col) % 2 == 0) {
                    celda.setStyle("-fx-background-color: #a0c172");
                } else {
                    celda.setStyle("-fx-background-color: #b8d8be");
                }

                gridTablero.add(celda, col, fila);
            }
        }
        gridTablero.setGridLinesVisible(true);
    }

    public void activarHover() {
        hoverTablero.activarHover();
    }

    public void desactivarHover() {
        hoverTablero.desactivarHover();
    }

}
