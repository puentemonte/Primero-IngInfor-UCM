// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre problema: Vectores dinámicos
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

typedef struct {
	string nombre;
	int unidades;
}tObj;

void resolver() {

}

void visualizar(tObj* ptr, int tam) {
	for (int i = 0; i < tam; ++i) {
		cout << ptr[i].nombre << " " << ptr[i].unidades << endl;
	}
	cout << "---\n";
}

bool resuelveCaso() {
	int tam = 3, cont = 0;
	tObj* ptr = new tObj[tam];
	char n;
	cin.get(n);
	if (n == 'F')
		return false;
	// operaciones
	if (n == 'L')
		visualizar(ptr, tam);
	delete[]ptr;
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-17.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}