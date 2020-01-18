#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cmath>
#include <Windows.h>

using namespace std;

class Genetic
{
private:
	int** matrixOfCost; // wska�nik na dynamiczna macierz zawierajaca macierz kosztow przejsc
	int size; //rozmiar instancji

public:
	Genetic(int** loadedMatrix, double sizeOfMatrix); //konstruktor klasy
	void randomPerm(vector<int>& wektor); //losowanie sciezki
	vector<int> KrzyzowanieOx(vector<int> pierwszyWektor, vector<int> drugiWector); //krzyzowanie Ox
	void mutation(vector<int>& wektor); //mutowanie osobnika
	// g��wny algorytm
	vector<int>  GeneticAlg(int liczbaOsobnikow, int liczbaNajleoszychOsobnik�w, float jakCzestoMutacja, bool testy);
	void testy(); //testowanie
	int road(vector<int>& wektor);
	void showRoad(vector<int>& wektor);



};

