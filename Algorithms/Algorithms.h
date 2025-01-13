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
    int GeneticAlgorithm(const Matrix& matrix, vector<int>& bestPath, int populationSize, int stopCriterion, double crossoverFactor, double mutationFactor, string crossoverMethod, string mutationMethod);
private:
    static int computePathCost(const Matrix& matrix, const std::vector<int>& path);
    static std::vector<int> generateRandomPath(int size);
    static std::vector<std::vector<int>> initializePopulation(int populationSize, int chromosomeSize);
    static int tournamentSelection(const std::vector<std::vector<int>>& population, const std::vector<int>& fitness);
    static std::vector<int> pmxCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    static std::vector<int> oxCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2);
    static void swapMutation(std::vector<int>& individual);
    static void insertionMutation(std::vector<int>& individual);

};

#endif
