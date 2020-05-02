#include "puntuaciones.h"

void destruir(tPuntuaciones& marcador) {
	// liberamos memoria eliminando el array din�mico
	delete[]marcador.array_clasificacion;
}

void aumentar_Capacidad(tPuntuaciones& marcador) {
	// creamos un puntero auxiliar y lo inicialiamos a null
	tPuntuacionJugador* aux = nullptr;
	// ese aux va a apuntar a un array con tama�o doble del array que ten�amos
	aux = new tPuntuacionJugador[2 * TAM_INICIAL];
	// ahora copiamos todos los elementos que hab�a en el array antiguo
	for (int i = 0; i < marcador.num_jugadores; ++i) {
		aux[i] = marcador.array_clasificacion[i];
	}
	// liberamos memoria
	delete[]marcador.array_clasificacion;
	// pasamos la informaci�n de aux al array de clasificaci�n
	marcador.array_clasificacion = aux;
	// aumentamos la capacidad por dos
	marcador.capacidad *= 2;
	// aux vuelve a apuntar a null
	aux = nullptr;
}

void inicializar_Marcador(tPuntuaciones& marcador) {

}