#include "mina.h"
#include "juego.h"

int main() {
	tJuego juego;

	while (jugar(juego));

	system("cls");
	cout << "GAME OVER";

	return 0;
	
}