package org.pdp.model.logicaJuego;

import org.pdp.comun.Posicion;
import org.pdp.model.InteractuaConJugador;
import org.pdp.model.Jugador;
import org.pdp.model.Tablero;

import java.util.Random;

public class Teletransportador {
    private final Tablero tablero;
    private final Jugador jugador;
    private final HandlerTeletransportacion handler;

    public Teletransportador(Tablero tablero, Jugador jugador, HandlerTeletransportacion handler) {
        this.tablero = tablero;
        this.jugador = jugador;
        this.handler = handler;
    }

    public void teletransportarRandom() {
        Random rand = new Random();
        int xRand = rand.nextInt(tablero.getAncho());
        int yRand = rand.nextInt(tablero.getAlto());
        Posicion destino = new Posicion(xRand, yRand);

        moverJugadorADestino(destino, false);
    }

    public void teletransportarASafe(Posicion destino) {
        moverJugadorADestino(destino, true);
    }

    private void moverJugadorADestino(Posicion destino, boolean consumirSafe) {
        Posicion origen = jugador.getPosicion().getCopiaPosicion();
        InteractuaConJugador elemento = tablero.moverJugador(jugador, origen, destino);

        handler.postTeletransportacion(consumirSafe, elemento);
    }

}
