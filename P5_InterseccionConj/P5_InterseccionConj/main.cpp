// Autora: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: intersección de conjuntos

#include <iostream>
#include <fstream>

using namespace std;

const int N = 500;
typedef struct { 
	int cto[N]; 
	int cont = 0; 
}tCto;

void ordenarCto(tCto& cto, int total) {

	for (int i = 0; i < total; ++i) {

		int menor = i;

		for (int j = i + 1; j < total; ++j) {
			if (cto.cto[j] < cto.cto[menor])
				menor = j;
		}
		if (menor > i) {
			int tmp;
			tmp = cto.cto[i];
			cto.cto[i] = cto.cto[menor];
			cto.cto[menor] = tmp;
		}
	}
}

tCto resolver(tCto &cto1, int elemCto1, tCto &cto2, int elemCto2) {

	//devolvemos el conjunto resultante
	tCto ctoResultante;

	//ordenamos los conjuntos
	ordenarCto(cto1, elemCto1);
	ordenarCto(cto2, elemCto2);

	int i = 0, j = 0;
	while (i < cto1.cont && j < cto2.cont) {
		if (cto2.cto[j] < cto1.cto[i])
			++j;
		else if (cto2.cto[j] == cto1.cto[i]) {
			ctoResultante.cto[ctoResultante.cont] = cto2.cto[j];
			++ctoResultante.cont;
			++j;
			++i;
		}
		//cto2.cto[j] > cto1.cto[i]
		else
			++i;
	}

	return ctoResultante;
}

void resuelveCaso() {

	tCto cto1, cto2, ctoR;

	//los contadores de los conjuntos están inicializados a 0

	//primer conjunto
	cin >> cto1.cto[cto1.cont];
	while (cto1.cto[cto1.cont] != 0) {
		++cto1.cont;
		cin >> cto1.cto[cto1.cont];
	}

	//segundo conjunto
	cin >> cto2.cto[cto2.cont];
	while (cto2.cto[cto2.cont] != 0) {
		++cto2.cont;
		cin >> cto2.cto[cto2.cont];
	}

	ctoR = resolver(cto1, cto1.cont, cto2, cto2.cont);

	//ahora tenemos que imprimir 
	for (int i = 0; i < ctoR.cont; ++i) {
		cout << ctoR.cto[i] << " ";
	}
	cout << endl;

}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("sample-05.1.in");
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