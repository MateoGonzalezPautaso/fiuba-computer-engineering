(ns tp2.parser
  (:require [clojure.string :as str]))

(defn cargar-sistema-l [archivo]
  "Carga la estructura de un sistema-l desde el archivo especificado"

  (let [contenido (slurp (str "./resources/lsystems/" archivo))
        lista-parametros (str/split contenido #"\n")
        angulo (Double/parseDouble (first lista-parametros))
        axioma (second lista-parametros)
        reglas (->> (drop 2 lista-parametros)   ;; a partir de la 3ra línea
                    (map #(str/split % #" "))   ;;  ["F FF"] -> ["F" "FF"]
                    (map (fn [[pre post]]       ;; fn recibe [pre post]
                           [(first pre) post])) ;; convierte ["F" "FF"] en [\F "FF"]
                    (into {}))]                 ;; convierte [\F "FF"] en {\F "FF"}
    {:angulo angulo
     :sistema {
               :axioma axioma
               :reglas reglas
               }
     })
  )

