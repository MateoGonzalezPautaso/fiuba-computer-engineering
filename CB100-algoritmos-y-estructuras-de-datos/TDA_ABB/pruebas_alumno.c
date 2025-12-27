#include "pa2m.h"
#include "src/abb.h"

bool dummy(void *a, void *b)
{
	return true;
}

bool fail(void *a, void *b)
{
	return false;
}

int comparar_numeros(void *a, void *b)
{
	int valor_a = *(int *)a;
	int valor_b = *(int *)b;

	if (valor_a > valor_b) {
		return 1;
	} else if (valor_a < valor_b) {
		return -1;
	} else {
		return 0;
	}
}

void crearABBDebeRetornarABB()
{
	abb_t *abb = abb_crear(comparar_numeros);
	pa2m_afirmar(abb != NULL, "El ABB fue creado exitosamente");
	abb_destruir(abb);
}

void ABBNuevoDebeTenerCeroNodos()
{
	abb_t *abb = abb_crear(comparar_numeros);
	size_t cantidad = abb_cantidad(abb);
	pa2m_afirmar(cantidad == 0, "El ABB nuevo esta vacio");
	abb_destruir(abb);
}

void insertarElementosABBDebeRetornarTrue()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	pa2m_afirmar(abb_insertar(abb, &a) == true,
		     "El primer elemento fue agregado exitosamente al ABB");
	pa2m_afirmar(abb_insertar(abb, &b) == true,
		     "El segundo elemento fue agregado exitosamente al ABB");
	pa2m_afirmar(abb_insertar(abb, &c) == true,
		     "El tercer elemento fue agregado exitosamente al ABB");
	size_t cantidad = abb_cantidad(abb);
	pa2m_afirmar(cantidad == 3, "El ABB tiene 3 nodos");
	abb_destruir(abb);
}

void obtenerElementoABBDebeRetornarElemento()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	pa2m_afirmar(abb_obtener(abb, &a) == &a,
		     "El primer elemento fue obtenido exitosamente del ABB");
	pa2m_afirmar(abb_obtener(abb, &b) == &b,
		     "El segundo elemento fue obtenido exitosamente del ABB");
	pa2m_afirmar(abb_obtener(abb, &c) == &c,
		     "El tercer elemento fue obtenido exitosamente del ABB");
	pa2m_afirmar(abb_obtener(abb, &d) == NULL,
		     "Obtener elemento inexistente devuelve NULL");
	abb_destruir(abb);
}

void quitarElementosABBDebeRetornarTrue()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	int *encontrado = NULL;
	pa2m_afirmar(abb_quitar(abb, &c, (void **)&encontrado) == true,
		     "El elemento fue quitado exitosamente del ABB");
	pa2m_afirmar(encontrado == &c, "El elemento quitado no es nulo");
	size_t cantidad = abb_cantidad(abb);
	pa2m_afirmar(cantidad == 2, "El ABB tiene 2 nodos luego de quitar 1");
	abb_destruir(abb);
}

void iterarInordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	int ctx = 0;
	size_t cantidad = abb_iterar_inorden(abb, dummy, &ctx);
	pa2m_afirmar(cantidad == 3, "Se iteraron 3 elementos inorden");
	abb_destruir(abb);
}

void iterarPreordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	int ctx = 0;
	size_t cantidad = abb_iterar_preorden(abb, dummy, &ctx);
	pa2m_afirmar(cantidad == 3, "Se iteraron 3 elementos preorden");
	abb_destruir(abb);
}

void iterarPostordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	int ctx = 0;
	size_t cantidad = abb_iterar_postorden(abb, dummy, &ctx);
	pa2m_afirmar(cantidad == 3, "Se iteraron 3 elementos postorden");
	abb_destruir(abb);
}

void vectorizarInordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	void *vector[3];
	size_t cantidad = abb_vectorizar_inorden(abb, vector, 3);
	pa2m_afirmar(cantidad == 3,
		     "Se iteraron 3 elementos vectorizados inorden");
	pa2m_afirmar(*(int *)vector[0] == 1,
		     "El primer elemento del vector inorden es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 2,
		     "El segundo elemento del vector inorden es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 3,
		     "El tercer elemento del vector inorden es el correcto");
	abb_destruir(abb);
}

void vectorizarPreordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	void *vector[3];
	size_t cantidad = abb_vectorizar_preorden(abb, vector, 3);
	pa2m_afirmar(cantidad == 3,
		     "Se iteraron 3 elementos vectorizados preorden");
	pa2m_afirmar(*(int *)vector[0] == 1,
		     "El primer elemento del vector preorden es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 2,
		     "El segundo elemento del vector preorden es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 3,
		     "El tercer elemento del vector preorden es el correcto");
	abb_destruir(abb);
}

void vectorizarPostordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	void *vector[3];
	size_t cantidad = abb_vectorizar_postorden(abb, vector, 3);
	pa2m_afirmar(cantidad == 3,
		     "Se iteraron 3 elementos vectorizados postorden");
	pa2m_afirmar(*(int *)vector[0] == 3,
		     "El primer elemento del vector postorden es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 2,
		     "El segundo elemento del vector postorden es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 1,
		     "El tercer elemento del vector postorden es el correcto");
	abb_destruir(abb);
}

void falloIterarInordenDebeRetornarCantidadIterada()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	int c = 3;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	int ctx = 0;
	size_t cantidad = abb_iterar_inorden(abb, fail, &ctx);
	pa2m_afirmar(
		cantidad == 1,
		"Fallo en la primera iteracion y devuelve 1 elementos iterados");
	abb_destruir(abb);
}

void quitarABBConUnNodo()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	abb_insertar(abb, &a);
	int *encontrado = NULL;
	pa2m_afirmar(abb_quitar(abb, &a, (void **)&encontrado) == true,
		     "La raiz fue quitada exitosamente del ABB");
	pa2m_afirmar(encontrado == &a, "La raiz quitada es no nula");
	size_t cantidad = abb_cantidad(abb);
	pa2m_afirmar(cantidad == 0, "El ABB tiene 0 nodos");
	abb_destruir(abb);
}

void quitarABBConNodoConHijo()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 1;
	int b = 2;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	int *encontrado = NULL;
	pa2m_afirmar(abb_quitar(abb, &a, (void **)&encontrado) == true,
		     "La raiz con un hijo fue quitada exitosamente del ABB");
	pa2m_afirmar(encontrado == &a, "La raiz quitada coincide");
	size_t cantidad = abb_cantidad(abb);
	pa2m_afirmar(cantidad == 1, "El ABB tiene 1 nodo");
	abb_destruir(abb);
}

void quitarABBConNodoConDosHijos()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int a = 10;
	int b = 5;
	int c = 15;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	int *encontrado = NULL;
	pa2m_afirmar(abb_quitar(abb, &a, (void **)&encontrado) == true,
		     "La raiz con dos hijos fue quitada exitosamente del ABB");
	pa2m_afirmar(encontrado == &a, "La raiz quitada coincide");
	size_t cantidad = abb_cantidad(abb);
	pa2m_afirmar(cantidad == 2, "El ABB tiene 2 nodos");
	abb_destruir(abb);
}

void pruebasVectoresDiferentesCantidades()
{
	abb_t *abb = abb_crear(comparar_numeros);
	int numeros[] = { 10, 5, 15, 2, 8, 12, 3 };
	size_t cantidad_numeros = 7;

	for (size_t i = 0; i < cantidad_numeros; i++)
		abb_insertar(abb, &numeros[i]);

	void *vector1[7];
	size_t cantidad1 = abb_vectorizar_inorden(abb, vector1, 7);
	pa2m_afirmar(cantidad1 == 7,
		     "Se recorrieron los 7 elementos del vector");
	pa2m_afirmar(vector1[0] == &numeros[3],
		     "El primer elemento del vector coincide");
	pa2m_afirmar(vector1[6] == &numeros[2],
		     "El ultimo elemento del vector coincide");

	void *vector2[3];
	size_t cantidad2 = abb_vectorizar_inorden(abb, vector2, 3);
	pa2m_afirmar(cantidad2 == 3,
		     "Se recorrieron solo 3 elementos del vector");
	pa2m_afirmar(vector2[0] == &numeros[3],
		     "El primer elemento del vector coincide");
	pa2m_afirmar(vector2[2] == &numeros[1],
		     "El ultimo elemento del vector coincide");

	void *vector3[10];
	size_t cantidad3 = abb_vectorizar_inorden(abb, vector3, 10);
	pa2m_afirmar(
		cantidad3 == 7,
		"Se recorrieron los 7 elementos del vector aunque tenga tamaño 10");
	pa2m_afirmar(vector3[0] == &numeros[3],
		     "El primer elemento del vector coincide");
	pa2m_afirmar(vector3[6] == &numeros[2],
		     "El ultimo elemento del vector coincide");

	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas de ABB ===============");
	crearABBDebeRetornarABB();
	ABBNuevoDebeTenerCeroNodos();
	insertarElementosABBDebeRetornarTrue();
	quitarElementosABBDebeRetornarTrue();
	obtenerElementoABBDebeRetornarElemento();
	iterarInordenDebeRetornarCantidadIterada();
	iterarPreordenDebeRetornarCantidadIterada();
	iterarPostordenDebeRetornarCantidadIterada();
	vectorizarInordenDebeRetornarCantidadIterada();
	vectorizarPreordenDebeRetornarCantidadIterada();
	vectorizarPostordenDebeRetornarCantidadIterada();
	falloIterarInordenDebeRetornarCantidadIterada();
	quitarABBConUnNodo();
	quitarABBConNodoConHijo();
	quitarABBConNodoConDosHijos();
	pruebasVectoresDiferentesCantidades();

	return pa2m_mostrar_reporte();
}
