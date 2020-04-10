// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
/*
Explicaci�n:
A�adir dos funciones m�s al m�dulo de juego.cpp
Una de las funciones gestionar� la ca�da de una sola piedra o gema mientras el espacio que tenga debajo est� LIBRE
La otra permitir� realizar la ca�da de las piedras o gemas en cascada
Implementaci�n:
Mientras haya una PIEDRA en la posici�n actual y estemos dentro del plano
	Mientras la siguiente posici�n est� LIBRE y estemos dentro del plano
		Poner LIBRE en la posici�n actual
		Poner la PIEDRA en la siguiente fila (pero la misma columna)
*/
#include "mina.h"
#include "juego.h"

using namespace std;

void resuelveCaso() {
	tJuego juego;

	//lee los par�metros escala y entrada de movimientos
	cin >> juego.escala >> juego.introMovimientos;

	//llamada a la funci�n jugar
	jugar(juego, cin, cin);

	cout << "Movimientos: " << juego.numMovimientos << "\n";
	cout << "Gemas: " << juego.gemasRecogidas << "\n";
	cout << "Dinamitas: " << juego.dinamitasUsadas << "\n";
	dibujar(juego);
	switch (juego.estadoMinero) {
	case EXITO:
		cout << "Mina recorrida\n";
		break;
	case ABANDONO:
		cout << "Pide rescate\n";
		break;
	case FRACASO:
		cout << "Le alcanzo la dinamita\n";
	}
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample-PR_04.2.in");
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