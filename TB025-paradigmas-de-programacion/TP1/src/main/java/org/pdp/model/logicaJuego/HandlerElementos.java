package org.pdp.model.logicaJuego;

import org.pdp.model.Diamante;
import org.pdp.model.enemigos.Fuego;
import org.pdp.model.enemigos.Robot;

public interface HandlerElementos {
    void quemarRobot(Robot robot);
    void agregarFuego(Fuego fuego);
    void recolectarDiamante(Diamante diamante);
}
