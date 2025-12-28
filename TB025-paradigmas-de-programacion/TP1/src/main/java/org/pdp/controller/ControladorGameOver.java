package org.pdp.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;

import java.io.IOException;

public class ControladorGameOver {
    @FXML private Button botonVolverMenu;
    @FXML private Label labelDiamantesRecolectados;
    @FXML private Label labelRobotsQuemados;

    public void setLabels(int diamantesRecolectados, int robotsQuemados) {
        labelDiamantesRecolectados.setText("Diamantes recolectados: " + diamantesRecolectados);
        labelRobotsQuemados.setText("Robots quemados: " + robotsQuemados);
    }

    @FXML protected void onClickBotonVolverMenu() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("/menu.fxml"));

        // Muestra la nueva escena por el stage
        Scene nuevaEscena = new Scene(root);
        Stage stage = (Stage) botonVolverMenu.getScene().getWindow();
        stage.setScene(nuevaEscena);
    }
}

