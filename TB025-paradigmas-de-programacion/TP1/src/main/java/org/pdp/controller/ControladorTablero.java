package org.pdp.controller;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.PauseTransition;
import javafx.animation.Timeline;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.pdp.model.ElementoTablero;
import org.pdp.model.logicaJuego.Juego;
import org.pdp.view.RepresentacionElementoTablero;
import org.pdp.view.VistaTablero;

import java.io.IOException;
import java.util.Map;

public class ControladorTablero {
    private static final int SIZECELDA = 32;
    private VistaTablero vista;
    private ControladorRepresentacionesTablero controladorRepresentaciones;

    @FXML private GridPane gridTablero;
    @FXML private Label labelNivel;
    @FXML private Label labelDiamantesRestantesNivel;
    @FXML private Label labelRobots;
    @FXML private Label cantidadDiamantes;
    @FXML private Label cantidadRobotsQuemados;
    @FXML private Label teleportSeguroRestante;
    @FXML private Button botonTPRand;
    @FXML private Button botonTPSafe;

    private Juego juego;
    private int anchoTablero;
    private int altoTablero;

    public void iniciarJuego(int ancho, int alto) {
        this.vista = new VistaTablero(gridTablero);
        this.juego = new Juego(ancho, alto);
        this.anchoTablero = ancho;
        this.altoTablero = alto;
        this.controladorRepresentaciones = new ControladorRepresentacionesTablero(gridTablero);

        vista.generarTableroGUI(ancho, alto);

        controladorRepresentaciones.crearRepresentacionJugador(juego.getJugador());
        controladorRepresentaciones.crearRepresentaciones(juego.getElementosActivos());
        actualizarUI();
        listenerTeclas();
    }

    /**
     * Ejecuta la accion que se pasa por parametro.
     * Despues actualiza las representaciones en la vista acorde a las consecuencias
     * que tuvo la accion en el Juego.
     */
    private void procesarAccion(Runnable accion) {
        accion.run();       // Ejecuta el turno en el juego

        Map<ElementoTablero, RepresentacionElementoTablero> mapa = controladorRepresentaciones.getMapaElementosARepresentaciones();
        // Si el jugador no esta en el hash, siginifica que hay un nuevo jugador. Es decir, se subio de nivel
        if (!mapa.containsKey(juego.getJugador())) {
            // Se reemplazan las representaciones viejas por las nuevas
            mapa.clear(); // Se vacia el hash con las representaciones viejas
            vista.generarTableroGUI(anchoTablero,altoTablero); // Se inicia un nuevo GridPane
            controladorRepresentaciones.crearRepresentacionJugador(juego.getJugador());
            controladorRepresentaciones.crearRepresentaciones(juego.getElementosActivos()); // Se representan los nuevos elementosActivos
        } else {
            controladorRepresentaciones.actualizarRepresentacion(juego.getJugador());
            controladorRepresentaciones.actualizarRepresentacionesElementos(juego.getElementosActivos());
            controladorRepresentaciones.borrarRepresentaciones(juego.getElementosDescartados());
        }

        if (juego.isJugadorMuerto()) {
            // Si muere apaga todos los metodos de movimiento e inicia la animacion
            botonTPRand.setDisable(true);
            botonTPSafe.setDisable(true);
            gridTablero.setOnKeyPressed(null);
            iniciarAnimacionMuerte();
        }

        actualizarUI();
        gridTablero.requestFocus();
    }

    private void listenerTeclas() {
        gridTablero.setFocusTraversable(true);

        gridTablero.setOnKeyPressed(event -> {
            String teclaPresionada = event.getText().toUpperCase();
            procesarAccion(() -> juego.asociarTeclaPresionadaAMovimiento(teclaPresionada));
            event.consume();
        });

        gridTablero.requestFocus();
    }

    @FXML protected void onClickBotonTPRand() { procesarAccion(() -> juego.teletransportacionRandom()); }

    @FXML protected void onClickBotonTPSafe() {
        if (juego.getTpSafeDisponibles() == 0) return;

        if (botonTPSafe.getText().equals("Teletransportarse seguro")) {
            botonTPSafe.setText("Cancelar TP seguro");
            botonTPRand.setDisable(true);

            vista.activarHover();
            gridTablero.setOnMouseClicked(evt -> {
                int x = (int)(evt.getX() / SIZECELDA);
                int y = (int)(evt.getY() / SIZECELDA);
                vista.desactivarHover();
                procesarAccion(() -> juego.teletransportacionSafe(x, y));
                botonTPRand.setDisable(false);
                botonTPSafe.setText("Teletransportarse seguro");
            });

        } else {
            botonTPSafe.setText("Teletransportarse seguro");
            vista.desactivarHover();
            listenerTeclas();
            botonTPRand.setDisable(false);
        }
    }

    private void iniciarAnimacionMuerte(){
        Map<ElementoTablero, RepresentacionElementoTablero> mapa = controladorRepresentaciones.getMapaElementosARepresentaciones();
        // Crea la animacion de parpadeo
        Timeline parpadeo = new Timeline(
                new KeyFrame(Duration.millis(500), e -> {
                    for (RepresentacionElementoTablero representacion : mapa.values()) {
                        Node nodo = representacion.getVisualizacion();
                        nodo.setVisible(!nodo.isVisible());
                    }
                })
        );
        parpadeo.setCycleCount(Animation.INDEFINITE);
        parpadeo.play();

        // Agrega un delay para que el cambio de escena no sea tan brusco
        PauseTransition delay = new PauseTransition(Duration.seconds(4));
        delay.setOnFinished(evento -> {
            parpadeo.stop();
            try {
                cambiarEsceneaAPerdiste();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
        delay.play();
    }

    private void cambiarEsceneaAPerdiste() throws IOException {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/gameover.fxml"));
        Parent root = loader.load();

        // Consigue el controlador asociado a gameover.fxml (ControladorGameOver)
        ControladorGameOver controladorGameOver = loader.getController();
        controladorGameOver.setLabels(juego.getDiamantesCapturados(), juego.getRobotsQuemados());

        // Muestra la nueva escena por el stage
        Scene nuevaEscena = new Scene(root);
        Stage stage = (Stage) labelRobots.getScene().getWindow();
        stage.setScene(nuevaEscena);
    }


    private void actualizarUI() {
        labelNivel.setText("Nivel: " + juego.getNivelActual());
        labelDiamantesRestantesNivel.setText("Diamantes restantes: " + juego.getCantidadDiamantesEnNivel());
        labelRobots.setText("Robots restantes en el nivel: " + juego.getCantidadRobotsEnNivel());

        cantidadDiamantes.setText("Diamantes recolectados: " + juego.getDiamantesCapturados());
        cantidadRobotsQuemados.setText("Robots quemados: " + juego.getRobotsQuemados());

        teleportSeguroRestante.setText("Teletransportaciones seguras restantes: " + juego.getTpSafeDisponibles());
    }

}
