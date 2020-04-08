#include "juego.h"

const int NUM_DIRECCIONES = 4;
const pair<int, int> tdirs4[NUM_DIRECCIONES] = { {-1,0},{1,0},{0,1},{0,-1} };

int menuEscala(tJuego& juego) {
	int opEscala;
	// primer menú
	cout << "1. Jugar partida a escala 1:1.\n";
	cout << "2. Jugar partida a escala 1:3.\n";
	cout << "3. Salir.\n";
	cin >> opEscala;
	while (opEscala < 1 || opEscala > 3 || !cin) {
		system("cls");
		cout << "1. Jugar partida a escala 1:1.\n";
		cout << "2. Jugar partida a escala 1:3.\n";
		cout << "3. Salir.\n";
		cin >> opEscala;
	}
	system("cls");
	switch (opEscala)
	{
	case 1:
		juego.escala = 1;
		break;
	case 2:
		juego.escala = 2;
		break;
	case 3:
		break;
	}
	return opEscala;
}

int menuMovimientos(tJuego& juego) {
	int opMovimientos;
	// segundo menú
	cout << "1. Introducir movimientos por teclado.\n";
	cout << "2. Introducir movimientos por fichero.\n";
	cout << "0. Salir.\n";
	cin >> opMovimientos;
	while (opMovimientos < 1 || opMovimientos > 3 || !cin) {
		system("cls");
		cout << "1. Introducir movimientos por teclado.\n";
		cout << "2. Introducir movimientos por fichero.\n";
		cout << "0. Salir.\n";
		cin >> opMovimientos;
	}
	system("cls");

	//para el nombre del fichero en caso de elegir la opción 2
	string nombreFichero;
	switch (opMovimientos)
	{
	case 1:
		juego.introMovimientos = 1;
		break;
	case 2:
		juego.introMovimientos = 2;
		break;
	case 3:
		opMovimientos = 0;
		break;
	}
	return opMovimientos;
}

tTecla leerTecla() {
	tTecla t;
	cin.sync();
	int dir = _getch();
	if (dir == 0xe0) {
		dir = _getch();
		switch (dir) {
		case 72:
			t = ARRIBA;
			break;
		case 80:
			t = ABAJO;
			break;
		case 77:
			t = DCHA;
			break;
		case 75:
			t = IZDA;
		}
	}
	else if (dir == 27)
		t = SALIR;
	else if (dir == 100)
		t = TNT;
	else
		t = NADA;

	return t;
}

bool cargarJuego(tJuego& juego, int nivel) {
	ifstream archivo;
	bool ok;
	string n = to_string(nivel);
	archivo.open( n + ".txt");
	if (!archivo.is_open())
		ok = false;
	else {
		ok = true;
		cargar_mina(archivo, juego.mina);
		juego.estadoMinero = EXPLORANDO;
	}
	archivo.close();
	return ok;
}

void dibujar(const tJuego& juego) {
	if (juego.escala == 1)
		dibujar1_1(juego.mina);
	else
		dibujar1_3(juego.mina);
	cout << "Gemas totales recogidas: " << juego.gemasRecogidas << "\n";
	cout << "Número de movimientos: " << juego.numMov << "\n";
	cout << "Dinamitas usadas: " << juego.numTnt << "\n";
}

void hacerMovimiento(tJuego& juego, tTecla tecla) {
	//obtenemos la posición de destino del minero con el movimiento realizado
	int destinoX = juego.mina.filaMinero + tdirs4[tecla].first;
	int destinoY = juego.mina.columnaMinero + tdirs4[tecla].second;

	if (dentroPlano(juego.mina, destinoX, destinoY)) {
		switch (juego.mina.plano[destinoX][destinoY]) {
		case LIBRE:
			// hace lo mismo que en TIERRA
		case TIERRA:
			//la posición en la que estaba el minero queda libre
			juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = LIBRE;
			//cambian las coordenadas del minero
			juego.mina.filaMinero = destinoX;
			juego.mina.columnaMinero = destinoY;
			//ahora el minero está en esas nuevas coordenadas
			juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = MINERO;
			break;
		case MURO:
			//la posición del minero no cambia y el plano de la mina tampoco
			break;
		case PIEDRA:
			//comprobamos si la dirección a la que apuntamos es una posición válida
			if (dentroPlano(juego.mina, destinoX + tdirs4[tecla].first, destinoY + tdirs4[tecla].second)) {
				//si la posición siguiente en el mismo sentido es LIBRE entonces mueve la PIEDRA
				if (juego.mina.plano[destinoX + tdirs4[tecla].first][destinoY + tdirs4[tecla].second] == LIBRE) {
					//la posición en la que estaba el minero queda libre
					juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = LIBRE;
					//actualizamos la información del minero
					juego.mina.filaMinero = destinoX;
					juego.mina.columnaMinero = destinoY;
					//movemos la PIEDRA donde antes estaba LIBRE
					juego.mina.plano[destinoX + tdirs4[tecla].first][destinoY + tdirs4[tecla].second] = PIEDRA;
					//movemos MINERO donde antes estaba la PIEDRA
					juego.mina.plano[destinoX][destinoY] = MINERO;
				}
			}
			// ahora que ya se ha movido la piedra hay que comprobar si cae por efecto de la gravedad
			caidaPiedra(juego, destinoX + tdirs4[tecla].first, destinoY + tdirs4[tecla].second);
			break;
		case GEMA:
			//la posición en la que estaba el minero queda libre
			juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = LIBRE;
			//cambian las coordenadas del minero
			juego.mina.filaMinero = destinoX;
			juego.mina.columnaMinero = destinoY;
			//ahora el minero está en esas nuevas coordenadas
			juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = MINERO;
			//aumentamos el número de movimientos realizados y las gemas recogidas
			++juego.gemasRecogidas;
			break;
		case SALIDA:
			//la posición en la que estaba el minero queda libre porque el minero ha salido de la mina
			juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = LIBRE;
			//cambian las coordenadas del minero
			juego.mina.filaMinero = destinoX;
			juego.mina.columnaMinero = destinoY;
			//ahora el minero está en esas nuevas coordenadas
			juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = MINERO;
			//actualizamos el estado del minero
			juego.estadoMinero = EXITO;
		case MINERO:
			// para el juez
			break;
		}
	}
	++juego.numMov;
}

void caidaPiedra(tJuego& juego, int f, int c) {
	// mientras la posición en la que estemos haya una piedra o una gema
	// y estemos dentro del plano
	while (juego.mina.plano[f][c] == PIEDRA && dentroPlano(juego.mina, f, c)) {
		// mientras la siguiente posición (la de abajo) esté libre
		// y estemos dentro del plano
		while (juego.mina.plano[f + 1][c] == LIBRE && dentroPlano(juego.mina, f + 1, c)) {
			// ponemos libre la posición actual
			juego.mina.plano[f][c] == LIBRE;
			// ponemos una posición más abajo la piedra/gema
			juego.mina.plano[f + 1][c] == PIEDRA;
			dibujar(juego);
		}
	}
}