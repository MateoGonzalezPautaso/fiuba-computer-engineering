(ns tp2.interprete
  (:require [tp2.tortuga :as t]))

(def unidad-movimento 10)

(defn interpretar [cadena angulo]
  "A partir de la cadena formada por el sistema-L la traduce en el grafico tortuga"

  (loop [caracteres (seq cadena)
         pila-tortugas []
         tortuga (t/nueva-tortuga)
         trayectoria-total []]
    (if (empty? caracteres)
      ;; Ya se procesaron todos los caracteres. Agrego la trayectoria de la tortuga actual
      (into trayectoria-total (:trayectoria tortuga))

      (let[c (first caracteres) ;; se recorriendo la cadena.
           resto (rest caracteres)]
        (cond
          ;; F o G avanza 1 unidad
          (or (= c \F) (= c \G))
          (recur resto pila-tortugas (t/adelante tortuga unidad-movimento) trayectoria-total)

          ;; f o g: Pluma arriba, avanzar una unidad, pluma abajo
          (or (= c \f) (= c \g))
          (recur resto pila-tortugas (-> tortuga  (t/pluma-arriba) (t/adelante unidad-movimento) (t/pluma-abajo)) trayectoria-total)

          ;; +: girar a la derecha
          (= c \+)
          (recur resto pila-tortugas (t/derecha tortuga angulo) trayectoria-total)

          ;; -: girar a la izquierda
          (= c \-)
          (recur resto pila-tortugas (t/izquierda tortuga angulo) trayectoria-total)

          ;; |: invertir la dirección
          (= c \|)
          (recur resto pila-tortugas (t/derecha tortuga 180) trayectoria-total)

          ;; 1: cambia el grosor de la pluma a 1
          (= c \1)
          (recur resto pila-tortugas (t/grosor-1 tortuga) trayectoria-total)

          ;; 2: cambia el grosor de la pluma a 1
          (= c \2)
          (recur resto pila-tortugas (t/grosor-2 tortuga) trayectoria-total)

          ;; a: cambia el color a azul
          (= c \a)
          (recur resto pila-tortugas (t/color-azul tortuga) trayectoria-total)

          ;; r: cambia el color a rojo
          (= c \r)
          (recur resto pila-tortugas (t/color-rojo tortuga) trayectoria-total)

          ;; n: cambia el color a negro
          (= c \n)
          (recur resto pila-tortugas (t/color-negro tortuga) trayectoria-total)

          ;; [: apilar; mismo estado tortuga pero con la trayectoria vacia, asi no se repiten lineas
          (= c \[)
          (recur resto (conj pila-tortugas (assoc tortuga :trayectoria [])) tortuga trayectoria-total)

          ;; ]: desapilar (guarda todas la trayectoria de la tortuga actual)
          (= c \])
          (recur resto (pop pila-tortugas) (peek pila-tortugas) (into trayectoria-total (:trayectoria tortuga)))

          ;; cualquier otro caracter: ignorar
          :else
          (recur resto pila-tortugas tortuga trayectoria-total))))))

