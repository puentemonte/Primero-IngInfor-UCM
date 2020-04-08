// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
/*
Implementación de la solución:
Mientras haya una PIEDRA en la posición actual y estemos dentro del plano
	Mientras la siguiente posición esté LIBRE y estemos dentro del plano
		Poner LIBRE en la posición actual
		Poner la PIEDRA en la siguiente fila (pero la misma columna)
*/
#include "juego.h"
using namespace std;

const int NUM_DIRECCIONES = 4;
const pair<int, int> tdirs4[NUM_DIRECCIONES] = { {-1,0},{1,0},{0,1},{0,-1} };

void caidaPiedra(tMina& mina, int x, int y, tElemento ELEMENTO) {
	
	mina.plano[x][y] = LIBRE;
	mina.plano[x + 1][y] = ELEMENTO;

}

void cascadaPiedra(tMina& mina, int x, int y) {

	while ((mina.plano[x][y] == PIEDRA || mina.plano[x][y] == GEMA) && dentroPlano(mina, x, y)) {
		//x + 1 indicando la posición de abajo, en la que hay que comprobar si está libre
		while (mina.plano[x + 1][y] == LIBRE && dentroPlano(mina, x + 1, y)) {
			//comprobamos si lo que cae es una PIEDRA o una GEMA
			if (mina.plano[x][y] == PIEDRA)
				caidaPiedra(mina, x, y, PIEDRA);
			else
				caidaPiedra(mina, x, y, GEMA);
		}
	}

}

istream& operator>> (istream& movimientos, tTecla& tecla) {
	char c;
	movimientos >> c;
	switch (c) {
	case 'A':
		tecla = ARRIBA;
		break;
	case 'Z':
		tecla = ABAJO;
		break;
	case 'N':
		tecla = IZDA;
		break;
	case 'M':
		tecla = DCHA;
		break;
	case 'S':
		tecla = SALIR;
	}
	return movimientos;
}

void leerMovimiento(tJuego& juego, tTecla& tecla, istream& movimientos) {
	movimientos >> tecla;
	switch (tecla) {
	case ARRIBA:
		realizarMovimiento(juego, ARRIBA);
		break;
	case ABAJO:
		realizarMovimiento(juego, ABAJO);
		break;
	case DCHA:
		realizarMovimiento(juego, DCHA);
		break;
	case IZDA:
		realizarMovimiento(juego, IZDA);
		break;
	case SALIR:
		juego.estadoMinero = ABANDONO;
	}
}

void realizarMovimiento(tJuego& juego, tTecla mov) {
	//obtenemos la posición de destino del minero con el movimiento realizado
	int destinoX = juego.mina.filaMinero + tdirs4[mov].first;
	int destinoY = juego.mina.colMinero + tdirs4[mov].second;
	//inicializamos el estado del minero a EXPLORANDO
	juego.estadoMinero = EXPLORANDO;

	if (dentroPlano(juego.mina, destinoX, destinoY)) {
		switch (juego.mina.plano[destinoX][destinoY]) {
		case LIBRE:
			// hace lo mismo que en TIERRA
		case TIERRA:
			//la posición en la que estaba el minero queda libre
			juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = LIBRE;
			//cambian las coordenadas del minero
			juego.mina.filaMinero = destinoX;
			juego.mina.colMinero = destinoY;
			//ahora el minero está en esas nuevas coordenadas
			juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = MINERO;
			break;
		case MURO:
			//la posición del minero no cambia y el plano de la mina tampoco
			break;
		case PIEDRA:
			//comprobamos si la dirección a la que apuntamos es una posición válida
			if (dentroPlano(juego.mina, destinoX + tdirs4[mov].first, destinoY + tdirs4[mov].second)) {
				//si la posición siguiente en el mismo sentido es LIBRE entonces mueve la PIEDRA
				if (juego.mina.plano[destinoX + tdirs4[mov].first][destinoY + tdirs4[mov].second] == LIBRE) {
					//la posición en la que estaba el minero queda libre
					juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = LIBRE;
					//actualizamos la información del minero
					juego.mina.filaMinero = destinoX;
					juego.mina.colMinero = destinoY;
					//movemos MINERO donde antes estaba la PIEDRA
					juego.mina.plano[destinoX][destinoY] = MINERO;
					//movemos la PIEDRA donde antes estaba LIBRE
					juego.mina.plano[destinoX + tdirs4[mov].first][destinoY + tdirs4[mov].second] = PIEDRA;
					//llamamos a la función cascada para que la piedra caiga
					cascadaPiedra(juego.mina, destinoX + tdirs4[mov].first, destinoY + tdirs4[mov].second);
				}
			}
			break;
		case GEMA:
			//la posición en la que estaba el minero queda libre
			juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = LIBRE;
			//cambian las coordenadas del minero
			juego.mina.filaMinero = destinoX;
			juego.mina.colMinero = destinoY;
			//ahora el minero está en esas nuevas coordenadas
			juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = MINERO;
			//aumentamos el número de movimientos realizados y las gemas recogidas
			++juego.gemasRecogidas;
			break;
		case SALIDA:
			//la posición en la que estaba el minero queda libre porque el minero ha salido de la mina
			juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = LIBRE;
			//cambian las coordenadas del minero
			juego.mina.filaMinero = destinoX;
			juego.mina.colMinero = destinoY;
			//ahora el minero está en esas nuevas coordenadas
			juego.mina.plano[juego.mina.filaMinero][juego.mina.colMinero] = MINERO;
			//actualizamos el estado del minero
			juego.estadoMinero = EXITO;
		case MINERO:
			// para el juez
			break;
		}
	}
	++juego.numMovimientos;
}

void dibujar(tJuego const& juego) {
	if (juego.escala == 1)
		dibujar1_1(juego.mina);
	else
		dibujar3_1(juego.mina);
}

void jugar(tJuego& juego, istream& entrada, istream& movimientos) {
	tTecla tecla;

	//carga los datos de la mina
	cargar_mina(entrada, juego.mina);
	//va leyendo los movimientos
	//la función realizar movimientos está implementada dentro
	leerMovimiento(juego, tecla, movimientos);
	while (juego.estadoMinero != ABANDONO && juego.estadoMinero != EXITO) {
		leerMovimiento(juego, tecla, movimientos);
	}
}