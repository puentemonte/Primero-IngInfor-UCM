#pragma once
#include "mina.h"
typedef enum tTecla { ARRIBA, ABAJO, DCHA, IZDA, SALIR, NADA, TNT };
typedef enum tEstado {EXPLORANDO, EXITO, ABANDONO, FRACASO};
typedef struct {
	tMina mina;
	tEstado estadoMinero = EXPLORANDO;
	int gemasRecogidas = 0,
		nivel = 1,
		numMov = 0,
		numTnt = 0,
		escala = 1,
		introMovimientos = 1;
}tJuego;

//menu del juego
int menuEscala(tJuego& juego);
int menuMovimientos(tJuego& juego);

//leer tecla desde el teclado
tTecla leerTecla();

//carga el juego del nivel indicado
//inicializa el juego y carga la mina, y si la mina no se pudo cargar devuelve falso
bool cargarJuego(tJuego& juego, int nivel);

//muestra el estado del juego teniendo en cuenta la escala
//muestra el n�mero de gemas, movimientos y dinamitas usadas
void dibujar(const tJuego& juego);

//cada vez que el minero haga un movimiento cambia el estado de la mina y el n�mero de movimientos
//el n�mero de gemas y de dinamitas usadas tambi�n puede cambiar
//cualquier acci�n del minero cuenta como movimiento
void hacerMovimiento(tJuego& juego, tTecla tecla);

// hace que una o varias piedras/gemas se caigan desde la posici�n f, c
void caidaPiedra(tJuego& juego, int f, int c);

//hace que la dinamita caiga y explota
//devuelve true si el minero muere
bool caidaDinamita(tJuego& juego);