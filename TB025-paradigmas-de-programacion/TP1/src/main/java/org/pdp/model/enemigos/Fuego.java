package org.pdp.model.enemigos;

import org.pdp.comun.Posicion;
import org.pdp.model.logicaJuego.AccionesDeJuego;
import org.pdp.model.InteractuaConRobot;

public class Fuego extends Enemigo implements InteractuaConRobot {

    public Fuego(Posicion posicion) {
        super(posicion);
    }

    @Override
    public void interactuarConRobot(Robot robot, AccionesDeJuego acciones) {
        acciones.robotPisaFuego(robot, this);
    }

    @Override
    public String rutaImagen() {
        return "/img/Fuego.gif";
    }
}
