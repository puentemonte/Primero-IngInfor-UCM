#include "mina.h"
#include "juego.h"

int main() {

	ifstream archivo, movimientos;
	tJuego juego;
	int escala, introMovimientos;
	string nombreFicheroMovimientos;

	// si el jugador escoge la opción salir, el programa finaliza
	if (menuEscala(juego) == 3)
		return 0;
	if (menuMovimientos(juego, nombreFicheroMovimientos) == 0)
		return 0;

	if (!cargarJuego(juego, juego.nivel))
		cout << "El archivo no pudo ser abierto.\n";
	else
		dibujar(juego);

	movimientos.open(nombreFicheroMovimientos);

	while (juego.nivel < 5) {
		while (juego.estadoMinero != EXITO) {
			leerMovimiento(juego, movimientos);
			dibujar(juego);
		}
		system("cls");
		if (menuNivel(juego) == 0)
			return 0;
		cargarJuego(juego, juego.nivel);
		dibujar(juego);
	}
	
	movimientos.close();
	
}