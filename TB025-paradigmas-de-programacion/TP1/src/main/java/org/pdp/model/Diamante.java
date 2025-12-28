package org.pdp.model;

import org.pdp.comun.Posicion;
import org.pdp.model.logicaJuego.AccionesDeJuego;

public class Diamante extends ElementoTablero implements InteractuaConJugador{

    public Diamante(Posicion posicion) { super(posicion); }

    @Override
    public void interactuarConJugador(AccionesDeJuego acciones) {
        acciones.jugadorCapturaDiamante(this);
    }

    @Override
    public boolean esTransitableParaRobot() {
        return false;
    }

    @Override
    public String rutaImagen() {
        return "/img/Diamante.gif";
    }
}
