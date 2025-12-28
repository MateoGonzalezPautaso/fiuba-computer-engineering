(ns tp2.core
  (:gen-class)
  (:require [tp2.sistemaL :as sistema])
  (:require [tp2.interprete :as interprete])
  (:require [tp2.pintor :as pintor])
  (:require [tp2.parser :as parser]))

(defn -main [& args]
  "Recibe por parametro: archivo.sl, cantidad, salida.svg"

  (let [[archivo-sl iteraciones-str salida-svg] args
        iteraciones (Integer/parseInt iteraciones-str)
        parseo (parser/cargar-sistema-l archivo-sl)
        angulo (:angulo parseo)
        sistema-l (:sistema parseo)
        cadena (sistema/sistema-l sistema-l iteraciones)
        trayectorias (interprete/interpretar cadena angulo)]
    (pintor/pintar trayectorias salida-svg))
  )
