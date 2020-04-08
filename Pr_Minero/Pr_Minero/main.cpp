#include "mina.h"
#include "juego.h"

int main() {

	ifstream archivo;
	tJuego juego;
	int escala, introMovimientos;

	// si el jugador escoge la opción salir, el programa finaliza
	if (menuEscala(juego) == 3)
		return 0;
	if (menuMovimientos(juego) == 0)
		return 0;


	if (!cargarJuego(juego, juego.nivel))
		cout << "El archivo no pudo ser abierto.\n";
	else
		dibujar(juego);

	while (juego.nivel < 5) {
		while (juego.estadoMinero != EXITO) {
			hacerMovimiento(juego, leerTecla());
			dibujar(juego);
		}
		++juego.nivel;
		cargarJuego(juego, juego.nivel);
		dibujar(juego);
	}
	
	
}