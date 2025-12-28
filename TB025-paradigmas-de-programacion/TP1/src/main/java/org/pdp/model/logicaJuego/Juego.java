package org.pdp.model.logicaJuego;

import org.pdp.comun.Posicion;
import org.pdp.model.*;
import org.pdp.model.enemigos.Fuego;
import org.pdp.model.enemigos.Robot;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Juego implements HandlerNuevoNivel, HandlerElementos, AccionesDeJuego{
    private Tablero tablero;
    private int nivelActual;
    private Jugador jugador;
    private boolean jugadorMuerto;
    protected int tpSafeDisponibles;
    protected int cantidadDiamantesEnNivel;
    protected int diamantesCapturados;
    protected int cantidadRobotsEnNivel;
    protected int robotsQuemados;

    protected List<ElementoTablero> elementosActivos = new ArrayList<>();
    protected List<ElementoTablero> elementosDescartados = new ArrayList<>();
    protected List<Robot> robotsActivos = new ArrayList<>();
    private static final Map<String, MovimientosJugador> mapaTeclasAMovimientos = new HashMap<>();

    private GeneradorNiveles generadorNiveles;
    private Teletransportador teletransportador;
    private GestorElementos gestorElementos;

    static{
        mapaTeclasAMovimientos.put("Q",MovimientosJugador.ARRIBAYIZQUIERDA);
        mapaTeclasAMovimientos.put("W",MovimientosJugador.ARRIBA);
        mapaTeclasAMovimientos.put("E",MovimientosJugador.ARRIBAYDERECHA);
        mapaTeclasAMovimientos.put("A",MovimientosJugador.IZQUIERDA);
        mapaTeclasAMovimientos.put("S",MovimientosJugador.ESPERAR);
        mapaTeclasAMovimientos.put("D",MovimientosJugador.DERECHA);
        mapaTeclasAMovimientos.put("Z",MovimientosJugador.ABAJOYIZQUIERDA);
        mapaTeclasAMovimientos.put("X",MovimientosJugador.ABAJO);
        mapaTeclasAMovimientos.put("C",MovimientosJugador.ABAJOYDERECHA);
    }

    public Juego(int ancho, int alto){
        this.tablero = new Tablero(ancho, alto);
        this.nivelActual = 1;
        this.diamantesCapturados = 0;
        this.robotsQuemados = 0;
        this.tpSafeDisponibles = 40;
        this.jugadorMuerto = false;

        this.gestorElementos = new GestorElementos(tablero, this);

        this.generadorNiveles = new GeneradorNiveles(tablero, this);
        generadorNiveles.iniciarNivel(nivelActual);
    }


    private void subirNivel() {
        nivelActual++;
        tpSafeDisponibles ++;
        generadorNiveles.iniciarNivel(nivelActual);
    }

    private void verificarNivel() {
        if (cantidadDiamantesEnNivel == 0 || cantidadRobotsEnNivel == 0) {
            subirNivel();
        }

        procesarTurnoRobots();

        if (cantidadDiamantesEnNivel == 0 || cantidadRobotsEnNivel == 0) {
            subirNivel();
        }
    }

    public void asociarTeclaPresionadaAMovimiento(String tecla) {
        if (mapaTeclasAMovimientos.containsKey(tecla)) {
            MovimientosJugador mov = mapaTeclasAMovimientos.get(tecla);
            moverJugadorEnJuego(mov);
            verificarNivel();
        }
    }


    /**
     * Mueve al jugador dependiendo del valor del Enum y devuelve el
     * ElementoTablero que estaba en la nueva posicion
     */
    private void moverJugadorEnJuego(MovimientosJugador mov) {
        Posicion origen = jugador.getPosicion().getCopiaPosicion();
        jugador.desplazarse(mov);
        InteractuaConJugador elementoAInteractuar = tablero.moverJugador(jugador, origen, jugador.getPosicion());
        if(elementoAInteractuar != null) {
            elementoAInteractuar.interactuarConJugador(this);
        }
    }

    private void procesarTurnoRobots() {
        ArrayList<Robot> copiaRobotsActivos = new ArrayList<>(robotsActivos);

        for (Robot robot : copiaRobotsActivos) {
            if (!elementosActivos.contains(robot)) continue;

            boolean colision = false;
            int cantidadMovimientos = robot.cantidadMovimientos();
            for (int i = 0; i < cantidadMovimientos; i++) {
                if(colision){
                    break;
                }

                Posicion origen = robot.getPosicion().getCopiaPosicion();
                robot.moverRobot(jugador);

                ElementoTablero elementoAnterior = tablero.getElementoEnPosicion(robot.getPosicion());
                if(elementoAnterior != null){
                    colision = true;
                }

                InteractuaConRobot antiguo = tablero.moverRobot(robot, origen, robot.getPosicion());

                if(antiguo != null){
                    antiguo.interactuarConRobot(robot,this);
                }

                if(elementosDescartados.contains(robot)){
                    break;  // Se murio el robot, pierde el resto de losl turnos.
                }
            }
        }
    }


    // Lógica de Teletransportador

    public void teletransportacionRandom() {
        teletransportador.teletransportarRandom();
    }

    public void teletransportacionSafe(int x, int y) {
        Posicion destino = new Posicion(x, y);
        teletransportador.teletransportarASafe(destino);
    }

    private void postTeletransportacion(boolean consumirSafe, InteractuaConJugador elemento) {
        if (consumirSafe) tpSafeDisponibles--;
        if (elemento != null) elemento.interactuarConJugador(this);
        verificarNivel();
    }

    // Logica de GeneradorNiveles

    public void reiniciarValoresPorNivel(int nivel){
        this.cantidadDiamantesEnNivel = 0;
        this.cantidadRobotsEnNivel = 2 + nivel;
        this.elementosActivos.clear();
        this.elementosDescartados.clear();
        this.robotsActivos.clear();
        this.tablero.iniciarTableroVacio();

        Posicion centroTablero = new Posicion(tablero.getAncho()/2, tablero.getAlto()/2);
        this.jugador = new Jugador(centroTablero);
        tablero.setElementoEnPosicion(centroTablero, jugador);

        this.teletransportador = new Teletransportador(tablero, jugador, this::postTeletransportacion);
    }

    public void agregarDiamanteAlNivel(Diamante diamante){
        elementosActivos.add(diamante);
        cantidadDiamantesEnNivel++;
    }

    public void agregarRobotAlNivel(Robot robot) {
        elementosActivos.add(robot);
        robotsActivos.add(robot);
    }

    // Lógica de GestordeElementos

    private void eliminarRobot(Robot robot) {
        elementosActivos.remove(robot);
        robotsActivos.remove(robot);
        elementosDescartados.add(robot);
    }

    public void quemarRobot(Robot robot) {
        eliminarRobot(robot);
        robotsQuemados++;
        cantidadRobotsEnNivel--;
    }

    public void agregarFuego(Fuego fuego) {
        elementosActivos.add(fuego);
    }

    public void recolectarDiamante(Diamante diamanteRecolectado) {
        cantidadDiamantesEnNivel--;
        diamantesCapturados++;
        elementosDescartados.add(diamanteRecolectado);
        elementosActivos.remove(diamanteRecolectado);
    }

    // Definicion de interacciones

    public void matarJugador(){ this.jugadorMuerto = true; }

    public void chocarRobots(Robot robot1, Robot robot2){
        gestorElementos.crearFuego(robot1,robot2);
    }

    public void robotPisaFuego(Robot robotQuemado, Fuego fuego){
        gestorElementos.quemarRobot(robotQuemado,fuego);
    }

    public void jugadorCapturaDiamante(Diamante diamante) { gestorElementos.recolectarDiamante(diamante); }

    // getters y setters

    public boolean isJugadorMuerto() { return jugadorMuerto; }

    public Jugador getJugador() { return jugador; }

    public List<ElementoTablero> getElementosActivos() { return elementosActivos; }

    public List<ElementoTablero> getElementosDescartados() { return elementosDescartados; }

    // Estadísticas de la interfaz

    public int getNivelActual() { return nivelActual; }

    public int getCantidadDiamantesEnNivel() { return cantidadDiamantesEnNivel; }

    public int getCantidadRobotsEnNivel() { return cantidadRobotsEnNivel; }

    public int getDiamantesCapturados() { return diamantesCapturados; }

    public int getRobotsQuemados() { return robotsQuemados; }

    public int getTpSafeDisponibles() { return tpSafeDisponibles; }

}