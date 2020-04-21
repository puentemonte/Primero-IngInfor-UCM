// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre problema: Colección de fotos
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
typedef struct {
	int cont;
	tFoto array_fotos[TAM];
}tListaFotos;

typedef tFoto *tPtrFoto;
typedef struct {
	tPtrFoto tArrayPtr[TAM];
	// mismo cont que numFotos
	int cont;
}tPunteros;

void ordenarPorTitulo(tPunteros &punteros) {
	for (int i = 0; i < punteros.cont; ++i) {

		int menor = i;

		for (int j = i + 1; j < punteros.cont; ++j) {
			if (punteros.tArrayPtr[j]->titulo < punteros.tArrayPtr[menor]->titulo)
				menor = j;
		}
		if (menor > i) {
			string tmp;
			tmp = punteros.tArrayPtr[i]->titulo;
			punteros.tArrayPtr[i]->titulo = punteros.tArrayPtr[menor]->titulo;
			punteros.tArrayPtr[menor]->titulo = tmp;
		}
	}
}

void ordenarPorTema(tPunteros& punteros) {
	for (int i = 0; i < punteros.cont; ++i) {

		int menor = i;

		for (int j = i + 1; j < punteros.cont; ++j) {
			if (punteros.tArrayPtr[j]->tema < punteros.tArrayPtr[menor]->tema)
				menor = j;
		}
		if (menor > i) {
			string tmp;
			tmp = punteros.tArrayPtr[i]->tema;
			punteros.tArrayPtr[i]->titulo = punteros.tArrayPtr[menor]->tema;
			punteros.tArrayPtr[menor]->tema = tmp;
		}
	}
}

bool operator>(string izq, string der) {
	return izq > der;
}

void cargar(tListaFotos& lista_fotos) {
	for (int i = 0; i < lista_fotos.cont; ++i) {
		getline(cin, lista_fotos.array_fotos[i].titulo);
	}
	for (int i = 0; i < lista_fotos.cont; ++i) {
		getline(cin, lista_fotos.array_fotos[i].tema);
	}
}

void inicializar(tPunteros& ptr, tListaFotos& lista_fotos) {
	for (int i = 0; i < ptr.cont; ++i) {
		ptr.tArrayPtr[i] = &lista_fotos.array_fotos[i];
	}
}

void resuelveCaso() {
	int n;
	tListaFotos lista_fotos;
	tPunteros ptr1, ptr2;
	// num casos
	cin >> n;
	lista_fotos.cont = n;
	// cargamos lista de fotos
	cargar(lista_fotos);
	// inicializamos los punteros
	ptr1.cont = n;
	ptr2.cont = n;
	inicializar(ptr1, lista_fotos);
	inicializar(ptr2, lista_fotos);
	// ordenamos primero por titulo
	ordenarPorTitulo(ptr1);
	// una vez ordenado por titulo, ordenamos por tema
	ordenarPorTitulo(ptr2);
	ordenarPorTema(ptr2);
	// visualizamos
	for (int i = 0; i < ptr1.cont; ++i) {
		cout << ptr1.tArrayPtr[i]->titulo << endl;
	}
	for (int i = 0; i < ptr2.cont; ++i) {
		cout << ptr2.tArrayPtr[i]->tema << " - " << ptr2.tArrayPtr[i]->titulo << endl;
	}
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-14.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
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