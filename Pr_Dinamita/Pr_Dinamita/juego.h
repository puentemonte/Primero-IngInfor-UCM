// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
#pragma once
#include "mina.h"
using namespace std;

typedef enum tTecla { ARRIBA, ABAJO, DCHA, IZDA, SALIR, TNT };
typedef enum tEstado { EXPLORANDO, EXITO, ABANDONO, FRACASO };
typedef struct {
	tMina mina;
	int gemasRecogidas = 0, numMovimientos = 0, escala, introMovimientos, dinamitasUsadas = 0;
	tEstado estadoMinero;
}tJuego;

void lanzamientoDinamita(tJuego& juego);

//lee un movimiento y devuelve el valor del tipo enumerado correspondiente
istream& operator>> (istream& movimientos, tTecla& tecla);

//lee un movimiento del fichero con la sobrecarga del operador
//si el minero selecciona el movimiento SALIR pondr� el estado del minero en situaci�n de ABANDONO
void leerMovimiento(tJuego& juego, tTecla& tecla, istream& movimientos);

//se encarga de realizar el movimiento indicado en el par�metro mov
//modificando el plano de la mina y la posici�n del minero en la mina
void realizarMovimiento(tJuego& juego, tTecla mov);

//manda dibujar el plano de la mina a la escala que tiene guardada en las opciones del juego
void dibujar(tJuego const& juego);

void jugar(tJuego& juego, istream& entrada, istream& movimientos);

void inicializar_mina(tMina& mina);

void caidaPiedra(tJuego& juego, int f, int c);