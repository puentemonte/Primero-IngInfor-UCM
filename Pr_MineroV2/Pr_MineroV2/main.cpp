// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Pr�ctica minero v2
#include "juego.h"
#include "puntuaciones.h"

int main() {
	tJuego juego;
	tPuntuaciones marcador;
	
	// el jugador elegir� cuando salir del juego
	jugar(juego, marcador);

	system("cls");
	cout << "-----------------\n";
	cout << "| HASTA OTRA :) |\n";
	cout << "-----------------\n";
	system("PAUSE");

	return 0;
}