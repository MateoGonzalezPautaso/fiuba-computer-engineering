(ns tp2.sistemaL)

(defn aplicar-reglas [reglas cadena]
  (apply str
         (map #(get reglas % (str %)) cadena)))     ;; % = caracter actual de cadena

(defn sistema-l [sistema iteraciones]
  (let [reglas (:reglas sistema)]
    (loop [actual (:axioma sistema)
           i 0]
      (if (= i iteraciones)
        actual
        (recur (aplicar-reglas reglas actual) (inc i))))))