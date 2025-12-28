package org.pdp.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class ControladorMenu {
    @FXML private TextField anchoTablero;
    @FXML private TextField altoTablero;
    @FXML private Button botonJugar;
    @FXML private Label labelError;

    private void cambiarEsceneaATablero(int ancho, int alto) throws IOException {
        // Carga la nueva escena a un nodo raiz
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/tablero.fxml"));
        Parent root = loader.load();

        // Consigue el controlador asociado a tablero.fxml (ControladorTablero)
        ControladorTablero controladorTablero = loader.getController();
        controladorTablero.iniciarJuego(ancho, alto); // ancho y alto vienen de los TextField

        // Muestra la nueva escena por el stage
        Scene nuevaEscena = new Scene(root);
        Stage stage = (Stage) botonJugar.getScene().getWindow();
        stage.setScene(nuevaEscena);
    }

    @FXML
    protected void onClickBotonJugar() {
        try {
            int ancho = Integer.parseInt(anchoTablero.getText());
            int alto = Integer.parseInt(altoTablero.getText());

            if (ancho < 15 || ancho > 30 || alto < 15 || alto > 30) {
                labelError.setText("Los valores deben estar entre 15 y 30.");
                return;
            }

            // iniciar juego
            cambiarEsceneaATablero(ancho, alto);

        } catch (Exception e) {
            labelError.setText("Los valores deben ser numeros");
        }
    }
}
