#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "lista.h"

typedef struct Nodo nodo_t;
struct Nodo{
	void* dato ;
	nodo_t* siguiente ;
};

struct lista{
	nodo_t* primero ;
	nodo_t* ultimo ;
	size_t largo ;
};

struct lista_iter{
	nodo_t* nodo_actual;
	nodo_t* nodo_anterior ;
	lista_t* lista ;
};

/*PRIMITIVAS DE LA LISTA*/

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t)) ;
	if(!lista)
		return NULL ;
	lista->primero = lista->ultimo = NULL ;
	lista->largo = 0 ;
	return lista ;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){

	while(!lista_esta_vacia(lista)){
		void* dato = lista_borrar_primero(lista) ;
		if(destruir_dato)
			destruir_dato(dato);
	}
	free(lista) ;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == 0 ;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo ;
}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista))
		return NULL;
	return lista->primero->dato ;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista))
		return NULL;
	return lista->ultimo->dato ;
}


bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = malloc(sizeof(nodo_t)) ;
	if(!nodo)
		return false ;
	nodo->dato = dato ;

	if(lista_esta_vacia(lista)){
		lista->primero = lista->ultimo = nodo ;
		nodo->siguiente = NULL ;
	}
	else{
		nodo->siguiente = lista->primero ;
		lista->primero = nodo ;
	}
	lista->largo ++ ;
	return true ;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = malloc(sizeof(nodo_t)) ;
	if(!nodo)
		return false ;
	nodo->dato = dato ;
	nodo->siguiente = NULL ;
	if(lista_esta_vacia(lista))
		lista->primero = lista->ultimo = nodo ;
	else{
		lista->ultimo->siguiente = nodo ;
		lista->ultimo = nodo ;
	}
	
	lista->largo ++ ;
	return true ;
}

void* lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista))
		return NULL;

	nodo_t* nodo = lista->primero ;
	lista->primero = nodo ->siguiente ;

	/*Si la lista quedo vacia*/
	if(!lista->primero)
		lista->ultimo = NULL ;
	
	void* dato = nodo->dato ;
	free(nodo) ;
	lista->largo -- ;
	return dato ;	
}

/*ITERADOR EXTERNO*/
/*PRIMITIVAS DE ITERACION*/

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t)) ;
	if(!iter)
		return NULL ;

	iter->lista = lista ;
	iter->nodo_actual = lista->primero ;
	iter->nodo_anterior = NULL ;
	return iter ;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->nodo_actual == NULL ;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter))
		return false ;

	iter->nodo_anterior = iter->nodo_actual ;
	iter->nodo_actual = iter->nodo_actual->siguiente ;
	return true ;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter))
		return NULL ;
	return iter->nodo_actual->dato ;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo)
		return false ;

	nuevo_nodo->dato = dato ;

	/*CASO INSERTAR AL PRINCIPIO*/
	if(!iter->nodo_anterior){
		nuevo_nodo->siguiente = iter->lista->primero ;
		iter->lista->primero = nuevo_nodo ;
	}

	/*INSERTAR AL MEDIO O AL FINAL*/
	else{
		nuevo_nodo->siguiente = iter->nodo_actual ;
		iter->nodo_anterior->siguiente = nuevo_nodo;
	}
	/*SI INSERTAMOS EN UNA LISTA VACIA O AL FINAL MODIFICAMOS LA REF AL FINAL*/
	if(!iter->nodo_actual)
		iter->lista->ultimo = nuevo_nodo ;
	
	iter->nodo_actual = nuevo_nodo ;
	iter->lista->largo ++ ;

	return true ;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(!iter->nodo_actual)
		return NULL ;

	nodo_t* nodo_a_borrar = iter->nodo_actual ;

	/*BORRAR DEL PRINCIPIO*/
	if(!iter->nodo_anterior)
		iter->lista->primero = nodo_a_borrar->siguiente ;
	/*BORRAR DEL MEDIO O DEL FINAL*/
	else
		iter->nodo_anterior->siguiente = nodo_a_borrar->siguiente;
	
	iter->nodo_actual = nodo_a_borrar->siguiente ;

	/*LA LISTA QUEDO VACIA*/
	if(!iter->nodo_actual && !iter->nodo_anterior)
		iter->lista->primero = iter->lista->ultimo = NULL ;
	/*SE BORRO DEL FINAL*/
	if(!iter->nodo_actual)
		iter->lista->ultimo = iter->nodo_anterior ;
	/*SE BORRO DEL PPIO PERO LA LISTA NO QUEDO VACIA*/
	if(!iter->nodo_anterior)
		iter->lista->primero = iter->nodo_actual ;

	iter->lista->largo -- ;

	void* dato = nodo_a_borrar->dato ;
	free(nodo_a_borrar) ;
	return dato ;
}

/*ITERADOR INTERNO*/
void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra){
	if(!lista->primero || !visitar)
		return ;

	bool iter_continuar = true ;
	nodo_t* nodo_actual = lista->primero ;
	while(nodo_actual && iter_continuar){
		iter_continuar = visitar(nodo_actual->dato, extra) ;
		nodo_actual = nodo_actual->siguiente ;
	}
}