(ns tp2.tortuga)

(defn nueva-tortuga []
  "Proporciona el estado inicial de la tortuga"
  {:posicion [0 0]
   :angulo 90                                                ;; Empieza hacia la arriba
   :pluma true                                               ;; true abajo. false arriba
   :stroke-width 1
   :color "black"
   :trayectoria []})                                        ;; array con las lineas dibujadas

(defn pluma-arriba [estado]
  (assoc estado :pluma false))

(defn pluma-abajo [estado]
  (assoc estado :pluma true))

(defn derecha [estado angulo]
  (update estado :angulo #(mod (- % angulo) 360)))

(defn izquierda [estado angulo]
  (update estado :angulo #(mod (+ % angulo) 360)))

(defn grosor-1 [estado]
  (assoc estado :stroke-width 1))

(defn grosor-2 [estado]
  (assoc estado :stroke-width 2))

(defn color-rojo [estado]
  (assoc estado :color "red"))

(defn color-azul [estado]
  (assoc estado :color "blue"))

(defn color-negro [estado]
  (assoc estado :color "black"))

(defn grados-a-radian [grados]
  (* grados (/ Math/PI 180)))

(defn adelante [estado distancia]
  (let [angulo-rad (grados-a-radian (estado :angulo))
        grosor-linea (:stroke-width estado)
        color-linea (:color estado)
        dx (* distancia (Math/cos angulo-rad))
        dy (* -1 distancia (Math/sin angulo-rad))
        x-ori (nth (estado :posicion) 0)
        y-ori (nth (estado :posicion) 1)
        x-dest (+ dx x-ori)
        y-dest (+ dy y-ori)
        nueva-linea {:x1 x-ori :x2 x-dest :y1 y-ori :y2 y-dest :stroke-width grosor-linea :color color-linea}]
    (-> estado
        (assoc :posicion [x-dest y-dest])
        (update :trayectoria #(if (:pluma estado) (conj % nueva-linea) %)))))
