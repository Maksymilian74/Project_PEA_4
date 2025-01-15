/*
 * Klasa Algorithms odpowiedzialna jest za implementacje
 * algorytmu rozwiazywania problemu komiwojazera oraz metod pomocniczych
 *
 */

#ifndef PROJEKT_PEA_2_ALGORITHMS_H
#define PROJEKT_PEA_2_ALGORITHMS_H

#include "../Structures/Matrix.h"
#include <vector>
#include <random>

using namespace std;

class Algorithms {
public:
    // Metoda Genetic Algorithm
    int GeneticAlgorithm(const Matrix& matrix, vector<int>& bestPath, int populationSize, int stopCriterion, double crossoverFactor, double mutationFactor, string crossoverMethod, string mutationMethod, double& bestPathTime);
private:
    // Metoda pomocnicza odpowiedzialna za obliczanie kosztu sciezki
    static int computePathCost(const Matrix& matrix, const std::vector<int>& path);

    // Metoda pomocnicza odpowiedzialna za generowanie losowych sciezek
    static std::vector<int> generateRandomPath(int size);

    // Metoda pomocnicza odpowiedzialna za inicjalizacje populacji
    static std::vector<std::vector<int>> initializePopulation(int populationSize, int chromosomeSize);

    // Metoda pomocnicza odpowiedzialna za selekcje turniejowa
    static int tournamentSelection(const std::vector<std::vector<int>>& population, const std::vector<int>& fitness);

    // Metoda pomocnicza odpowiedzialna za metode krzyzowania pmx
    static std::vector<int> pmxCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2);

    // Metoda pomocnicza odpowiedzialna za metode krzyzowania ox
    static std::vector<int> oxCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2);

    // Metoda pomocnicza odpowiedzialna za mutacje swap
    static void swapMutation(std::vector<int>& individual);

    // Metoda pomocnicza odpowiedzialna za mutacje insert
    static void insertionMutation(std::vector<int>& individual);

};

#endif
