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
	
	char choice;
	cout << "Menu:" << endl;
	cout << "1. Wczytaj instancje" << endl
		<< "2. Wyswietl instancje" << endl
		<< "3. Algorytm genetyczny" << endl
		<< "0. Wyjscie" << endl;

	do {
		cout << "Twoj wybor: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
			load.load();
			isRead = true;
			break;
		case '2':
			if (!isRead) {
				cout << "Instancja nie zostala wczytana." << endl;
			}
			else {
				load.printTab();
			}
			break;
		case '3':
			if (!isRead) {
				cout << "Instancja nie zostala wczytana." << endl;
			}
			else {
				cout << "Populacja: " << endl;
				cin >> osobnicy;
				cout << "\nIlu najlepszych: " << endl;
				cin >> ileNaj;
				cout << "\n\nIlosc miast: " << load.size << endl;
				Genetic genetic(load.costMatrix, load.size);
				timer.start();
				odp = genetic.GeneticAlg(osobnicy, ileNaj, 0.01, true);
				cout << "Czas wykonania: " << timer.duration() << endl;
				genetic.showRoad(odp);
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