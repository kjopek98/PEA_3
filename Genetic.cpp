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

Genetic::Genetic(int** loadedMatrix, int sizeOfMatrix) {

	size = sizeOfMatrix; //rozmiar instancji
	
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

//g��wny algorytm
vector<int> Genetic::geneticAlg(int liczbaOsobnikow, int liczbaNajlepszychOsobnik�w ,float jakCzestoMutacja, float jakCzestoKrzyzowanie, int mutation, bool testy) {

	vector<int>* osobniki; 
	osobniki = new vector<int>[liczbaOsobnikow];
	vector<int>* noweOsobniki;
	noweOsobniki = new vector<int>[liczbaOsobnikow];
	vector<int> najlepszyOsobnik;

	// przygotowanie macierzy - pierwszy losowy zbior populacji
	for (int i = 0; i < liczbaOsobnikow; i++) {
		
		osobniki[i].resize(size);
		noweOsobniki[i].resize(size);
		randomPerm(osobniki[i]);
	}
	// tworzymy struktur� pary, kt�ra wskazuje funckj� celu osobnika oraz jego indeks
	pair <double, int>* rozwiazanie;
	rozwiazanie = new pair <double, int>[liczbaOsobnikow];

	int pokolenie = 5;	//liczba pokolen po ktorych zakonczy sie algorytm
	double ostatni = INT_MAX;

	//g��wna p�tla
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
			// przypisanie najlepszego osobnika o najni�szym koszcie
			najlepszyOsobnik = osobniki[rozwiazanie[0].second];
		}
		else {
			pokolenie--;
		}
		/*if (testy == 0) {
			cout << "Koszt: " << rozwiazanie[0].first << endl;
		}*/

		// krzy�owanie i mutowanie osobnik�w
		for (int i = 0; i < liczbaOsobnikow; i++) {
			// je�eli prawdopodobie�stwo jest dobre, to nastepuje krzyzowanie
			if (float(rand()) / RAND_MAX < jakCzestoKrzyzowanie) {
				// wybranie dw�ch najlepszych osobnik�w do krzy�owania
				noweOsobniki[i] = krzyzowanieOx(osobniki[rozwiazanie[rand() % liczbaNajlepszychOsobnik�w].second], osobniki[rozwiazanie[rand() % liczbaNajlepszychOsobnik�w].second]);
			}
			else {
				noweOsobniki[i] = osobniki[i];
			}
			// je�eli prawdopodobie�stwo jest dobre, to nastepuje mutacja
			if (float(rand()) / RAND_MAX < jakCzestoMutacja) {
				if (mutation = 1) {
					swapMutation(noweOsobniki[i]);
				}
				if (mutation == 2) {
					inversionMutation(noweOsobniki[i]);
				}
				if (mutation == 3) {
					scrambleMutation(noweOsobniki[i]);
				}
			}
		}
		vector <int>* temp = osobniki;
		osobniki = noweOsobniki; //wrzucenie nowego pokolenia po zmianach genetycznych
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


// wypisywanie �cie�ki
void Genetic::showRoad(vector<int>& wektor) {
	for (int i = 0; i < wektor.size() - 1; i++) {
		cout << wektor[i] << " ->";
	}
	cout << wektor[wektor.size() - 1]<< endl;
}

// mutowanie osobnika swap
void Genetic::swapMutation(vector<int>& wektor) {
	int x, y;
	do {
		x = rand() % size;
		y = rand() % size;
	} while (x == y);

	swap(wektor.at(x), wektor.at(y));
}

//Funkcja pomocnicza do mutacji invert
void Genetic::invert(int i, int j, vector<int>& wektor) {
	int tempi;
	for (; i < j; i++, j--) {
		tempi = wektor[i];
		wektor[i] = wektor[j];
		wektor[j] = tempi;
	}
}
void Genetic::inversionMutation(vector<int>& wektor) {
	int i, j;
	do {
		i = rand() % size;
		j = rand() % size;
	} while (i == j);
	if (i <= j) {
		invert(i, j, wektor);
	}
	else {
		invert(j, i, wektor);
	}
}

void Genetic::scrambleMutation(vector<int>& wektor) {
	vector<int> pozycje (wektor.size());
	int l = pozycje.size();
	//kopiowanie osobnika do mutacji
	for (int i = 0; i < wektor.size(); i++) {
		pozycje[i] = wektor[i];
	}
	for (int k = 0; k < 5; k++) {
		int r1 = rand() % size;
		int r2 = rand() % size;
		//upewniamy si�, �e r1 jest wi�ksze od r2
		while(r1 >= r2){ r1 = rand() % size; r2 = rand() % size;}
		//scrambling
		for (int i = 0; i < 10; i++) {
			int i1 = rand() % (r2 + 1 - r1 + 1) + r1;
			int i2 = rand() % (r2 + 1 - r1 + 1) + r1;
			int a = pozycje[i1];
			pozycje[i1] = pozycje[i2];
			pozycje[i2] = a;
		}
	}
	//przepisywanie do osobnika zmutowanej wersji
	for (int i = 0; i < wektor.size(); i++) {
		wektor[i] = pozycje[i];
	}
}


vector<int> Genetic::krzyzowanieOx(vector<int> pierwszyWektor, vector<int> drugiWector) {
	int odkad = rand() % size;
	int dokad = rand() % size;
	vector<int> wynik(size);
	vector<int> czyBylo(size);
	for (int i = 0; i < size; i++) {
		czyBylo[i] = 0;
	}

	for (int i = odkad; i != dokad; i = (i + 1) % size) {
		wynik[i] = pierwszyWektor[i];
		czyBylo[pierwszyWektor[i]] = 1; // wpisuje, ktore geny wzi�lem z pierwszego wektora
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


vector<int> Genetic::krzyzowaniePmx(vector<int> pierwszyWektor, vector<int> drugiWector) {
	int odkad = rand() % size;
	int dokad = rand() % size;
	vector<int> wynik(size);
	vector<int> czyBylo(size);

	for (int i = odkad; i != dokad; i = (i + 1) % size) {
		wynik[i] = pierwszyWektor[i];
		//czyBylo[pierwszyWektor[i]] = 1;//ktore wzi�lem z pierwszego wektora
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
