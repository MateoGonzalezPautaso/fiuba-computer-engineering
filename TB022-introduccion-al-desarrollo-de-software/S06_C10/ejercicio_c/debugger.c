#include "stdio.h"

void mostrar(int fecha){
  if (fecha == 18122022){
    printf("Argentina campeon!\n");
  } else {
    printf("No es una fecha importante...\n");
  }
}

int main(){
  int fecha = 1012025;
  mostrar(fecha);
  return 0;
}
