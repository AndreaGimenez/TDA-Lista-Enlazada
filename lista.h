#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stddef.h>


/*DEFINICION DE LOS TIPOS DE DATOS*/
struct lista ;
typedef struct lista lista_t ;
struct lista_iter ;
typedef struct lista_iter lista_iter_t;

/*PRIMITIVAS DE LA LISTA*/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al principio de la lista, valor se encuentra al principio de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la list. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Devuelve el largo de la lista.
//Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);


// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/*PRIMITIVAS DEL ITERADOR*/

// Crea un iterador.
// Post: devuelve un nuevo iterador vacío.
lista_iter_t *lista_iter_crear(lista_t *lista);

//Hace avanzar el iterador al siguiente nodo de la lista. Devuelve falso si ya
//se encontraba al final de la lista.
//Pre: el iterador fue creado.
//Post: el iterador se encuentra sobre el siguiente nodo
bool lista_iter_avanzar(lista_iter_t *iter);

//Obtiene la posicion actual del iterador de lista.
//Si está al final de la lista devuelve NULL.
//Pre: el iterador de lista fue creado.
//Post: se devolvió el valor del la posicion actual del iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Devuelve verdadero o falso, según si el iterador esta o no al final de la lista.
//Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador de lista.
//Pre: el iterador fue creado.
//Post: el iterador fue eliminado.
void lista_iter_destruir(lista_iter_t *iter);

//Agrega un nuevo elemento la lista. Devuelve falso en caso de error.
//Pre: la lista fue creada.
//Post: se agregó un nuevo elemento en la lista en la posicion actual del iterador
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra un elemento de la lista. Devuelve el valor de dicho elemento.
//Devuelve NULL esi el iterador se encontraba al final de la lista.
//Pre: el iterador de lista fue creado.
void *lista_iter_borrar(lista_iter_t *iter);

 void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);

void pruebas_alumno(void) ;
#endif 