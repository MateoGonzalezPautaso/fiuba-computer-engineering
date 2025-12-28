package org.pdp.model.enemigos;

import org.pdp.comun.Posicion;
import org.pdp.model.logicaJuego.AccionesDeJuego;
import org.pdp.model.InteractuaConRobot;
import org.pdp.model.Jugador;
import org.pdp.model.MovimientosJugador;

abstract public class Robot extends Enemigo implements InteractuaConRobot {

    public Robot(Posicion posicion) { super(posicion); }

    public abstract int cantidadMovimientos();

    @Override
    public void interactuarConRobot(Robot robot, AccionesDeJuego acciones) {
        acciones.chocarRobots(robot, this);
    }

    private MovimientosJugador calcularMovimiento(Jugador jugador) {
        Posicion posicionJugador = jugador.getPosicion();

        int dx = Integer.compare(posicionJugador.getX(), this.getPosicion().getX());
        int dy = Integer.compare(posicionJugador.getY(), this.getPosicion().getY());

        // Buscar el enum que corresponde a ese dx, dy
        for (MovimientosJugador movimiento : MovimientosJugador.values()) {
            if (movimiento.getMovimientoEnX() == dx && movimiento.getMovimientoEnY() == dy) {
                return movimiento;
            }
        }

        return MovimientosJugador.ESPERAR; // En caso de error, el robot se queda quieto
    }

    public void moverRobot(Jugador jugador) {
        MovimientosJugador direccion = calcularMovimiento(jugador);

        Posicion posicionActual = super.getPosicion();
        int nuevoX = posicionActual.getX() + direccion.getMovimientoEnX();
        int nuevoY = posicionActual.getY() + direccion.getMovimientoEnY();

        posicionActual.actualizar(nuevoX, nuevoY);
    }
}
