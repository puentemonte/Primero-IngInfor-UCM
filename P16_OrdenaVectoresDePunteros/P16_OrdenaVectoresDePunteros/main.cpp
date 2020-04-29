// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre problema: Ordenación con vectores de punteros
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX = 50;
const int TAM = 200;
typedef struct {
	string titulo, tema;
	int tMatriz[MAX][MAX];
}tFoto;

typedef tFoto* tPtrFoto;
typedef tPtrFoto tPunteros[TAM];

void ordenarPorTitulo(tPunteros& punteros, int total) {
	int pos;
	tFoto* tmp = NULL;
	for (int i = 1; i < total; ++i) {
		pos = i;
		while ((pos > 0) && punteros[pos - 1]->titulo > punteros[pos]->titulo) {
			tmp = punteros[pos];
			punteros[pos] = punteros[pos - 1];
			punteros[pos - 1] = tmp;
			--pos;
		}
	}
}

void ordenarPorTema(tPunteros& punteros, int total) {
	int pos;
	tFoto* tmp = NULL;
	for (int i = 1; i < total; ++i) {
		pos = i;
		while ((pos > 0) && punteros[pos - 1]->tema > punteros[pos]->tema) {
			tmp = punteros[pos];
			punteros[pos] = punteros[pos - 1];
			punteros[pos - 1] = tmp;
			--pos;
		}
	}
}

bool resuelveCaso() {
	tPunteros ptrTitulo, ptrTema;
	tFoto* arrayFoto = new tFoto[TAM];
	int n;
	char aux;
	cin >> n;
	if (n == 0)
		return false;
	cin.get(aux);
	// leemos la información en el array dinámico
	for (int i = 0; i < n; ++i)
		getline(cin, arrayFoto[i].titulo);
	for (int i = 0; i < n; ++i)
		getline(cin, arrayFoto[i].tema);
	// cada puntero apunta a un tFoto del array dinámico
	for (int i = 0; i < n; ++i)
		ptrTitulo[i] = &arrayFoto[i];
	// ordenamos por título el primer array
	ordenarPorTitulo(ptrTitulo, n);
	// copiamos el primer array ordenado por título al segundo
	for (int i = 0; i < n; ++i)
		ptrTema[i] = ptrTitulo[i];
	// ordenamos el segundo array por tema
	ordenarPorTema(ptrTema, n);
	// imprimimos
	for (int i = 0; i < n; ++i) {
		cout << ptrTitulo[i]->titulo << endl;
	}
	cout << endl;
	for (int i = 0; i < n; ++i) {
		cout << ptrTema[i]->tema << " - " << ptrTema[i]->titulo << endl;
	}
	cout << endl;
	// finalmente borramos el array dinámico del montón
	delete[] arrayFoto;
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-16.1.in");
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