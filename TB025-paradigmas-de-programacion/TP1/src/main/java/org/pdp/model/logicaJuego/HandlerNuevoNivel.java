package org.pdp.model.logicaJuego;

import org.pdp.model.Diamante;
import org.pdp.model.ElementoTablero;
import org.pdp.model.enemigos.Robot;

import java.util.List;

public interface HandlerNuevoNivel {
    void reiniciarValoresPorNivel(int nivel);
    int getCantidadDiamantesEnNivel();
    int getCantidadRobotsEnNivel();
    void agregarDiamanteAlNivel(Diamante diamante);
    void agregarRobotAlNivel(Robot robot);
    List<ElementoTablero> getElementosActivos();
}
