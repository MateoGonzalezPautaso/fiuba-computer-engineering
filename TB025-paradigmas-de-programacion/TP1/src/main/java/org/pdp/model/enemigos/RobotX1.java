package org.pdp.model.enemigos;

import org.pdp.comun.Posicion;

public class RobotX1 extends Robot{
    private final int cantidadMovimientos;

    public RobotX1(Posicion posicion) {
        super(posicion);
        cantidadMovimientos = 1;
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
        return "/img/RobotX1.gif";
    }
}
