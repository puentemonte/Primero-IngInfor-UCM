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
int menuMovimientos(tJuego& juego, string& ficheroMovimientos);
int menuNivel(tJuego& juego);

//leer tecla
tTecla leerTecla();
istream& operator>> (istream& movimientos, tTecla& tecla);
void leerMovimiento(tJuego& juego, ifstream& movimientos);

//carga el juego del nivel indicado
//inicializa el juego y carga la mina, y si la mina no se pudo cargar devuelve falso
bool cargarJuego(tJuego& juego, int nivel);

//muestra el estado del juego teniendo en cuenta la escala
//muestra el número de gemas, movimientos y dinamitas usadas
void dibujar(const tJuego& juego);

//cada vez que el minero haga un movimiento cambia el estado de la mina y el número de movimientos
//el número de gemas y de dinamitas usadas también puede cambiar
//cualquier acción del minero cuenta como movimiento
void hacerMovimiento(tJuego& juego, tTecla tecla);

// hace que una o varias piedras/gemas se caigan desde la posición f, c
void caidaPiedra(tJuego& juego, int f, int c);

//hace que la dinamita caiga y explota
void lanzamientoDinamita(tJuego& juego);

// función que gestiona un juego
bool jugar(tJuego& juego);