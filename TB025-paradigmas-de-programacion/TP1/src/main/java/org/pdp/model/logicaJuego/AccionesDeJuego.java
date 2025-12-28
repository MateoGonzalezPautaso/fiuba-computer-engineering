package org.pdp.model.logicaJuego;

import org.pdp.model.Diamante;
import org.pdp.model.enemigos.Fuego;
import org.pdp.model.enemigos.Robot;

public interface AccionesDeJuego {
    void matarJugador();
    void chocarRobots(Robot robot1, Robot robot2);
    void robotPisaFuego(Robot robotQuemado, Fuego fuego);
    void jugadorCapturaDiamante(Diamante diamante);
}
