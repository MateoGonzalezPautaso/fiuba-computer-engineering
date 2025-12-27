#include "pa2m.h"
#include "src/hash.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2 * i == 10, "2*i es igual a 2 (%d)", 2 * i);
}

bool funcion_dummy(char *clave, void *elemento, void *ctx)
{
	return true;
}

void crearHashDebeRetornarHash()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);
	pa2m_afirmar(hash != NULL, "El Hash fue creado exitosamente");
	hash_destruir(hash);
}

void hashNuevoDebeTenerCantidadCero()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);
	size_t cantidad = hash_cantidad(hash);
	pa2m_afirmar(cantidad == 0, "El Hash nuevo esta vacio");
	hash_destruir(hash);
}

void hashConCapacidadMenorATresCambiaValor()
{
	size_t capacidad_inicial = 2;
	hash_t *hash = hash_crear(capacidad_inicial);
	pa2m_afirmar(
		hash != NULL,
		"La capacidad inicial era 0 < capacidad < 3 y fue cambiada a 3");
	hash_destruir(hash);
}

void crearHashFallidoDebeRetornarNULL()
{
	size_t capacidad_inicial = 0;
	hash_t *hash = hash_crear(capacidad_inicial);
	pa2m_afirmar(hash == NULL,
		     "Si la capacidad inicial es 0, no se crea el Hash");
	hash_destruir(hash);
}

void insertarHashDebeRetornarTrue()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "valentino";
	char *clave3 = "Nazarena";
	int valor1 = 21;
	int valor2 = 19;
	int valor3 = 15;

	bool resultado = false;

	resultado = hash_insertar(hash, clave1, (void *)&valor1, NULL);
	pa2m_afirmar(resultado == true,
		     "El primer par clave valor fue insertado correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El Hash tiene 1 elemento");

	resultado = hash_insertar(hash, clave2, (void *)&valor2, NULL);
	pa2m_afirmar(resultado == true,
		     "El segundo par clave valor fue insertado correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El Hash tiene 2 elementos");

	resultado = hash_insertar(hash, clave3, (void *)&valor3, NULL);
	pa2m_afirmar(resultado == true,
		     "El tercer par clave valor fue insertado correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 3, "El Hash tiene 3 elemento");

	hash_destruir(hash);
}

void insertarClaveNULLDebeRetornarFalse()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	int valor1 = 21;
	bool resultado = false;

	resultado = hash_insertar(hash, NULL, (void *)&valor1, NULL);
	pa2m_afirmar(
		resultado == false,
		"El primer par clave valor NO fue insertado correctamente ya que la clave era nula");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El Hash tiene 0 elementos");

	hash_destruir(hash);
}

void insertarRepetidoHashDebeRetornarValorViejo()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "valentino";
	char *clave3 = "Nazarena";
	int valor1 = 21;
	int valor2 = 19;
	int valor3 = 15;
	int valor4 = 100;

	bool resultado = false;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);
	hash_insertar(hash, clave2, (void *)&valor2, NULL);
	hash_insertar(hash, clave3, (void *)&valor3, NULL);

	int *encontrado = NULL;
	resultado = hash_insertar(hash, clave1, (void *)&valor4,
				  (void *)&encontrado);
	pa2m_afirmar(resultado == true,
		     "El nuevo valor de una clave repetida fue actualizado");
	pa2m_afirmar(*encontrado == valor1,
		     "El valor viejo retornado coincide con el de la prueba");

	hash_destruir(hash);
}

void hashBuscarDebeRetornarValor()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "valentino";
	char *clave3 = "Nazarena";
	int valor1 = 21;
	int valor2 = 19;
	int valor3 = 15;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);
	hash_insertar(hash, clave2, (void *)&valor2, NULL);
	hash_insertar(hash, clave3, (void *)&valor3, NULL);

	void *valor = hash_buscar(hash, clave1);
	int *encontrado = (int *)valor;
	pa2m_afirmar(*encontrado == valor1,
		     "El primer valor buscado coincide con el valor probado");

	valor = hash_buscar(hash, clave2);
	encontrado = (int *)valor;
	pa2m_afirmar(*encontrado == valor2,
		     "El segundo valor buscado coincide con el valor probado");

	hash_destruir(hash);
}

void hashBuscarDebeRetornarBool()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "valentino";
	char *clave3 = "Nazarena";
	int valor1 = 21;
	int valor2 = 19;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);
	hash_insertar(hash, clave2, (void *)&valor2, NULL);

	bool resultado = hash_contiene(hash, clave1);
	pa2m_afirmar(resultado == true,
		     "El valor esta contenido en la estructura");

	resultado = hash_contiene(hash, clave3);
	pa2m_afirmar(resultado == false,
		     "El valor no esta contenido en la estructura");

	hash_destruir(hash);
}

void hashQuitarDebeRetornarValor()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "valentino";
	char *clave3 = "Nazarena";
	int valor1 = 21;
	int valor2 = 19;
	int valor3 = 15;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);
	hash_insertar(hash, clave2, (void *)&valor2, NULL);
	hash_insertar(hash, clave3, (void *)&valor3, NULL);

	void *valor = hash_quitar(hash, clave1);
	int *quitado = (int *)valor;
	pa2m_afirmar(*quitado == valor1,
		     "El primer valor quitado coincide con el valor probado");

	pa2m_afirmar(2 == hash_cantidad(hash),
		     "Ahora la tabla de Hash tiene 2 elementos");

	valor = hash_quitar(hash, clave2);
	quitado = (int *)valor;
	pa2m_afirmar(*quitado == valor2,
		     "El segundo valor quitado coincide con el valor probado");

	pa2m_afirmar(1 == hash_cantidad(hash),
		     "Ahora la tabla de Hash tiene 1 elemento");

	hash_destruir(hash);
}

void hashQuitarClaveNULLDebeRetornarNULL()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	int valor1 = 21;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);

	void *valor = hash_quitar(hash, "Juan");
	pa2m_afirmar(
		valor == NULL,
		"El valor quitado es NULL ya que la clave no existe dentro del Hash");

	hash_destruir(hash);
}

void hashIterarDebeRetornarCantidadIterada()
{
	size_t capacidad_inicial = 5;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "valentino";
	char *clave3 = "Nazarena";
	int valor1 = 21;
	int valor2 = 19;
	int valor3 = 15;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);
	hash_insertar(hash, clave2, (void *)&valor2, NULL);
	hash_insertar(hash, clave3, (void *)&valor3, NULL);

	void *ctx = NULL;
	size_t iterados = hash_iterar(hash, funcion_dummy, ctx);
	pa2m_afirmar(
		iterados == hash_cantidad(hash),
		"La cantidad de nodos iterados coincide con la cantidad dentro del Hash");

	hash_destruir(hash);
}

void hashRehashDebeRetornarHashNuevo()
{
	size_t capacidad_inicial = 3;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "Mateo";
	char *clave2 = "Juan";
	char *clave3 = "Agustin";
	char *clave4 = "Uriel";
	int valor1 = 21;
	int valor2 = 19;
	int valor3 = 15;
	int valor4 = 234;

	hash_insertar(hash, clave1, (void *)&valor1, NULL);
	hash_insertar(hash, clave2, (void *)&valor2, NULL);
	hash_insertar(hash, clave3, (void *)&valor3, NULL);
	hash_insertar(hash, clave4, (void *)&valor4, NULL);

	pa2m_afirmar(
		4 == hash_cantidad(hash),
		"El Hash nuevo tiene la misma cantidad de nodos que antes pero un factor de carga mas chico");

	hash_destruir(hash);
}

void pruebasDeActualizacionDeClaves()
{
	size_t capacidad_inicial = 3;
	hash_t *hash = hash_crear(capacidad_inicial);

	char *clave1 = "1";

	char *valor1 = "A";
	char *valor2 = "B";

	char *encontrado = NULL;
	bool resultado = false;

	resultado = hash_insertar(hash, clave1, (void *)valor1,
				  (void *)&encontrado);
	pa2m_afirmar(resultado == true, "Inserto <1,A> exitosamente");
	pa2m_afirmar(encontrado == NULL,
		     "El elemento anterior reemplazado en el insertar es NULL");

	resultado = hash_insertar(hash, clave1, (void *)valor2,
				  (void *)&encontrado);
	pa2m_afirmar(resultado == true, "Inserto <1,B> exitosamente");
	pa2m_afirmar(encontrado == valor1,
		     "El elemento anterior reemplazado en el insertar es A");

	char *valor_buscado = hash_buscar(hash, clave1);
	pa2m_afirmar(valor_buscado == valor2, "Obtengo 1 y vale B");

	char *valor_quitado = hash_quitar(hash, clave1);
	pa2m_afirmar(valor_quitado == valor2,
		     "Elimino la clave 1 y devuelve B");

	resultado = hash_insertar(hash, clave1, (void *)valor2,
				  (void *)&encontrado);
	pa2m_afirmar(resultado == true, "Inserto <1,B> exitosamente");
	pa2m_afirmar(encontrado == NULL,
		     "El elemento anterior reemplazado en el insertar es NULL");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas de Hash ===============");
	//prueba_simple();
	crearHashDebeRetornarHash();
	hashNuevoDebeTenerCantidadCero();
	hashConCapacidadMenorATresCambiaValor();
	crearHashFallidoDebeRetornarNULL();
	insertarHashDebeRetornarTrue();
	insertarClaveNULLDebeRetornarFalse();
	insertarRepetidoHashDebeRetornarValorViejo();
	hashBuscarDebeRetornarValor();
	hashBuscarDebeRetornarBool();
	hashQuitarDebeRetornarValor();
	hashQuitarClaveNULLDebeRetornarNULL();
	hashIterarDebeRetornarCantidadIterada();
	hashRehashDebeRetornarHashNuevo();
	pruebasDeActualizacionDeClaves();

	return pa2m_mostrar_reporte();
}
