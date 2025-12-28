package org.pdp.model.logicaJuego;

import org.pdp.comun.Posicion;
import org.pdp.model.Diamante;
import org.pdp.model.ElementoTablero;
import org.pdp.model.Tablero;
import org.pdp.model.enemigos.RobotX1;
import org.pdp.model.enemigos.RobotX2;

import java.util.Random;

public class GeneradorNiveles {
    private Tablero tablero;
    private final HandlerNuevoNivel handler;

    public GeneradorNiveles(Tablero tablero, HandlerNuevoNivel handler) {
        this.tablero = tablero;
        this.handler = handler;
    }

    public void iniciarNivel(int nivel){
        handler.reiniciarValoresPorNivel(nivel);

        // Siempre se agregan 4 diamantes por nivel. Tienen que estar a 3 celdas de distancia como minimo.
        colocarDiamantes();

        // Agregar cantidad de robots dependiendo del nivel.
        int total = handler.getCantidadRobotsEnNivel();
        int cantidadX2 = total / 2;
        int cantidadX1 = total - cantidadX2;
        colocarRobots(cantidadX1, cantidadX2);
    }

    private void colocarRobots(int cantidadX1, int cantidadX2){
        Random generador = new Random();
        int X1Colocados = 0, X2Colocados = 0;

        while (X1Colocados < cantidadX1){
            int xRand = generador.nextInt(tablero.getAncho());
            int yRand = generador.nextInt(tablero.getAlto());
            Posicion posicionX1 = new Posicion(xRand, yRand);

            if ( tablero.getElementoEnPosicion(posicionX1) == null ) {
                // Si la celda esta vacia, se agrega el robot
                RobotX1 nuevoX1 = new RobotX1(posicionX1);
                tablero.setElementoEnPosicion(posicionX1, nuevoX1);
                handler.agregarRobotAlNivel(nuevoX1);
                X1Colocados++;
            }
        }

        while (X2Colocados < cantidadX2){
            int xRand = generador.nextInt(tablero.getAncho());
            int yRand = generador.nextInt(tablero.getAlto());
            Posicion posicionX2 = new Posicion(xRand, yRand);

            if ( tablero.getElementoEnPosicion(posicionX2) == null ) {
                // Si la celda esta vacia, se agrega el robot
                RobotX2 nuevoX2 = new RobotX2(posicionX2);
                tablero.setElementoEnPosicion(posicionX2, nuevoX2);
                handler.agregarRobotAlNivel(nuevoX2);
                X2Colocados++;
            }
        }
    }

    private void colocarDiamantes() {
        Random generador = new Random();

        while (handler.getCantidadDiamantesEnNivel() < 4) {
            int xRand = generador.nextInt(tablero.getAncho());
            int yRand = generador.nextInt(tablero.getAlto());
            Posicion posicionDiamante = new Posicion(xRand, yRand);

            if (tablero.getElementoEnPosicion(posicionDiamante) != null) {
                continue; // Si se quiere agregar el diamante y la celda esta ocupada, se busca otra Posicion
            }

            boolean flag = true;
            for (ElementoTablero elementoExistente : handler.getElementosActivos()) {
                // los elementoExistente solo van a ser instancias de Diamante porque comienza vacia al llamar esta funcion

                int distanciaX = Math.abs(xRand - elementoExistente.getPosicion().getX());
                int distanciaY = Math.abs(yRand - elementoExistente.getPosicion().getY());

                // Si el nuevo diamante esta dentro de un cuadrado de 3x3 de uno que ya existe, busca otra posicion.
                if(distanciaX <= 3 && distanciaY <= 3){
                    flag = false;   // Demasiado cerca de diamanteExistente
                    break;
                }
            }

            if (flag) {
                // Se agrega exitosamente el diamante al nivel
                Diamante nuevoDiamante = new Diamante(posicionDiamante);
                tablero.setElementoEnPosicion(posicionDiamante, nuevoDiamante);
                handler.agregarDiamanteAlNivel(nuevoDiamante);
            }
        }
    }

}
