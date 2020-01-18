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
		<< "4. Algorytm mrowkowy" << endl
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
		case 4:
			if (!load.isRead) {
				cout << "Instancja nie zostala wczytana." << endl;
			}
			else {

			}
			break;
		case '0':
			break;
		default:
			cout << "Bledny wybor." << endl;
		}
	} while (choice != '0');

	return 0;
}