// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
/*
Explicación:
Añadir dos funciones más al módulo de juego.cpp
Una de las funciones gestionará la caída de una sola piedra o gema mientras el espacio que tenga debajo esté LIBRE
La otra permitirá realizar la caída de las piedras o gemas en cascada
Implementación:
Mientras haya una PIEDRA en la posición actual y estemos dentro del plano
	Mientras la siguiente posición esté LIBRE y estemos dentro del plano
		Poner LIBRE en la posición actual
		Poner la PIEDRA en la siguiente fila (pero la misma columna)
*/
#include "mina.h"
#include "juego.h"

using namespace std;

void resuelveCaso() {
	tJuego juego;

	//lee los parámetros escala y entrada de movimientos
	cin >> juego.escala >> juego.introMovimientos;

	//llamada a la función jugar
	jugar(juego, cin, cin);

	cout << "Movimientos: " << juego.numMovimientos << "\n";
	cout << "Gemas: " << juego.gemasRecogidas << "\n";
	dibujar(juego);
	if (juego.estadoMinero == EXITO)
		cout << "Mina recorrida\n";
	else
		cout << "Pide rescate\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample-PR_03.2.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}