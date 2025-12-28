package org.pdp.model.enemigos;

import org.pdp.comun.Posicion;

public class RobotX2 extends Robot{
    private final int cantidadMovimientos;

    public RobotX2(Posicion posicion) {
        super(posicion);
        cantidadMovimientos = 2;
    }

    public Posicion getPosicion() {
        return super.getPosicion();
    }

    @Override
    public int cantidadMovimientos() {
        return cantidadMovimientos;
    }

    @Override
    public String rutaImagen() {
        return "/img/RobotX2.gif";
    }
}
