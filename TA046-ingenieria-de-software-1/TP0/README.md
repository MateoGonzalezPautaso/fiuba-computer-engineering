# TP0 - Piedra, Papel o Tijera

---

## Mateo Gonzalez Pautaso
- Padrón: 111699

- Mail: magonzalezp@fi.uba.ar

## Descripción 

Es una implementación del juego Piedra, Papel o Tijera en Java. El objetivo es modelar las reglas del juego respetando restricciones de diseño, evitando estructuras de control de flujo y favoreciendo el polimorfismo.

## Restricciones de diseño

- Sin uso de `if`, ciclos ni excepciones dentro de los métodos
- Sin herencia entre clases concretas
- Máximo 1 línea por método

## Diseño

El comportamiento se modela mediante **double dispatch**: cuando una jugada recibe un `vs`, delega la decisión en la otra jugada, que sabe exactamente qué resultado devolver según su tipo.

### Interfaces

- **`Move`**: contrato de una jugada. Define `vs(Move other)`, `againstRock`, `againstPaper` y `againstScissors`.
- **`Player`**: interfaz funcional que representa un jugador. Define `getMove()`, lo que permite usarla con lambdas.

### Clases

- **`Rock`**, **`Paper`**, **`Scissors`**: implementaciones concretas de `Move`. Cada una sabe cómo responder cuando se enfrenta a cada tipo de jugada.

## Estructura del proyecto

```
TP0/
├── src/
│   ├── main/java/is1/
│   │   ├── Move.java
│   │   ├── Rock.java
│   │   ├── Paper.java
│   │   ├── Scissors.java
│   │   └── Player.java
│   └── test/java/is1/
│       ├── RulesTest.java
│       └── GameTest.java
└── pom.xml
```


## Tests

### RulesTest
Verifica todas las combinaciones posibles de enfrentamientos entre jugadas:
- Piedra gana a Tijera
- Papel gana a Piedra
- Tijera gana a Papel
- Empates entre jugadas iguales

### GameTest
Verifica la extensibilidad del diseño mediante la interfaz `Player`. Dos jugadores definidos como lambdas se enfrentan usando `getMove().vs(...)`, demostrando que el sistema puede integrarse en contextos más amplios sin cambiar la lógica del juego.

## Ejecución

Requiere Java 21 y Maven. Para correr los tests:

```bash
cd TP0
mvn test
```