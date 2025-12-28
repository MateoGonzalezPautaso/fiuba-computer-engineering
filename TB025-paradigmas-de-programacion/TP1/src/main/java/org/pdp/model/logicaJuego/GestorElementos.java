package org.pdp.model.logicaJuego;

import org.pdp.comun.Posicion;
import org.pdp.model.Diamante;
import org.pdp.model.Tablero;
import org.pdp.model.enemigos.Fuego;
import org.pdp.model.enemigos.Robot;

public class GestorElementos {
    private final Tablero tablero;
    private final HandlerElementos handler;

    public GestorElementos(Tablero tablero, HandlerElementos handler) {
        this.tablero = tablero;
        this.handler = handler;
    }

    public void crearFuego(Robot robot1, Robot robot2) {
        Posicion posicionChoque = robot1.getPosicion().getCopiaPosicion();

        tablero.setElementoEnPosicion(robot1.getPosicion(), robot1);
        tablero.setElementoEnPosicion(robot2.getPosicion(), robot2);

        Fuego fuego = new Fuego(posicionChoque);
        tablero.setElementoEnPosicion(posicionChoque, fuego);

        handler.agregarFuego(fuego);
        handler.quemarRobot(robot1);
        handler.quemarRobot(robot2);
    }

    public void recolectarDiamante(Diamante diamanteRecolectado){
        handler.recolectarDiamante(diamanteRecolectado);
    }

    public void quemarRobot(Robot robotQuemado, Fuego fuego){
        Posicion posicionQuemado = robotQuemado.getPosicion();
        tablero.setElementoEnPosicion(posicionQuemado, fuego); // Se saca el robot quemado y se mantiene el fuego en la Celda

        handler.quemarRobot(robotQuemado);
    }

}
