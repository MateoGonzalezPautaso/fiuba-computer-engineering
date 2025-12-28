package org.pdp.controller;

import javafx.scene.layout.GridPane;
import org.pdp.comun.Posicion;
import org.pdp.model.ElementoTablero;
import org.pdp.model.Jugador;
import org.pdp.view.RepresentacionElementoTablero;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ControladorRepresentacionesTablero {
    private GridPane gridTablero;
    private Map<ElementoTablero, RepresentacionElementoTablero> mapaElementosARepresentaciones = new HashMap<>();
    private CreadorRepresentaciones creadorRepresentaciones;

    public ControladorRepresentacionesTablero(GridPane gridTablero) {
        this.gridTablero = gridTablero;
        this.creadorRepresentaciones = new CreadorRepresentaciones();
    }

    public Map<ElementoTablero, RepresentacionElementoTablero> getMapaElementosARepresentaciones() {
        return mapaElementosARepresentaciones;
    }

    private void agregarRepresentacion(ElementoTablero elemento) {
        RepresentacionElementoTablero representacionElementoActual = creadorRepresentaciones.crearRepresentacion(elemento);
        mapaElementosARepresentaciones.put(elemento, representacionElementoActual);

        Posicion posicionElemento = elemento.getPosicion();
        gridTablero.add(representacionElementoActual.getVisualizacion(), posicionElemento.getX(), posicionElemento.getY());
    }

    public void crearRepresentacionJugador(Jugador jugador) {
        agregarRepresentacion(jugador);
    }

    public void crearRepresentaciones(List<ElementoTablero> elementosActivos) {
        for (ElementoTablero elementoActual : elementosActivos) {
            if (!mapaElementosARepresentaciones.containsKey(elementoActual)) {
                // Si el elemento no existe en el hash, se agrega.
                agregarRepresentacion(elementoActual);
            }
        }
    }

    public void actualizarRepresentacion(ElementoTablero elemento) {
        RepresentacionElementoTablero representacionDelElemento = mapaElementosARepresentaciones.get(elemento);
        gridTablero.getChildren().remove(representacionDelElemento.getVisualizacion());
        Posicion nuevaPosicion = elemento.getPosicion();
        representacionDelElemento.setPosicion(nuevaPosicion);

        gridTablero.add(representacionDelElemento.getVisualizacion(), nuevaPosicion.getX(), nuevaPosicion.getY());
    }

    public void actualizarRepresentacionesElementos(List<ElementoTablero> elementosActivos){
        // Si hay nuevos elementos en la lista, se agregan sus representaciones.
        crearRepresentaciones(elementosActivos);

        for(ElementoTablero elementoActual : elementosActivos){
            actualizarRepresentacion(elementoActual);
        }
    }

    public void borrarRepresentaciones(List<ElementoTablero> elementosDescartados) {
        for (ElementoTablero elementoActual : elementosDescartados) {

            RepresentacionElementoTablero representacionElementoDescartado = mapaElementosARepresentaciones.get(elementoActual);
            if(representacionElementoDescartado == null){
                continue;   // El elemento ya se borro de la interfaz
            }

            mapaElementosARepresentaciones.remove(elementoActual);
            gridTablero.getChildren().remove(representacionElementoDescartado.getVisualizacion());
        }
    }

}
