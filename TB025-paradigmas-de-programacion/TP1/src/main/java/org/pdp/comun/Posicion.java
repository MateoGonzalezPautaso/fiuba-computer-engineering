package org.pdp.comun;

public class Posicion {
        private int x;
        private int y;

        public Posicion(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public void actualizar(int nuevoX, int nuevoY){
            x = nuevoX;
            y = nuevoY;
        }

        @Override
        public boolean equals(Object o) {
            if (o == null || getClass() != o.getClass()) return false;
            Posicion posicion = (Posicion) o;
            return x == posicion.x && y == posicion.y;
        }

        public Posicion getCopiaPosicion(){
            return new Posicion(x,y);
        }
        public int getX() { return x; }
        public int getY() { return y; }
    }
