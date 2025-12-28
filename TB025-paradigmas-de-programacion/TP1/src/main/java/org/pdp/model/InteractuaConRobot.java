package org.pdp.model;

import org.pdp.model.enemigos.Robot;
import org.pdp.model.logicaJuego.AccionesDeJuego;

public interface InteractuaConRobot {

    void interactuarConRobot(Robot robot, AccionesDeJuego acciones);
}
