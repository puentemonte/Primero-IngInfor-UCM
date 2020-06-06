// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Pr�ctica minero v2
#pragma once
#include "mina.h"
#include "puntuaciones.h"
const int ULTIMO_NIVEL = 5;
typedef enum { ARRIBA, ABAJO, DCHA, IZDA, SALIR, NADA, TNT } tTecla;
typedef enum { EXPLORANDO, EXITO, ABANDONO, FRACASO } tEstado;
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

// men� del juego
int menuEscala(tJuego& juego);
int menuMovimientos(tJuego& juego, ifstream& movimientos);
int menuNivel(tJuego& juego);

// leer tecla
tTecla leerTecla();
istream& operator>> (istream& movimientos, tTecla& tecla);
void leerMovimiento(tJuego& juego, ifstream& movimientos);

// carga el juego del nivel indicado
// inicializa el juego y carga la mina, y si la mina no se pudo cargar devuelve falso
bool cargarJuego(tJuego& juego, int nivel);

// muestra el estado del juego teniendo en cuenta la escala
// muestra el n�mero de gemas, movimientos y dinamitas usadas
void dibujar(const tJuego& juego);

// cada vez que el minero haga un movimiento cambia el estado de la mina y el n�mero de movimientos
// el n�mero de gemas y de dinamitas usadas tambi�n puede cambiar
// cualquier acci�n del minero cuenta como movimiento
void hacerMovimiento(tJuego& juego, tTecla tecla);

// hace que una o varias piedras/gemas se caigan desde la posici�n f, c
void caidaPiedra(tJuego& juego, int f, int c);

// hace que la dinamita caiga y explota
void lanzamientoDinamita(tJuego& juego);

// CAMBIOS SEGUNDA PARTE MINERO

// calcula la puntuacion de una mina con la f�rmula que se da
int puntos(const tJuego &juego);

// MEN�S PRINCIPALES
// men� en el que se pide al jugador elegir la mina que quiere jugar
int menuPartida(string& nombre);
// men� en el que se le pide al usuario su nombre
int menuJugador(tPuntuaciones& marcador, int& posicion);

// funci�n que gestiona un juego
void jugar(tJuego& juego, tPuntuaciones& marcador);