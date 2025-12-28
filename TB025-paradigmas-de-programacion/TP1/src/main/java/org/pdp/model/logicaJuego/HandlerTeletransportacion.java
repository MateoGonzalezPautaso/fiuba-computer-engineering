package org.pdp.model.logicaJuego;

import org.pdp.model.InteractuaConJugador;

public interface HandlerTeletransportacion {
    void postTeletransportacion(boolean consumirSafe, InteractuaConJugador elemento);
}
