#include "LoadInstance.h"
#include "Timer.h"
#include "Genetic.h"
#include <iostream>
#include <climits>
#include <windows.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std::chrono;
using namespace std;

int main()
{
	srand(time(NULL));

	bool isRead = false;
	LoadInstance load;
	Timer timer;
	vector<int> odp;
	
	int osobnicy;
	int ileNaj;
	int mutationType;

	
	
	char choice;
	cout << "Projektowanie Efektywnych Algorytmow - Etap 3" << endl
		<< "Krzysztof Jopek 241406" << endl
		<< "1. Wczytaj instancje" << endl
		<< "2. Wyswietl instancje" << endl
		<< "3. Algorytm genetyczny" << endl
		<< "4. Testy" << endl
		<< "0. Wyjscie" << endl;

	do {
		cout << "Twoj wybor: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
			load.load();
			break;
		case '2':
			if (!load.isRead) {
				cout << "Instancja nie zostala wczytana." << endl;
			}
			else {
				load.printTab();
			}
			break;
		case '3':
			if (!load.isRead) {
				cout << "Instancja nie zostala wczytana." << endl;
			}
			else {
				cout << "Populacja: " << endl;
				cin >> osobnicy;
				cout << "\nIlu najlepszych: " << endl;
				cin >> ileNaj;
				cout << "1. Mutacja swap" << endl
					<< "2. Mutacja invert" << endl
					<< "3. Mutacja scramble" << endl;
				cin >> mutationType;
				cout << "\n\nIlosc miast: " << load.size << endl;
				Genetic genetic(load.costMatrix, load.size);
				timer.start();
				odp = genetic.geneticAlg(osobnicy, ileNaj, 0.1, 0.9, mutationType, true);
				cout << "Czas wykonania: " << timer.duration() << " [ms]"<< endl;
				genetic.showRoad(odp);
			}
			break;
		case '4': 
			int ilosc = 30;
			mutationType = 3;
			double najWynik = INT_MAX;
			double najCzas = INT_MAX;
			double czas = 0;
			load.load();
			Genetic genetic(load.costMatrix, load.size);
			int ileOsobnikow = load.size * load.size;
			cout << "n" << endl;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.01 * ileOsobnikow , 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 1%: " << najWynik << " oraz czas: " << najCzas << endl;

			najWynik = INT_MAX;
		    najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.1 * ileOsobnikow, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 10%: " << najWynik << " oraz czas: " << najCzas << endl;
			
			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.3 * ileOsobnikow, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 30%: " << najWynik << " oraz czas: " << najCzas << endl;
			cout << "n^2" << endl;
			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = 4 * load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.01 * ileOsobnikow + 1, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 1%: " << najWynik << " oraz czas: " << najCzas << endl;

			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = 4 * load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.1 * ileOsobnikow, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 10%: " << najWynik << " oraz czas: " << najCzas << endl;

			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = 4 * load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.3 * ileOsobnikow, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 30%: " << najWynik << " oraz czas: " << najCzas << endl;
			cout << "4*n^2" << endl;
			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = 4* load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.01 * ileOsobnikow + 1, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 1%: " << najWynik << " oraz czas: " << najCzas << endl;

			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = 4 * load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.1 * ileOsobnikow, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 10%: " << najWynik << " oraz czas: " << najCzas << endl;
			
			najWynik = INT_MAX;
			najCzas = INT_MAX;
			czas = 0;
			ileOsobnikow = 4 * load.size * load.size;
			for (int i = 0; i < ilosc; i++) {
				timer.start();
				odp = genetic.geneticAlg(ileOsobnikow, 0.3 * ileOsobnikow, 0.1, 0.9, mutationType, true);
				czas = timer.duration();
				if (genetic.wynik < najWynik) {
					najWynik = genetic.wynik;
					najCzas = czas;
				}
			}
			cout << "Najlepszy wynik 30%: " << najWynik << " oraz czas: " << najCzas << endl;


			break;
		}
	} while (choice != '0');

	return 0;
}