#pragma once
#include <string>

using namespace std;

class LoadInstance
{
public:
    LoadInstance();

    string instance;    //nazwa instancji
    int number;         //numer pliku do wczytania
    int size;           //rozmiar instancji
    int** costMatrix;   //wskaznik na macierz kosztow podrozy komiwojazera
    bool isRead; //zmienna czy wczytany plik

    void load();     //laduje jedna instancje problemu wskazana przez uzytkownika
    void printTab(); //wypisuje macierz
};


