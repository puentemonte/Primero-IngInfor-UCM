#include "puntuaciones.h"

void mostrar_Datos_Usuario(const tPuntuaciones& marcador) {
	cout << "---JUGADORES ORDENADOS POR NOMBRE---\n";
	for (int i = 0; i < marcador.num_jugadores; ++i)
		mostrar_Minas_Usuario(marcador, i);
	system("PAUSE");
}

void mostrar_Alfabetico(const tPuntuaciones& marcador) {
	cout << "---LISTA DE JUGADORES---\n";
	//el array ya está ordenado así que solo hay que sacar por pantalla la información
	for (int i = 0; i < marcador.num_jugadores; ++i)
		cout << marcador.array_clasificacion[i].nombre << " " << marcador.array_clasificacion[i].punt_total << "\n";
	system("PAUSE");
}

void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont) {
	cout << marcador.array_clasificacion[cont].nombre << setw(7) << "Movimientos" << setw(7)
		<< "Gemas" << setw(7) << "Dinamitas" << setw(7) << "Puntos" << setw(7) << "Puntos en total\n";
	for (int i = 0; i < marcador.array_clasificacion[cont].minasRecorridas; ++i) {
		cout << "Mina" << marcador.array_clasificacion[cont].vMinasRecorridas[i].idMina << setw(7)
			<< marcador.array_clasificacion[cont].vMinasRecorridas[i].numMovimientos << setw(7)
			<< marcador.array_clasificacion[cont].vMinasRecorridas[i].numGemas << setw(7)
			<< marcador.array_clasificacion[cont].vMinasRecorridas[i].numDinamitas << setw(7)
			<< marcador.array_clasificacion[cont].vMinasRecorridas[i].ptosMina << setw(7)
			<< marcador.array_clasificacion[cont].punt_total << "\n";

	}
	cout << "\n";
}

bool guardar_Marcador(tPuntuaciones& marcador) {
	ofstream archivo;
	bool ok = false;
	archivo.open("Puntuaciones.txt");
	if (!archivo.is_open())
		ok = false;
	else {
		ok = true;
		for (int i = 0; i < marcador.num_jugadores; ++i) {
			archivo << marcador.array_clasificacion[i].nombre << "\n"
				<< marcador.array_clasificacion[i].punt_total << "\n"
				<< marcador.array_clasificacion[i].minasRecorridas << "\n";
			for(int j = 0; j < marcador.array_clasificacion[i].minasRecorridas; ++j) {
				// solo volcamos los datos de las minas que han sido recorridas, es decir, numMovimientos != 0
				if (marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos != 0) {
					archivo << marcador.array_clasificacion[i].vMinasRecorridas[j].idMina << " "
						<< marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos << " "
						<< marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas << " "
						<< marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas << " "
						<< marcador.array_clasificacion[i].vMinasRecorridas[j].ptosMina << "\n";
				}
			}
		}
	}
	archivo.close();
	return ok;
}

bool cargar_Marcador(tPuntuaciones& marcador) {
	ifstream archivo;
	bool ok = false;
	archivo.open("Puntuaciones.txt");
	if (!archivo.is_open())
		// si el archivo no se ha podido abrir, se devuelve false
		ok = false;
	else {
		ok = true;
		// leemos el primer nombre
		getline(archivo, marcador.array_clasificacion[marcador.num_jugadores].nombre);
		while (marcador.array_clasificacion[marcador.num_jugadores].nombre != "000") {
			// añadimos un jugador al array
			archivo >> marcador.array_clasificacion[marcador.num_jugadores].punt_total
				>> marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas;
			// por cada mina recorrida se recoge la misma info
			for (int i = 0; i < marcador.array_clasificacion[marcador.num_jugadores].minasRecorridas; ++i) {
				//leemos las minas según están en el archivo
				archivo >> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].idMina
					>> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].idMina
					>> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].numMovimientos
					>> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].numGemas
					>> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].numDinamitas
					>> marcador.array_clasificacion[marcador.num_jugadores].vMinasRecorridas[i].ptosMina;
			}
			// aumentamos el número de jugadores
			++marcador.num_jugadores;
			// comprobamos si está lleno el array
			if (marcador.num_jugadores == marcador.capacidad)
				aumentar_Capacidad(marcador);
			// leemos el siguiente nombre
			getline(archivo, marcador.array_clasificacion[marcador.num_jugadores].nombre);
		}
	}
	archivo.close();
	return ok;
}

void destruir(tPuntuaciones& marcador) {
	// liberamos memoria eliminando el array dinámico
	delete[]marcador.array_clasificacion;
}

void aumentar_Capacidad(tPuntuaciones& marcador) {
	// creamos un puntero auxiliar y lo inicialiamos a null
	tPuntuacionJugador* aux = nullptr;
	// ese aux va a apuntar a un array con tamaño doble del array que teníamos
	aux = new tPuntuacionJugador[2 * TAM_INICIAL];
	// ahora copiamos todos los elementos que había en el array antiguo
	for (int i = 0; i < marcador.num_jugadores; ++i) {
		aux[i] = marcador.array_clasificacion[i];
	}
	// liberamos memoria
	delete[]marcador.array_clasificacion;
	// pasamos la información de aux al array de clasificación
	marcador.array_clasificacion = aux;
	// aumentamos la capacidad por dos
	marcador.capacidad *= 2;
	// aux vuelve a apuntar a null
	aux = nullptr;
}

void inicializar_Marcador(tPuntuaciones& marcador) {
	// la capacidad inicial es 2
	marcador.capacidad = TAM_INICIAL;
	// el número de jugadores es igual a 0
	marcador.num_jugadores = 0;
	// el puntero apunta al array en el montón de tipo tPuntuaciónJugador
	marcador.array_clasificacion = new tPuntuacionJugador[TAM_INICIAL];
}

bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos) {
	// utilizamos la búsqueda binaria iterativa
	int ini = 0, fin = marcador.num_jugadores - 1, mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (nombre == marcador.array_clasificacion[mitad].nombre)
			encontrado = true;
		else if (nombre < marcador.array_clasificacion[mitad].nombre)
			fin = mitad - 1;
		else
			ini = mitad + 1;
	}
	if (encontrado)
		pos = mitad;
	else
		// si no lo ha encontrado debería ir en ini
		pos = ini;
	return encontrado;
}

void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {
	// comprobar si hay espacio en el array
	if (marcador.num_jugadores == marcador.capacidad)
		aumentar_Capacidad(marcador);
	// hacemos hueco para el nuevo jugador
	// movemos una posición a la derecha todos los elementos
	for (int i = marcador.num_jugadores - 1; i > pos; --i)
		marcador.array_clasificacion[i] = marcador.array_clasificacion[i + 1];
	// insertamos en pos el nuevo nombre
	marcador.array_clasificacion[pos].nombre = nombre;
	// ahora hay un jugador más
	++marcador.num_jugadores;
}