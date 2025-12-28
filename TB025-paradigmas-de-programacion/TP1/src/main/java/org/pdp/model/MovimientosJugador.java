package org.pdp.model;

public enum MovimientosJugador {
    ESPERAR (0, 0),
    ARRIBA   (0, -1),
    ABAJO  (0, 1),
    IZQUIERDA    (-1, 0),
    DERECHA (1,0),
    ARRIBAYDERECHA  (1, -1),
    ARRIBAYIZQUIERDA  (-1, -1),
    ABAJOYDERECHA (1, 1),
    ABAJOYIZQUIERDA (-1,1);

    private final int movimientoEnX;
    private final int movimientoEnY;

    MovimientosJugador(int dx, int dy){
        this.movimientoEnX = dx;
        this.movimientoEnY = dy;
    }

    public int getMovimientoEnY() { return movimientoEnY; }

    public int getMovimientoEnX() { return movimientoEnX; }
}
