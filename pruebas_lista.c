#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

/*Tipo de dato con el que se probaran algunos aspectos de la lista,
la funcion de destruccion del mismo y los tipos enumerativos que utiliza*/

typedef enum cafe{
	variedad_negro = 1, 
	variedad_cortado = 2,
	variedad_capuccino = 3,
	variedad_americano = 4,
	variedad_cafe_con_leche = 5
} variedad_cefe_t;

typedef enum intensidades{
	intensidad_suave = 1,
	intensidad_media = 2,
	intensidad_fuerte = 3
}intensidad_cafe_t ;

typedef struct gusto{
	variedad_cefe_t tipo;
	bool azucar;
	bool sacarina ;
	intensidad_cafe_t intensidad ;
	size_t tazas_por_dia ;
}gusto_cafe_t ;

typedef struct consumidor{
	int numero_identificador ;
	char nombre[20] ;
	size_t edad ; 
	char sexo ;
	gusto_cafe_t* preferencia ;
} consumidor_cafe_t ;

void destruir_consumidor(void* consumidor){ 
	consumidor_cafe_t* consumidor_actual = (consumidor_cafe_t*)consumidor ;
	gusto_cafe_t* cafe = consumidor_actual->preferencia;
	
	free(cafe);
	free(consumidor_actual);
}

/* *** *** *** */

void pruebas_lista_vacia() ;
void pruebas_lista_algunos_elementos() ;
void pruebas_funcionamiento_lista() ;
void pruebas_iter_interno() ;
bool multiplicar(void* dato, void* extra) ;
bool imprimir(void* dato , void*extra) ;
bool es_menor(void* dato, void* extra) ;
void pruebas_funcionamiento_iterador() ;

void pruebas_lista_vacia(){
	printf("PRUEBAS LISTA VACIA \n\n") ;
	lista_t* lista = lista_crear() ;
	print_test("Crear lista", lista != NULL) ;
	print_test("La lista esta vacia", lista_esta_vacia(lista)) ;
	print_test("Ver primero es invalido", !lista_ver_primero(lista)) ;
	print_test("Borrar es invalido", !lista_borrar_primero(lista)) ;
	lista_destruir(lista, NULL);
	print_test("La lista ha sido destruida", true) ;
}

void pruebas_lista_algunos_elementos(){
	printf("\n\nPRUEBAS LISTA ALGUNOS ELEMENTOS \n\n") ;
	lista_t* lista = lista_crear() ;
	print_test("La lista esta vacia", lista_esta_vacia(lista)) ;

	lista_iter_t* iter_1 = lista_iter_crear(lista) ;

	print_test("El iterador esta al principio", (int*)lista_iter_ver_actual(iter_1) == NULL) ;
	print_test("El iterador esta al final", lista_iter_al_final(iter_1) == true) ;
	lista_iter_destruir(iter_1) ;

	int elemento_0 = 22 ;
	char elemento_1 = 'a' ;
	bool elemento_2 = true ;
	char elemento_3[] = "Ingenieria Informatica" ;

	print_test("Insertar un elemento al principio en una lista vacia es valido", lista_insertar_primero(lista, &elemento_0)) ;
	print_test("La lista ya no esta vacia", !lista_esta_vacia(lista)) ;
	print_test("El tamaño de la lista es 1", lista_largo(lista) == 1) ;
	print_test("Ver primero es valido", lista_ver_primero(lista) != NULL) ;
	print_test("Insertar elemento_1 es valido", lista_insertar_ultimo(lista, &elemento_1)) ;
	print_test("Insertar elemento_2 es valido", lista_insertar_primero(lista, &elemento_2)) ;
	print_test("Insertar elemento_3 es valido", lista_insertar_primero(lista,elemento_3)) ;
	print_test("Ver primero es I", *(char*)lista_ver_primero(lista) == elemento_3[0]) ;
	print_test("La lista tiene 4 elementos", lista_largo(lista) == 4) ;

	double elemento_4 = 3.14 ;
	char* elemento_5 = &elemento_1 ;

	print_test("Insertar adelante funciona", lista_insertar_primero(lista, &elemento_4)) ;
	print_test("Ver primero es 3.14", *(double*)lista_ver_primero(lista) == elemento_4) ;
	print_test("Insertar al final funciona", lista_insertar_ultimo(lista, elemento_5)) ;
	print_test("La lista tiene 6 elementos", lista_largo(lista) == 6) ;
	while(!lista_esta_vacia(lista))
		lista_borrar_primero(lista);
	
	/*FUNCIONA COMO RECIEN CREADA*/
	print_test("La lista esta vacia", lista_esta_vacia(lista)) ;
	print_test("Ver primero es invalido", !lista_ver_primero(lista)) ;
	print_test("Borrar es invalido", !lista_borrar_primero(lista)) ;
	lista_destruir(lista, NULL) ;
	print_test("La lista ha sido destruida", true) ;
}

void pruebas_de_volumen(){
	printf("\n\nPRUEBAS LISTA ALGUNOS ELEMENTOS \n\n") ;
	lista_t* lista = lista_crear() ;
	print_test("La lista esta vacia", lista_esta_vacia(lista)) ;

	int vec[5000] ;

	for(int i = 0 ; i < 5000 ; i++)
		vec[i] = i ;
	
	bool ok = true ;

	for(int j = 0 ; j < 5000 && ok ; j++){
		ok &= lista_insertar_primero(lista, &vec[j]) ;
		ok &= lista_insertar_ultimo(lista, &vec[j]) ;
	}
	print_test("La carga en volumen se ha completado", ok) ;
	print_test("El tamaño de la lista es 10000", lista_largo(lista) == 10000) ;

	lista_destruir(lista, NULL) ;
	printf("La lista ha sido destruida\n") ;
}

void pruebas_funcionamiento_lista(){
	printf("\n\nPRUEBAS FUNCIONAMIENTO CORRECTO DE LA LISTA \n\n") ;
	lista_t* lista = lista_crear() ;
	print_test("La lista esta vacia", lista_esta_vacia(lista)) ;
	
	/*Datos que se insertaran*/
	/*Primer dato*/
	consumidor_cafe_t* consumidor_1 = (consumidor_cafe_t*)malloc(sizeof(consumidor_cafe_t));
	consumidor_1->numero_identificador = 100 ;
	consumidor_1->edad = 52 ;
	consumidor_1->sexo = 'F' ;
	gusto_cafe_t* cafe_consumidor_1 = (gusto_cafe_t*)malloc(sizeof(gusto_cafe_t));
	cafe_consumidor_1->tipo = variedad_negro ;
	cafe_consumidor_1->azucar = false ;
	cafe_consumidor_1->sacarina = true ;
	cafe_consumidor_1->intensidad = intensidad_fuerte ;
	cafe_consumidor_1->tazas_por_dia = 1 ;
	consumidor_1->preferencia =cafe_consumidor_1 ;

	/*Segundo dato*/
	consumidor_cafe_t* consumidor_2 = (consumidor_cafe_t*)malloc(sizeof(consumidor_cafe_t));
	consumidor_2->numero_identificador = 200 ;
	consumidor_2->edad = 23 ;
	consumidor_2->sexo = 'M' ;
	gusto_cafe_t* cafe_consumidor_2 = (gusto_cafe_t*)malloc(sizeof(gusto_cafe_t));
	cafe_consumidor_2->tipo = variedad_capuccino ;
	cafe_consumidor_2->azucar = true ;
	cafe_consumidor_2->sacarina = false;
	cafe_consumidor_2->intensidad = intensidad_media ;
	cafe_consumidor_2->tazas_por_dia = 2 ;
	consumidor_2->preferencia =cafe_consumidor_2 ;

	/*Tercer dato*/
	consumidor_cafe_t* consumidor_3 = (consumidor_cafe_t*)malloc(sizeof(consumidor_cafe_t));
	consumidor_3->numero_identificador = 300 ;
	consumidor_3->edad = 30 ;
	consumidor_3->sexo = 'F' ;
	gusto_cafe_t* cafe_consumidor_3 = (gusto_cafe_t*)malloc(sizeof(gusto_cafe_t));
	cafe_consumidor_3->tipo = variedad_cortado ;
	cafe_consumidor_3->azucar = false ;
	cafe_consumidor_3->sacarina = false ;
	cafe_consumidor_3->intensidad = intensidad_suave ;
	cafe_consumidor_3->tazas_por_dia = 3 ;
	consumidor_3->preferencia =cafe_consumidor_3 ;

	/*Cuarto dato*/
	consumidor_cafe_t* consumidor_4 = (consumidor_cafe_t*)malloc(sizeof(consumidor_cafe_t));
	consumidor_4->numero_identificador = 400 ;
	consumidor_4->edad = 27 ;
	consumidor_4->sexo = 'M' ;
	gusto_cafe_t* cafe_consumidor_4 = (gusto_cafe_t*)malloc(sizeof(gusto_cafe_t));
	cafe_consumidor_4->tipo = variedad_americano;
	cafe_consumidor_4->azucar = true ;
	cafe_consumidor_4->sacarina = false ;
	cafe_consumidor_4->intensidad = intensidad_suave ;
	cafe_consumidor_4->tazas_por_dia = 1 ;
	consumidor_4->preferencia = cafe_consumidor_4 ;

	/*Quinto dato*/
	consumidor_cafe_t* consumidor_5 = (consumidor_cafe_t*)malloc(sizeof(consumidor_cafe_t));
	consumidor_5->numero_identificador = 500 ;
	consumidor_5->edad = 42 ;
	consumidor_5->sexo = 'F' ;
	gusto_cafe_t* cafe_consumidor_5 = (gusto_cafe_t*)malloc(sizeof(gusto_cafe_t));
	cafe_consumidor_5->tipo = variedad_cafe_con_leche ;
	cafe_consumidor_5->azucar = false ;
	cafe_consumidor_5->sacarina = true ;
	cafe_consumidor_5->intensidad = intensidad_media ;
	cafe_consumidor_5->tazas_por_dia = 2 ;
	consumidor_5->preferencia =cafe_consumidor_5 ;

	printf("Insercion de los datos: \n\n") ;
	print_test("Insertar consumidor_2 al final",lista_insertar_ultimo(lista,consumidor_2));
	print_test("Insertar consumidor_3 al final", lista_insertar_ultimo(lista,consumidor_3));
	print_test("Insertar consumidor_4 al final", lista_insertar_ultimo(lista,consumidor_4));
	print_test("Insertar consumidor_5 al final", lista_insertar_ultimo(lista,consumidor_5));
	
	print_test("El largo de la lista es 4", lista_largo(lista) == 4) ;

	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Crear iterador", iter) ;

	consumidor_cafe_t* dato = (consumidor_cafe_t*)lista_iter_ver_actual(iter) ;
	print_test("El iterador esta al principio", dato->numero_identificador == *(int*)lista_ver_primero(lista)) ;

	/*Al insertar un elemento en la posición en la que se crea el iterador se inserta al principio.*/
	print_test("Insertar consumidor_1 al principio", lista_iter_insertar(iter, consumidor_1)) ;
	print_test("Consumidor_1 se inserto al principiio", consumidor_1->numero_identificador == *(int*)lista_ver_primero(lista)) ;
	
	dato = (consumidor_cafe_t*)lista_iter_borrar(iter) ;
	print_test("Eliminar consumidor_1 del principio", dato->numero_identificador == consumidor_1->numero_identificador) ;
	
	dato = (consumidor_cafe_t*)lista_ver_primero(lista) ;
	print_test("El principio de la lista es consumidor_2", dato->numero_identificador == consumidor_2->numero_identificador) ;
	print_test("El largo de la lista es 4", lista_largo(lista) == 4) ;
	
	dato = (consumidor_cafe_t*)lista_iter_ver_actual(iter) ;
	print_test("El iterador esta al principio", dato->numero_identificador == consumidor_2->numero_identificador) ;
	print_test("Insertar consumidor_4",lista_iter_insertar(iter,consumidor_4));
	
	dato = (consumidor_cafe_t*)lista_ver_primero(lista) ;
	print_test("El primer elemento de la lista es consumidor_4", dato->numero_identificador == consumidor_4->numero_identificador);
	print_test("El iterador esta al principio", dato->numero_identificador == consumidor_4->numero_identificador) ;
	print_test("Avanza el iterador", lista_iter_avanzar(iter) );

	dato = (consumidor_cafe_t*)lista_iter_ver_actual(iter) ;
	print_test("El iterador esta sobre consumidor_2", dato->numero_identificador == consumidor_2->numero_identificador);
	lista_iter_avanzar(iter) ;
	lista_iter_avanzar(iter) ;
	
	dato = (consumidor_cafe_t*)lista_iter_ver_actual(iter) ;
	print_test("El iterador esta sobre consumidor_4", dato->numero_identificador == consumidor_4->numero_identificador);
	print_test("Se inserta consumidor_5 en la posicion 3", lista_iter_insertar(iter, consumidor_5)) ;
	
	print_test("El largo de la lista es 6", lista_largo(lista) == 6) ;
	
	lista_iter_avanzar(iter) ;
	dato = (consumidor_cafe_t*)lista_iter_borrar(iter) ;
	print_test("Eliminar consumidor_4 de la posicion 4", dato->numero_identificador == consumidor_4->numero_identificador) ;
	
	dato = (consumidor_cafe_t*)lista_iter_borrar(iter) ;
	print_test("Eliminar consumidor_5 de la posicion 4", dato->numero_identificador == consumidor_5->numero_identificador) ;
	
	print_test("El iterador esta al final de la lista", lista_iter_al_final(iter));

	/*Insertar un elemento cuando el iterador está al final es insertar al final.*/
	print_test("Se inserta consumidor_1 al final de la lista", lista_iter_insertar(iter, consumidor_1)) ;
	print_test("Consumidor_1 se inserto al final", consumidor_1->numero_identificador == *(int*)lista_ver_ultimo(lista)) ;
	

	print_test("El largo de la lista es 5", lista_largo(lista) == 5) ;

	lista_iter_destruir(iter) ;

	lista_destruir(lista, destruir_consumidor);
	print_test("La lista y el iterador han sido destruidos", true) ;
}

void pruebas_iter_interno(){

	printf("\n\nPRUEBAS LISTA ITERADOR INTERNO \n\n");
	lista_t* lista = lista_crear() ;

	int vec[5] ;

	for(int i = 0 ; i < 5 ; i++)
		vec[i] = i ;
	
	bool ok = true ;

	for(int j = 0 ; j < 5 && ok ; j++){
		ok &= lista_insertar_ultimo(lista, &vec[j]) ;
	}
	print_test("La carga se ha completado", ok) ;
	int factor = 2 ;
	void* extra = &factor ;
	printf("antes de multiplicar \n") ;
	lista_iterar(lista, imprimir, NULL);
	printf("\n") ;
	lista_iterar(lista, multiplicar, extra);
	printf("despues de multiplicar \n") ;
	lista_iterar(lista, imprimir, NULL);

	lista_destruir(lista, NULL) ;
}

bool multiplicar(void* dato, void* extra){
	if(!dato || !extra)
		return false ;
	*(int*)dato = *(int*)dato * (*(int*)extra) ;
	return true ;
}

bool imprimir(void* dato , void*extra){
	if(!dato)
		return false ;
	printf("%d \t", *(int*)dato) ;
	return true ;
}

void pruebas_iter_interno_corte(){

	printf("\n\nPRUEBAS LISTA ITERADOR INTERNO CON CORTE \n\n");
	lista_t* lista = lista_crear() ;

	int vec[5] ;

	for(int i = 0 ; i < 5 ; i++)
		vec[i] = i ;
	
	bool ok = true ;

	for(int j = 0 ; j < 5 && ok ; j++){
		ok &= lista_insertar_ultimo(lista, &vec[j]) ;
	}
	print_test("La carga se ha completado", ok) ;
	int maximo = 1 ;
	void* extra = &maximo;
	lista_iterar(lista, es_menor, extra);

	if(*(int*)extra == -1)
		printf("La iteracion se detuvo por corte \n") ;
	else
		printf("Se iteró toda la lista \n") ;

	lista_destruir(lista, NULL) ;
}

bool es_menor(void* dato, void* extra){
	if(*(int*)dato > *(int*)extra){
		*(int*)extra = -1 ;
		return false ;
	}
	return true ;
}

void pruebas_funcionamiento_iterador(){
	printf("\n\npruebas iterador errores \n\n");
	lista_t* lista = lista_crear() ;

	int valores[10] ;
	for(int i=0 ; i <10; i++)
		valores[i] = i ;

	print_test("lista largo es cero", lista_largo(lista) == 0);

	for(int i = 0 ; i < 10 ; i++){
		lista_insertar_primero(lista, &valores[i]) ;
	}

	printf("largo = %d \n", (int)lista_largo(lista)) ;

	lista_iter_t* iter = lista_iter_crear(lista) ;

	print_test("Prueba iter no esta al final", lista_iter_al_final(iter) == false) ;
	print_test("Prueba iter ver actual no es NULL", lista_iter_ver_actual(iter) != NULL ) ;
	lista_iter_insertar(iter, &valores[0]) ;
	print_test("Prueba iter insertar inserta en la primera posicion", valores[0] == *(int*)lista_ver_primero(lista)) ;

	for(int i = 0 ; i < 4 ; i++)
		lista_iter_avanzar(iter) ;

	print_test("Ver actual es 6", valores[6] == *(int*)lista_iter_ver_actual(iter)) ;
	
	lista_iter_insertar(iter, &valores[0]) ;
	lista_iter_t* iter_2 = lista_iter_crear(lista) ;
	for(int i = 0 ; i < 4 ; i++){
		lista_iter_avanzar(iter_2) ;
	}
	print_test("Hay un cero en la posicion 4 de la lista", valores[0] == *(int*)lista_iter_ver_actual(iter_2) );
	print_test("Iter actual es cero", *(int*)lista_iter_ver_actual(iter) == valores[0]) ;
	lista_iter_destruir(iter_2) ;

	lista_iter_avanzar(iter) ;
	printf("avanza el iterador /n") ;
	print_test(" Iter actual es seis", *(int*)lista_iter_ver_actual(iter) == valores[6]) ;
	int* dato = (int*)lista_iter_borrar(iter);
	print_test("Se borro un seis de la posicion 5 de la lista", *dato == valores[6]) ;

	lista_iter_t* iter_3 = lista_iter_crear(lista) ;
	for(int i = 0 ; i < 5 ; i++){
		lista_iter_avanzar(iter_3) ;
	}

	print_test("Hay un cinco en la posicion cinco de la lista", valores[5] == *(int*)lista_iter_ver_actual(iter_3)) ;
	print_test("Iter actual es cinco", *(int*)lista_iter_ver_actual(iter) == valores[5]) ;
	lista_iter_destruir(iter_3) ;

	bool continuar = true ;
	while (continuar)
		continuar = lista_iter_avanzar(iter) ;
	
	print_test("Iter esta al final", lista_iter_al_final(iter) ) ;
	int valor = 150 ;
	lista_iter_insertar(iter, &valor) ;
	print_test("iter insertar inserta al final", valor == *(int*)lista_ver_ultimo(lista));
	dato = (int*)lista_iter_borrar(iter) ;
	print_test("iter_borrar borro un 150 que era el ultimo elemento de la lista", *dato == valor);
	print_test("El ultimo de la lista es cero", *(int*)lista_ver_ultimo(lista) == valores[0]);
	print_test("El iterador esta al final", lista_iter_al_final(iter)) ;
	print_test("Avanzar con el iterador es falso", !lista_iter_avanzar(iter)) ;

	lista_iter_destruir(iter) ;
	lista_destruir(lista, NULL) ;
}

void pruebas_lista_alumno(void){
	pruebas_lista_vacia() ;
	pruebas_lista_algunos_elementos() ;
	pruebas_funcionamiento_lista() ;
	pruebas_iter_interno() ;
	pruebas_iter_interno_corte() ;
	pruebas_funcionamiento_iterador() ;
}

