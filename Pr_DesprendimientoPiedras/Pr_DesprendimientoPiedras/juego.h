// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
#pragma once
#include "mina.h"
using namespace std;

typedef enum tTecla { ARRIBA, ABAJO, DCHA, IZDA, SALIR };
typedef enum tEstado { EXPLORANDO, EXITO, ABANDONO, FRACASO };
typedef struct {
	tMina mina;
	int gemasRecogidas = 0, numMovimientos = 0, escala, introMovimientos;
	tEstado estadoMinero;
}tJuego;

//lee un movimiento y devuelve el valor del tipo enumerado correspondiente
istream& operator>> (istream& movimientos, tTecla& tecla);

//lee un movimiento del fichero con la sobrecarga del operador
//si el minero selecciona el movimiento SALIR pondrá el estado del minero en situación de ABANDONO
void leerMovimiento(tJuego& juego, tTecla& tecla, istream& movimientos);

//se encarga de realizar el movimiento indicado en el parámetro mov
//modificando el plano de la mina y la posición del minero en la mina
void realizarMovimiento(tJuego& juego, tTecla mov);

//manda dibujar el plano de la mina a la escala que tiene guardada en las opciones del juego
void dibujar(tJuego const& juego);

void jugar(tJuego& juego, istream& entrada, istream& movimientos);

//pone LIBRE en la posición x y 
//pone PIEDRA en la siguiente posición
void caidaPiedra(tMina& mina, int x, int y);

//mientras en la posición actual haya una piedra y esté dentro del plano
//mientras la siguiente posición sea LIBRE y esté dentro del plano
//llama a la función caidaPiedra
void cascadaPiedra(tMina& mina, int x, int y);