/*
 * Klasa Menu odpowiedzialna jest za zarzadzanie glowna logika programu.
 * Odpowiada za wczytywanie konfiguracji z pliku, tworzenie macierzy,
 * wybieranie i uruchamianie odpowiedniego algorytmu
 */

#ifndef PROJEKT_PEA_2_MENU_H
#define PROJEKT_PEA_2_MENU_H

#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Menu {
public:
    Menu();  // Konstruktor
    void run();  // Glowna metoda uruchamiajaca dzialanie programu
    void loadConfig(const string& configFile);  // Metoda odpowiedzialna za wczytanie danych z pliku konfiguracyjnego

private:
    string inputFile;  // Zmienna przechowujaca nazwe pliku wejsciowego
    bool displayMatrix;   // Zmienna przechowujaca informacje czy wyswietlac macierz
    int iterations;  // Zmienna przechowujaca liczbe iteracji
    bool runGA;  // Zmienna przechowujaca informacje czy wywolywac algorytm Genetic Algorithm
    string outputFile;  // Zmienna przechowujaca nazwe pliku wyjsciowego
    bool progress;  // Zmienna przechowujaca informacje czy wyswietlac pasek postepu
    bool showResults;  // Zmienna przechowujaca informacje czy wyswietlac wyniki dzialania algorytmu
    int stopCriterion; // Zmienna przechowujaca informacje o kryterium stopu
    int populationSize; // Zmienna przechowujaca informacje o wielkosci populacji
    double crossoverFactor; // Zmienna przechowujaca informacje o wspolczynniku krzyzowania
    double mutationFactor; // Zmienna przechowujaca informacje o wspolczynniku mutacji
    string mutationMethod; // Zmienna przechowujaca informacje o metodzie mutacji
    string crossoverMethod; // Zmienna przechowujaca informacje o metodzie krzyzowania

    string extractValue(const string& line); // Pomocnicza metoda do wyciagania wartosci po "="
    void saveResultsToCSV(const string& algorithm, int size, int cost, double time);  // Pomocnicza metoda odpowiedzialna za zapis pomiarow do pliku
};

#endif

