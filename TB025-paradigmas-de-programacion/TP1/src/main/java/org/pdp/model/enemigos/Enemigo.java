package org.pdp.model.enemigos;

import org.pdp.comun.Posicion;
import org.pdp.model.logicaJuego.AccionesDeJuego;
import org.pdp.model.ElementoTablero;
import org.pdp.model.InteractuaConJugador;

abstract public class Enemigo extends ElementoTablero implements InteractuaConJugador {

    public Enemigo(Posicion posicion) {
        super(posicion);
    }

    @Override
    public boolean esTransitableParaRobot() {
        return true;
    }

    @Override
    public void interactuarConJugador(AccionesDeJuego acciones) {
        acciones.matarJugador();
    }
}
