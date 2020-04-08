// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Explorando la mina
#include "mina.h"
#include "juego.h"

using namespace std;

void resuelveCaso() {
	tJuego juego;
	//inicializamos el número de movimientos y de gemas recogidas
	juego.numMovimientos = 0;
	juego.gemasRecogidas = 0;

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
	std::ifstream in("sample-PR_02.in");
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