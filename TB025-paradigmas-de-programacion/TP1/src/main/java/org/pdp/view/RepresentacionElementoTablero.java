package org.pdp.view;

import javafx.scene.Node;
import org.pdp.comun.Posicion;

public class RepresentacionElementoTablero {
    private Posicion posicion;
    private Node visualizacion;

    public RepresentacionElementoTablero(Posicion posicion, Node visualizacion) {
        this.posicion = posicion;
        this.visualizacion = visualizacion;
    }

    public Posicion getPosicion() { return posicion; }

    public void setPosicion(Posicion posicion) { this.posicion = posicion; }

    public Node getVisualizacion() { return visualizacion; }
}
