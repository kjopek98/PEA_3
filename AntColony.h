#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cmath>
#include <Windows.h>
class AntColony
{
private:
	int** matrixOfCost; // wska�nik na dynamiczna macierz zawierajaca macierz kosztow przejsc
	int size; //rozmiar instancji

public:
	AntColony(int** loadedMatrix, int sizeOfMatrix); //konstruktor klasy
};

