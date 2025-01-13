#include "Menu.h"
#include "../Structures/Matrix.h"
#include "../Utils/ReadFile.h"
#include "../Algorithms/Algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Konstruktor odpowiedzialny za inicjalizacje domyslnych wartosci zmiennych
Menu::Menu() {
    inputFile = "";
    displayMatrix = false;
    iterations = 0;
    runGA = 0;
    outputFile = "";
    progress = false;
    showResults = 0;
    stopCriterion = 0;
    populationSize = 0;
    crossoverFactor = 0;
    mutationFactor = 0;
    crossoverMethod = "";
    mutationMethod= "";
}

// Glowna metoda odpowiedzialna za wykonanie programu na podstawie wczytanej konfiguracji
void Menu::run() {
    loadConfig("config.txt");  // Wczytanie konfiguracji z pliku config.txt

    Matrix* matrix = nullptr;  // Wskaznik do dynamicznie alokowanej macierzy

    ReadFile fileReader;
    int fileMatrixSize;
    try {
        // Wczytywanie rozmiaru macierzy z pliku
        fileMatrixSize = fileReader.getMatrixSize(inputFile);
        matrix = new Matrix(fileMatrixSize);
        fileReader.loadData(inputFile, *matrix); // Wczytanie danych do macierzy
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return;
    }

    Algorithms algorithms;  // Tworzenie obiektu klasy z algorytmami

    for (int i = 0; i < iterations; i++) {

        // Wyswietlanie macierzy
        if (displayMatrix) {
            matrix->display();
        }
        vector<int> bestPath;
        int minCost = 0;

        if (runGA) {
            int minCost = algorithms.GeneticAlgorithm(*matrix, bestPath, populationSize, stopCriterion, crossoverFactor, mutationFactor, crossoverMethod, mutationMethod);
            cout << "Najlepszy znaleziony koszt: " << minCost << endl;

            // Zapis pojedynczych wynikow do pliku CSV
            saveResultsToCSV("SimulatedAnnealing",matrix->getSize(), minCost);
        }

        if (showResults) {
            // Wyswietlenie wynikow
            cout << "Najlepsza trasa: ";
            for (int city: bestPath) {
                cout << city << " ";
            }
            cout << endl << endl << endl;
        }

        // Wyswietlenie wskaznika postepu
        if (progress) {
            int progress = ((i + 1) * 100) / iterations;  // Obliczenie procenta ukonczenia symulacji
            cout << "Postep: " << progress << "%" << endl;
        }
    }

    delete matrix;
}

// Metoda odpowiedzialna za wczytywanie konfiguracji z pliku konfiguracyjnego
void Menu::loadConfig(const string& configFile) {
    ifstream file(configFile);
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku konfiguracyjnego: " << configFile << endl;
        return;
    }

    string line;
    int lineCount = 0;

    while (getline(file, line)) {
        // Pomijanie komentarzy i pustych linii
        if (line.empty() || line[0] == '#') {
            continue;
        }

        string value = extractValue(line);  // Wyciaganie wartosci po znaku "="

        // Przypisanie wartosci na podstawie numeru linii
        switch (lineCount) {
            case 0:
                inputFile = value;
                break;
            case 1:
                displayMatrix = (value == "1");
                break;
            case 2:
                iterations = stoi(value);
                break;
            case 3:
                runGA = (value == "1");
                break;
            case 4:
                outputFile = value;
                break;
            case 5:
                progress = (value == "1");
                break;
            case 6:
                showResults = (value == "1");
                break;
            case 7:
                stopCriterion = stoi(value);
                break;
            case 8:
                populationSize = stoi(value);
                break;
            case 9:
                crossoverFactor = stod(value);
                break;
            case 10:
                mutationFactor  = stod(value);
                break;
            case 11:
                crossoverMethod = value;
                break;
            case 12:
                mutationMethod = value;
                break;
        }
        lineCount++;
    }
    file.close();
}

// Pomocnicza metoda do wyciagania wartosci po znaku "="
string Menu::extractValue(const string& line) {
    size_t tmp = line.find("=");
    if (tmp != string::npos) {
        return line.substr(tmp + 1);
    }
    return "";
}

// Metoda odpowiedzialna za zapis wyników do pliku CSV
void Menu::saveResultsToCSV(const string& algorithm, int size, int cost) {
    ofstream file(outputFile, ios::app);  // Otwieranie pliku w trybie dopisywania
    if (!file.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku wyjsciowego: " << outputFile << endl;
        return;
    }

    file << algorithm << "," << size << "," << cost << "\n";

    file.close();
}
