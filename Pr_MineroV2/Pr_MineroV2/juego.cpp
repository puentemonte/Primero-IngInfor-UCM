// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Práctica minero v2
#include "juego.h"
#include "puntuaciones.h"

const int NUM_DIRECCIONES = 4;
const int NUM_DIR_DINAMITA = 8;
const pair<int, int> tdirs4[NUM_DIRECCIONES] = { {-1,0},{1,0},{0,1},{0,-1} };
const pair<int, int> dirs8[NUM_DIR_DINAMITA] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

void lanzamientoDinamita(tJuego& juego) {
	// guardamos la posición del minero
	int f = juego.mina.filaMinero, c = juego.mina.columnaMinero;

	// el minero se explota la dinamita en la cara y muere
	if (juego.mina.plano[f + 1][c] != LIBRE) {
		juego.estadoMinero = FRACASO;
		juego.mina.plano[f][c] = LIBRE;
		for (int dir = 0; dir < 8; ++dir)
			if (dentroPlano(juego.mina, f + dirs8[dir].first, c + dirs8[dir].second))
				if (juego.mina.plano[f + dirs8[dir].first][c + dirs8[dir].second] != SALIDA)
					juego.mina.plano[f + dirs8[dir].first][c + dirs8[dir].second] = LIBRE;

	}

	else {
		// cae la dinamita
		while (juego.mina.plano[f + 1][c] == LIBRE && dentroPlano(juego.mina, f + 1, c)) {
			juego.mina.plano[f + 1][c] = DINAMITA;
			dibujar(juego);
			juego.mina.plano[f + 1][c] = LIBRE;
			dibujar(juego);
			++f;
		}
		for (int dir = 0; dir < 8; ++dir)
			if (dentroPlano(juego.mina, f + dirs8[dir].first, c + dirs8[dir].second)) {
				// comprobamos si el minero estaba en una posición adyacente
				if (juego.mina.plano[f + dirs8[dir].first][c + dirs8[dir].second] == MINERO)
					juego.estadoMinero = FRACASO;
				else if (juego.mina.plano[f + dirs8[dir].first][c + dirs8[dir].second] != SALIDA)
					juego.mina.plano[f + dirs8[dir].first][c + dirs8[dir].second] = LIBRE;
			}
	}
}

int menuEscala(tJuego& juego) {
	int opEscala;
	// primer menú
	cout << "----------\n";
	cout << "| ESCALA |\n";
	cout << "----------\n";
	cout << "1. Jugar partida a escala 1:1.\n";
	cout << "2. Jugar partida a escala 1:3.\n";
	cout << "3. Salir.\n";
	cin >> opEscala;
	while (opEscala < 1 || opEscala > 3 || !cin) {
		system("cls");
		cout << "----------\n";
		cout << "| ESCALA |\n";
		cout << "----------\n";
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

int menuMovimientos(tJuego& juego, ifstream& movimientos) {
	int opMovimientos;
	string ficheroMovimientos;
	// cerrar el txt anterior
	if (movimientos.is_open())
		movimientos.close();

	// segundo menú
	cout << "---------------\n";
	cout << "| MOVIMIENTOS |\n";
	cout << "---------------\n";
	cout << "1. Introducir movimientos por teclado.\n";
	cout << "2. Introducir movimientos por fichero.\n";
	cout << "0. Salir.\n";
	cin >> opMovimientos;
	while (opMovimientos < 0 || opMovimientos > 2 || !cin) {
		system("cls");
		cout << "---------------\n";
		cout << "| MOVIMIENTOS |\n";
		cout << "---------------\n";
		cout << "1. Introducir movimientos por teclado.\n";
		cout << "2. Introducir movimientos por fichero.\n";
		cout << "0. Salir.\n";
		cin >> opMovimientos;
	}
	system("cls");

	switch (opMovimientos) {
	case 1:
		juego.introMovimientos = 1;
		break;
	case 2:
		juego.introMovimientos = 2;
		system("cls");
		cout << "Introduzca el nombre del fichero de movimientos: ";
		cin.sync();
		cin >> ficheroMovimientos;
		movimientos.open(ficheroMovimientos);
		// si el usuario introduce un el nombre de un fichero que no existe
		if (!movimientos.is_open()) {
			while (!movimientos.is_open()) {
				system("cls");
				cout << "El fichero no existe, por favor intentalo de nuevo: ";
				cin.sync();
				cin >> ficheroMovimientos;
				movimientos.open(ficheroMovimientos);
			}
		}
		system("cls");
		break;
	case 0:
		break;
	}
	return opMovimientos;
}

int menuNivel(tJuego& juego) {
	int opNivel;
	// menú que aparece después de pasarse un nivel
	cout << "---------\n";
	cout << "| NIVEL |\n";
	cout << "---------\n";
	cout << "1. Jugar siguiente nivel.\n";
	cout << "0. Salir.\n";
	cin >> opNivel;
	while (opNivel < 0 || opNivel > 1 || !cin) {
		system("cls");
		cout << "---------\n";
		cout << "| NIVEL |\n";
		cout << "---------\n";
		cout << "1. Jugar siguiente nivel.\n";
		cout << "0. Salir.\n";
		cin >> opNivel;
	}
	system("cls");

	switch (opNivel) {
	case 1:
		++juego.nivel;
		break;
	case 0:
		break;
	}
	return opNivel;
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
	archivo.open(n + ".txt");
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
	cout << "-----------\n";
	cout << "| NIVEL " << juego.nivel << " |\n";
	cout << "-----------\n";
	cout << "Gemas totales recogidas: " << juego.gemasRecogidas << "\n";
	cout << "Numero de movimientos: " << juego.numMov << "\n";
	cout << "Dinamitas usadas: " << juego.numTnt << "\n";
}

void hacerMovimiento(tJuego& juego, tTecla mov) {
	//obtenemos la posición de destino del minero con el movimiento realizado
	int destinoX = juego.mina.filaMinero + tdirs4[mov].first;
	int destinoY = juego.mina.columnaMinero + tdirs4[mov].second;
	//inicializamos el estado del minero a EXPLORANDO
	juego.estadoMinero = EXPLORANDO;
	if (mov != TNT) {
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
				// comprobamos si quiere mover una piedra hacia arriba
				if (mov != ARRIBA) {
					//comprobamos si la dirección a la que apuntamos es una posición válida
					if (dentroPlano(juego.mina, destinoX + tdirs4[mov].first, destinoY + tdirs4[mov].second)) {
						//si la posición siguiente en el mismo sentido es LIBRE entonces mueve la PIEDRA
						if (juego.mina.plano[destinoX + tdirs4[mov].first][destinoY + tdirs4[mov].second] == LIBRE) {
							//la posición en la que estaba el minero queda libre
							juego.mina.plano[juego.mina.filaMinero][juego.mina.columnaMinero] = LIBRE;
							//actualizamos la información del minero
							juego.mina.filaMinero = destinoX;
							juego.mina.columnaMinero = destinoY;
							//movemos MINERO donde antes estaba la PIEDRA
							juego.mina.plano[destinoX][destinoY] = MINERO;
							//movemos la PIEDRA donde antes estaba LIBRE
							juego.mina.plano[destinoX + tdirs4[mov].first][destinoY + tdirs4[mov].second] = PIEDRA;
						}
					}
				}
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
	}
	if (mov == TNT) {
		lanzamientoDinamita(juego);
	}
	++juego.numMov;
	// recorremos el plano para ver si hay piedras o gemas que pueden caerse
	for (int i = juego.mina.nFilas - 1; i >= 0; --i) {
		for (int j = juego.mina.nColumnas - 1; j >= 0; --j) {
			if ((juego.mina.plano[i][j] == PIEDRA || juego.mina.plano[i][j] == GEMA)
				&& juego.mina.plano[i + 1][j] == LIBRE)
				caidaPiedra(juego, i, j);
		}
	}
}

void caidaPiedra(tJuego& juego, int f, int c) {
	int n = 0;
	// mientras la posición en la que estemos haya una piedra o una gema
	// y estemos dentro del plano
	if (dentroPlano(juego.mina, f + n, c)) {
		while (juego.mina.plano[f + n][c] == PIEDRA || juego.mina.plano[f + n][c] == GEMA) {
			// mientras la siguiente posición (la de abajo) esté libre
			// y estemos dentro del plano
			n = 0;
			if (dentroPlano(juego.mina, f + n + 1, c)) {
				while (juego.mina.plano[f + n + 1][c] == LIBRE) {
					// ponemos una posición más abajo la piedra/gema
					juego.mina.plano[f + n + 1][c] = juego.mina.plano[f + n][c];
					// ponemos libre la posición actual
					juego.mina.plano[f + n][c] = LIBRE;
					dibujar(juego);
					++n;
				}
			}
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
		break;
	case 'D':
		tecla = TNT;
	}
	return movimientos;
}

void leerMovimiento(tJuego& juego, ifstream& movimientos) {
	tTecla tecla;
	switch (juego.introMovimientos) {
	case 1:
		switch (leerTecla()) {
		case ARRIBA:
			hacerMovimiento(juego, ARRIBA);
			break;
		case ABAJO:
			hacerMovimiento(juego, ABAJO);
			break;
		case DCHA:
			hacerMovimiento(juego, DCHA);
			break;
		case IZDA:
			hacerMovimiento(juego, IZDA);
			break;
		case TNT:
			hacerMovimiento(juego, TNT);
			++juego.numTnt;
			break;
		case NADA:
			break;
		case SALIR:
			juego.estadoMinero = ABANDONO;
		}
		break;
	case 2:
		movimientos >> tecla;
		if (!movimientos) {
			juego.estadoMinero = FRACASO;
			break;
		}
		switch (tecla) {
		case ARRIBA:
			hacerMovimiento(juego, ARRIBA);
			break;
		case ABAJO:
			hacerMovimiento(juego, ABAJO);
			break;
		case DCHA:
			hacerMovimiento(juego, DCHA);
			break;
		case IZDA:
			hacerMovimiento(juego, IZDA);
			break;
		case TNT:
			hacerMovimiento(juego, TNT);
			++juego.numTnt;
			break;
		case NADA:
			break;
		case SALIR:
			juego.estadoMinero = ABANDONO;
		}
	}
}

//CAMBIOS SEGUNDA PARTE MINERO

int menuPartida(string& nombre) {
	int opcion;
	cout << nombre << ", ¿Que mina quieres explorar?\n";
	cout << "Introduce un número entre 1 y 5 para explorar una mina y 0 para salir\n";
	cin >> opcion;
	// Hay que volver a pedirle al usuario el nivel si no lo ha puesto correctamente
	while (!cin || opcion > 5 || opcion < 0) {
		cout << "Introduce un número entre 1 y 5 para explorar una mina y 0 para salir\n";
		cin >> opcion;
	}
	return opcion;
}

int menuJugador(tPuntuaciones& marcador, int& posicion) {
	cout << "SEGUNDA PARTE PRACTICA MINERO\n";
	string nombre;
	// devolvemos nivel
	int pos, opcion, nivel;
	cout << "Introduce tu nombre de jugador/a: ";
	cin >> nombre;

	if (buscar(nombre, marcador, pos)) {
		cout << "Ya estas registrado.\n";
		cout << "Mira las minas que has recorrido\n";
		mostrar_Minas_Usuario(marcador, pos);
	}
	else {
		cout << "Eres nuevo/a: " << nombre << "\n";
		insertar(marcador, nombre, pos);
		mostrar_Alfabetico(marcador);
	}
	// devolvemos por parámetro la posición del jugador
	posicion = pos;
	nivel = menuPartida(nombre);
	system("cls");
	return nivel;
}

int puntos(const tJuego &juego) {
	return juego.mina.nFilas * juego.mina.nColumnas + A * juego.gemasRecogidas - juego.numMov - B * juego.numTnt;
}

void jugar(tJuego& juego, tPuntuaciones& marcador) {
	ifstream archivo, movimientos;
	int escala, introMovimientos, pos_jugador, pos_mina = 0;

	// inicializamos marcador
	inicializar_Marcador(marcador);
	// cargamos desde puntuaciones.txt
	cargar_Marcador(marcador);

	// mostramos el menú principal donde el jugador se registra
	juego.nivel = menuJugador(marcador, pos_jugador);
	system("cls");
	// si el jugador escoge la opción salir, el programa finaliza
	while (juego.nivel != 0) {
		// primero mostramos los menús para que el jugador escoja las opciones de juego
		if (menuEscala(juego) == 3)
			juego.nivel = 0;
		else
		{
			if (menuMovimientos(juego, movimientos) == 0)
				juego.nivel = 0;
			else
			{
				// cargamos el nivel que haya escogido
				if (!cargarJuego(juego, juego.nivel))
					cout << "El archivo no pudo ser abierto.\n";
				else
					dibujar(juego);

				// mientras el minero siga explorando la mina tenemos que dibujar y leer los movimientos
				while (juego.estadoMinero == EXPLORANDO) {
					dibujar(juego);
					leerMovimiento(juego, movimientos);
				}

				// dependiendo de cómo haya terminado la partida, debemos cambiar las puntuaciones del marcador
				switch (juego.estadoMinero) {
				case EXITO:
					system("cls");
					// primero buscamos la mina
					if (!buscarMina(marcador, pos_mina, juego.nivel, pos_jugador)) {
						// aumentamos las minas recorridas si no la ha encontrado
						++marcador.array_clasificacion[pos_jugador].minasRecorridas;
						// si no ha encontrado la mina, la insertamos ordenadamente
						for (int i = marcador.array_clasificacion[pos_jugador].minasRecorridas - 1; i > pos_mina; --i)
							marcador.array_clasificacion[pos_jugador].vMinasRecorridas[i] =
							marcador.array_clasificacion[pos_jugador].vMinasRecorridas[i - 1];
					}
					else
						// si ha encontrado el nivel y tiene éxito entonces hay que restar del total
						// la puntuación de la mina recorrida ya que es la puntuación anterior
						marcador.array_clasificacion[pos_jugador].punt_total -=
						marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].ptosMina; 
					// independientemente de si ha encontrado la mina o no hay que actualizar los datos
					marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].numDinamitas = juego.numTnt;
					marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].numGemas = juego.gemasRecogidas;
					marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].numMovimientos = juego.numMov;
					marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].idMina = juego.nivel;
					// ahora utilizamos la fórmula para calcular los puntos de esta mina
					marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].ptosMina = puntos(juego);
					// para finalizar a la puntuación que ya teníamos antes le sumamos la nueva puntuación
					marcador.array_clasificacion[pos_jugador].punt_total +=
						marcador.array_clasificacion[pos_jugador].vMinasRecorridas[pos_mina].ptosMina;
					break;
				// en caso de no haber terminado la mina exitosamente, el jugador se encontrará un triste mensaje
				case ABANDONO:
				case FRACASO:
					system("cls");
					cout << "----------------\n";
					cout << "| GAME OVER :( |\n";
					cout << "----------------\n";
					system("PAUSE");
					break;
				}
				// para cerrar el flujo del nivel en caso de haber elegido los movimientos por fichero
				//movimientos.close();

				// limipiamos la consola y mostramos el menú para que elija si quiere jugar otro nivel o salir
				system("cls");
				mostrar_Datos_Usuario(marcador);
				juego.nivel = menuPartida(marcador.array_clasificacion[pos_jugador].nombre);
				system("cls");
			}

		}
	}
	// finalmente guardamos todos los datos en puntuaciones.txt
	guardar_Marcador(marcador);
	// delete array dinámico
	destruir(marcador);
}