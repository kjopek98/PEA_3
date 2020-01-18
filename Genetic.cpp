#include "Genetic.h"
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<stdlib.h>
#include <Windows.h>
#include <algorithm>

using namespace std;

Genetic::Genetic(int** loadedMatrix, double sizeOfMatrix) {

	size = sizeOfMatrix; //romiar instancji
	
	matrixOfCost = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrixOfCost[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			matrixOfCost[i][j] = loadedMatrix[i][j];		//przekopiowanie wartosci macierzy kosztow do wewnetrznej macierzy algorytmu
		}
	}
}


void Genetic::randomPerm(vector<int>& wektor) {
	int n = wektor.size();
	int tempi;
	wektor[0] = 0;
	for (int i = 1; i < n; i++) {
		wektor[i] = i;
	}
	for (int i = 1; i < n; i++) {
		int r = rand() % i + 1;
		tempi = wektor[i];
		wektor[i] = wektor[r];
		wektor[r] = tempi;
	}
}


int Genetic::road(vector <int>& wektor)
{
	double cost = 0;
	for (int i = 0; i < wektor.size() - 1; i++)
	{
		cost += matrixOfCost[wektor[i]][wektor[i + 1]]; //obliczanie kosztow przejsc miedzy wierzcholkami
	}
	cost += matrixOfCost[wektor[size - 1]][wektor[0]]; // doliczenie kosztu powrotu
	return cost;
}

//g³ówny algorytm
vector<int> Genetic::GeneticAlg(int liczbaOsobnikow, int liczbaNajlepszychOsobników ,float jakCzestoMutacja, bool testy) {

	vector<int>* osobniki; 
	osobniki = new vector<int>[liczbaOsobnikow];
	vector<int>* noweOsobniki;
	noweOsobniki = new vector<int>[liczbaOsobnikow];
	vector<int> najlepszyOsobnik;

	// przygotowanie macierzy - pierwszy losowy zbior populacji
	for (int i = 0; i < liczbaOsobnikow; i++) {
		//
		osobniki[i].resize(size);
		noweOsobniki[i].resize(size);
		randomPerm(osobniki[i]);
	}

	pair <double, int>* rozwiazanie;
	rozwiazanie = new pair <double, int>[liczbaOsobnikow];

	int pokolenie = 5;	//liczba pokolen po ktorych zakonczy sie algorytm
	double ostatni = INT_MAX;

	//g³ówna pêtla
	while (pokolenie > 0) {

		for (int i = 0; i < liczbaOsobnikow; i++) {
			rozwiazanie[i].first = road(osobniki[i]);
			rozwiazanie[i].second = i;
		}

		sort(rozwiazanie, rozwiazanie + liczbaOsobnikow);

		// warunek stopu
		if (ostatni > rozwiazanie[0].first) {
			ostatni = rozwiazanie[0].first;
			pokolenie = 5;
			najlepszyOsobnik = osobniki[rozwiazanie[0].second];
		}
		else {
			pokolenie--;
		}
		/*if (testy == 0) {
			cout << "Koszt: " << rozwiazanie[0].first << endl;
		}*/

		for (int i = 0; i < liczbaOsobnikow; i++) {
			noweOsobniki[i] = KrzyzowanieOx(osobniki[rozwiazanie[rand() % liczbaNajlepszychOsobników].second], osobniki[rozwiazanie[rand() % liczbaNajlepszychOsobników].second]);
			// je¿eli prawdopodobieñstwo jest dobre, to nastepuje mutacja
			if (float(rand()) / RAND_MAX < jakCzestoMutacja) {
				mutation(noweOsobniki[i]);
			}
		}
		vector <int>* temp = osobniki;
		osobniki = noweOsobniki;
		noweOsobniki = temp;
	}
	if (testy == true) {
		cout << "Koszt: " << rozwiazanie[0].first << endl;
	}
	delete[] osobniki;
	delete[] noweOsobniki;
	delete[] rozwiazanie;
	return najlepszyOsobnik;
}


// wypisywanie œcie¿ki
void Genetic::showRoad(vector<int>& wektor) {
	for (int i = 0; i < wektor.size() - 1; i++) {
		cout << wektor[i] << " ->";
	}
	cout << wektor[wektor.size() - 1]<< endl;
}

// mutowanie osobnika je¿eli zgodne z prawdopodobieñstwem
void Genetic::mutation(vector<int>& wektor) {
	int x, y;
	do {
		x = rand() % size;
		y = rand() % size;
	} while (x == y);

	swap(wektor.at(x), wektor.at(y));
}

vector<int> Genetic::KrzyzowanieOx(vector<int> pierwszyWektor, vector<int> drugiWector) {
	int odkad = rand() % size;
	int dokad = rand() % size;
	vector<int> wynik(size);
	vector<int> czyBylo(size);
	for (int i = 0; i < size; i++) {
		czyBylo[i] = 0;
	}

	for (int i = odkad; i != dokad; i = (i + 1) % size) {
		wynik[i] = pierwszyWektor[i];
		czyBylo[pierwszyWektor[i]] = 1;//ktore wzi¹lem z pierwszego wektora
	}
	int gdzie = (dokad) % size;
	for (int i = 0; i < size; i++) {
		if (czyBylo[drugiWector[(dokad + i) % size]] == 0) { //tam gdzie jest zero przepisuje wartosci z drugiego wektora
			wynik[gdzie] = drugiWector[(dokad + i) % size];
			gdzie = (gdzie + 1) % size;
		}
	}
	return wynik;
}

