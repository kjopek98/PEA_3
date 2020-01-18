#include "LoadInstance.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "Timer.h"


using namespace std;

LoadInstance::LoadInstance()
{
    instance = "";
    number = 0;
    size = 0;
}


void LoadInstance::load()
{
    string name = "";
    int choice;
    cout << "Wybierz rodzaj instancji: " << endl;
    cout << "1. TSP" << endl;
    cout << "2. ATSP" << endl;
    cin >> choice;
    cout << "Podaj nazwe instancji  'data.txt': " << endl;
    cin >> name;
    switch (choice)
    { 
    case 1: 
        instance = "C:/Users/Krzysiek/source/repos/Pea3Test/TSP/" + name;
        break;
    case 2:
        instance = "C:/Users/Krzysiek/source/repos/Pea3Test/ATSP/" + name;
        break;
    default:
        break;
    }
   
   
    ifstream data(instance.c_str());
    if (!data)
    {
        cout << "Wykryto blad przy otwieraniu pliku." << endl << endl;
        return;
    }

    data >> instance >> size;

    costMatrix = new int* [size];         // utworzenie tablicy wskaznikow

    for (int i = 0; i < size; i++)
    {
        costMatrix[i] = new int[size];    //utworzenie macierzy dwuwymiaorwej
    }


    for (int i = 0; i < size; i++)         //wypelnienie macierzy wartosciami wejsciowymi
    {
        for (int j = 0; j < size; j++)
        {
            data >> costMatrix[i][j];
        }
    }
    cout << endl;
    data.close();

    cout << "Instancja zostala wczytana pomyslnie." << endl << endl;
}

void LoadInstance::printTab()
{
    cout << "Rozmiar: " << size << endl;
    for (int i = 0; i < size; i++)         //wypelnienie macierzy wartosciami wejsciowymi
    {
        for (int j = 0; j < size; j++)
        {
            cout << costMatrix[i][j] << " ";
        }
        cout << endl;
    }

}