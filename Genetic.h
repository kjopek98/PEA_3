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
	int** matrixOfCost; // wskaŸnik na dynamiczna macierz zawierajaca macierz kosztow przejsc
	int size; //rozmiar instancji

public:
	Genetic(int** loadedMatrix, int sizeOfMatrix); //konstruktor klasy
	void randomPerm(vector<int>& wektor); //losowanie sciezki
	vector<int> krzyzowanieOx(vector<int> pierwszyWektor, vector<int> drugiWector); //krzyzowanie Ox
	vector<int> krzyzowaniePmx(vector<int> pierwszyWektor, vector<int> drugiWector); //krzyzowanie Pmx
	void inversionMutation(vector<int>& wektor); //mutowanie osobnika - invert
	void scrambleMutation(vector<int>& wektor);
	void swapMutation(vector<int>& wektor); //mutowanie osobnika - swap
	void invert(int i, int j, vector<int>& wektor);
	// g³ówny algorytm
	vector<int>  geneticAlg(int liczbaOsobnikow, int liczbaNajleoszychOsobników, float jakCzestoMutacja, float jakCzestoKrzyzowanie, int mutation, bool testy);
	void testy(); //testowanie
	int road(vector<int>& wektor);
	void showRoad(vector<int>& wektor);



};

