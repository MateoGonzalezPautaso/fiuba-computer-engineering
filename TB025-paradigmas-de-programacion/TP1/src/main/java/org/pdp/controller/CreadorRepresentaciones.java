package org.pdp.controller;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import org.pdp.model.ElementoTablero;
import org.pdp.view.RepresentacionElementoTablero;

import java.io.InputStream;
import java.util.Objects;

public class CreadorRepresentaciones {

    public  RepresentacionElementoTablero crearRepresentacion(ElementoTablero elemento){
        String ruta = elemento.rutaImagen();
        ImageView gifElemento = crearImageView(ruta);
        return new RepresentacionElementoTablero(elemento.getPosicion(), gifElemento);
    }

    private ImageView crearImageView(String ruta){
        InputStream lectura =  Objects.requireNonNull(CreadorRepresentaciones.class.getResourceAsStream(ruta));

        Image imagen = new Image(lectura);

        ImageView imageView = new ImageView(imagen);
        imageView.setFitWidth(32);
        imageView.setFitHeight(32);
        return imageView;
    }
}
