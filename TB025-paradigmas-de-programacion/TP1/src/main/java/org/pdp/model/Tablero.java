package org.pdp.model;

import org.pdp.comun.Posicion;
import org.pdp.model.enemigos.Robot;

public class Tablero {
    private int ancho;
    private int alto;
    private Celda[][] matriz;

    public Tablero(int ancho, int alto) {
        this.alto = alto;
        this.ancho = ancho;
        this.matriz = new Celda[alto][ancho];
        iniciarTableroVacio();
    }

    public void iniciarTableroVacio() {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                matriz[y][x] = new Celda();
            }
        }
    }

    public int getAlto() {
        return alto;
    }
    public int getAncho() {
        return ancho;
    }

    /**Si no hay ningun ElementoTablero en esa posicion devuelve null*/
    public ElementoTablero getElementoEnPosicion(Posicion posicion) {
        Celda celdaPosicion = matriz[posicion.getX()][posicion.getY()];
        return celdaPosicion.getElementoTablero();
    }

    public void setElementoEnPosicion(Posicion posicion, ElementoTablero elemento) {
        if (elemento != null) {
            elemento.setPosicion(posicion);
        }

        Celda celdaPosicion = matriz[posicion.getX()][posicion.getY()];
        celdaPosicion.setElementoTablero(elemento);
    }

    private int[] modificarMovimiento(int dx, int dy, int xDestino, int yDestino){
        if (dx == 0 || dy == 0) {
            int aux = dx;
            dx = dy;
            dy = aux;

            if(dx + xDestino > ancho || dy + yDestino > alto) {
                dx = -dx;
                dy = -dy;
            }
        }else{
            // Caso diagonal
            dx = 0;
        }

        return new int[]{dx,dy};
    }


    public InteractuaConJugador moverJugador(Jugador jugador, Posicion origen, Posicion destino){
        // Trunca el movimiento a las dimensiones del tablero
        int xDestino = Math.max(0, Math.min(destino.getX(), ancho - 1));
        int yDestino = Math.max(0, Math.min(destino.getY(), alto - 1));
        Posicion destinoTruncado = new Posicion(xDestino, yDestino);

        ElementoTablero antiguo = getElementoEnPosicion(destinoTruncado);

        // Se vacia la celda de origen del movimiento
        setElementoEnPosicion(origen, null);

        // Se mueve el jugador a su nueva posicion
        setElementoEnPosicion(destinoTruncado,jugador);

        if(antiguo == jugador){
            return null;
        }

        return (InteractuaConJugador) antiguo;
    }

    public InteractuaConRobot moverRobot(Robot robot, Posicion origen, Posicion destino) {

        // Trunca el movimiento a las dimensiones del tablero
        int xDestino = Math.max(0, Math.min(destino.getX(), ancho - 1));
        int yDestino = Math.max(0, Math.min(destino.getY(), alto - 1));
        Posicion destinoTruncado = new Posicion(xDestino, yDestino);

        ElementoTablero antiguo = getElementoEnPosicion(destinoTruncado);

        if(antiguo != null && !antiguo.esTransitableParaRobot()){
            // Si la posicion es invalida se busca otra.
            int dx = xDestino - origen.getX();
            int dy = yDestino - origen.getY();

            int[] arr = modificarMovimiento(dx,dy,xDestino,yDestino);
            xDestino = origen.getX() + arr[0];
            yDestino = origen.getY() + arr[1];
            destinoTruncado.actualizar(xDestino,yDestino);
            antiguo = getElementoEnPosicion(destinoTruncado);
        }

        // Se vacia la celda de origen del movimiento
        setElementoEnPosicion(origen,null);

        // Se mueve el elemento a su nueva posicion
        setElementoEnPosicion(destinoTruncado,robot);

        return (InteractuaConRobot) antiguo;
    }
}
