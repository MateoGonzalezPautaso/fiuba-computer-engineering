(ns tp2.pintor
  (:require [clojure.java.io :as io]))

(defn linea-a-svg [trayectoria]
  "Convierte un mapa de línea {:x1 :y1 :x2 :y2} en una línea SVG."
  (let [x1 (:x1 trayectoria)
        x2 (:x2 trayectoria)
        y1 (:y1 trayectoria)
        y2 (:y2 trayectoria)
        stroke-width (:stroke-width trayectoria)
        color (:color trayectoria)]
    ;; Las coordenas y de un archivo SVG crecen para abajo.
    (str "<line x1=\"" x1 "\" y1=\"" y1
         "\" x2=\"" x2 "\" y2=\"" y2
         "\" stroke=\"" color "\" stroke-width=\"" stroke-width "\" vector-effect=\"non-scaling-stroke\" />\n")))

(defn extremos [lineas]
  "Guarda los maximos y minimos de las coordenadas x,y"
  (let [xs (mapcat (juxt :x1 :x2) lineas)
        ys (mapcat (juxt :y1 :y2) lineas)]
    {:min-x (apply min xs)
     :max-x (apply max xs)
     :min-y (apply min ys)
     :max-y (apply max ys)}))

(defn pintar [lineas ruta-svg]
  "Recibe el vector con todas las coordenadas de las lineas y la ruta a un archivo svg.
  Dibuja en el svg todas lineas y asigna un marco"

  (let [lims (extremos lineas)
        padding 10
        min-x (:min-x lims)
        min-y (:min-y lims)
        max-x (:max-x lims)
        max-y (:max-y lims)
        ancho (- max-x min-x)
        alto (- max-y min-y)
        vb-x (- min-x padding)
        vb-y (- min-y padding)
        vb-w (+ ancho (* 2 padding))
        vb-h (+ alto (* 2 padding))
        contenido-svg (str
                        "<svg viewBox=\"" vb-x " " vb-y " " vb-w " " vb-h "\" xmlns=\"http://www.w3.org/2000/svg\">\n"
                        (apply str (map linea-a-svg lineas))
                        "</svg>")]
    (spit ruta-svg contenido-svg)))
