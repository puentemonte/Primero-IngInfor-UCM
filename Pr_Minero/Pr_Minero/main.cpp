// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Práctica minero V1
#include "mina.h"
#include "juego.h"

int main() {
	tJuego juego;
	// el juego se ejecutara hasta que:
	// el jugador siga pasando de nivel
	// no muera por la dinamita
	// se pase el nivel 4
	while (jugar(juego));

	system("cls");
	if (juego.estadoMinero == FRACASO) {
		cout << "----------------\n";
		cout << "| GAME OVER :( |\n";
		cout << "----------------\n";
	}
	if (juego.estadoMinero == EXITO) {
		cout << "-----------------\n";
		cout << "| HASTA OTRA :) |\n";
		cout << "-----------------\n";
	}
	system("PAUSE");

	return 0;
	
}