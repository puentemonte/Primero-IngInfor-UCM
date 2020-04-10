// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Explorando la mina
#include "juego.h"

const int NUM_DIRECCIONES = 4;
const pair<int, int> tdirs4[NUM_DIRECCIONES] = { {-1,0},{1,0},{0,1},{0,-1} };

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
					//movemos la PIEDRA donde antes estaba LIBRE
					juego.mina.plano[destinoX + tdirs4[mov].first][destinoY + tdirs4[mov].second] = PIEDRA;
					//movemos MINERO donde antes estaba la PIEDRA
					juego.mina.plano[destinoX][destinoY] = MINERO;
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
	for (int i = juego.mina.fila; i >= 0; --i) {
		for (int j = juego.mina.col; j >= 0; --j) {
			if ((juego.mina.plano[i][j] == PIEDRA || juego.mina.plano[i][j] == GEMA)
				&& juego.mina.plano[i + 1][j] == LIBRE)
				caidaPiedra(juego, i, j);
		}
	}
}

void dibujar(tJuego const& juego) {
	if (juego.escala == 1)
		dibujar1_1(juego.mina);
	else
		dibujar3_1(juego.mina);
}

void inicializar_mina(tMina& mina) {
	mina.fila = -1;
	mina.col = -1;
	mina.filaMinero = -1;
	mina.colMinero = -1;
	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			mina.plano[i][j] = NADA;
		}
	}
}

void jugar(tJuego& juego, istream& entrada, istream& movimientos) {
	tTecla tecla;

	//inicializamos el juego
	inicializar_mina(juego.mina);
	//carga los datos de la mina
	cargar_mina(entrada, juego.mina);
	//va leyendo los movimientos
	//la función realizar movimientos está implementada dentro
	leerMovimiento(juego, tecla, movimientos);
	while (juego.estadoMinero != ABANDONO && juego.estadoMinero != EXITO) {
		leerMovimiento(juego, tecla, movimientos);
	}
}