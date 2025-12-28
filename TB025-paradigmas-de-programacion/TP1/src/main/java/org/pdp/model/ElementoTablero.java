package org.pdp.model;

import org.pdp.comun.Posicion;

public abstract class ElementoTablero {
    private Posicion posicion;

    public ElementoTablero(Posicion posicion){
        this.posicion = posicion;
    }

    public Posicion getPosicion() {
        return posicion;
    }

    public void setPosicion(Posicion posicion) { this.posicion = posicion; }

    public abstract boolean esTransitableParaRobot();

    public abstract String rutaImagen();
}
