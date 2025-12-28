package org.pdp.model;

import org.pdp.comun.Posicion;
import org.pdp.model.enemigos.Robot;
import org.pdp.model.logicaJuego.AccionesDeJuego;

public class Jugador extends ElementoTablero implements InteractuaConRobot {
    public Jugador(Posicion posicion) {
        super(posicion);
    }

    /**
     * Mueve al jugador hacia la direccion pasada por parametro.
     * Trunca el movieminto a los maximos que se indican en los parametros
     */
    public void desplazarse(MovimientosJugador direccion) {
        Posicion posicionJugador = super.getPosicion();
        int nuevoX = posicionJugador.getX() + direccion.getMovimientoEnX();
        int nuevoY = posicionJugador.getY() + direccion.getMovimientoEnY();

        posicionJugador.actualizar(nuevoX,nuevoY);
    }

    @Override
    public boolean esTransitableParaRobot() {
        return true;
    }

    @Override
    public void interactuarConRobot(Robot robot, AccionesDeJuego acciones) {
        acciones.matarJugador();
    }

    @Override
    public String rutaImagen() {
        return "/img/Jugador.gif";
    }
}
