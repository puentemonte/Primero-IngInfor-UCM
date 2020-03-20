#pragma once
#include "mina.h"
using namespace std;

enum tTecla{IZDA, DCHA, ARRIBA, ABAJO, SALIR};
enum tEstado{EXPLORANDO, EXITO, ABANDONO, FRACASO};
typedef struct {
	tMina mina;
	int gemasRecogidas, numMovimientos, escala, introMovimientos;
	tEstado estadoMinero;
}tJuego;

/*
lee del flujo de entrada movimientos un movimiento y devuelve el valor del tipo enumerado correspondiente
1.std::istream& operator<< (std::istream & movimientos, tTecla& tecla);

lee un movimiento del fichero con la sobrecarga del operador.
Si el minero selecciona el movimiento SALIR pondrá el estado del minero en situación de ABANDONO.
2.void leerMovimiento(tJuego & juego, tTecla& tecla, std::istream & movimientos);

se encarga de realizar el movimientoindicado en el parémetro mov modificando el plano de la mina 
y la posición del minero en la mina. Para obtener la casilla de destino se ayudará del vector tdirs4, 
de forma que no tiene que diferenciar el movimiento realizado
3.void realizarMovimiento (tJuego & juego, tTecla mov);

manda dibujar el plano de la mina a la escala que tiene guardada en las opciones del juego
.4.void dibujar(tJuego const& juego);

comienza cargando los datos de la mina, a continuación va leyendo los movimientos y 
para cada uno modificala mina de acuerdo con el movimiento.
Los movimientos no los almacena, los trata según los va leyendo.
La función debe recibir los dos flujos de entrada, porque en fases posteriores del desarrollo 
de la práctica será necesario tenerlos diferenciados
5.void jugar(tJuego& juego, std::istream& entrada, std::istream & movimientos);
*/