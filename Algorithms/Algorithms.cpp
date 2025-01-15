#include "Algorithms.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Metoda Genetic Algorithm
int Algorithms::GeneticAlgorithm(const Matrix& matrix, vector<int>& bestPath, int populationSize, int stopCriterion, double crossoverFactor, double mutationFactor, string crossoverMethod, string mutationMethod, double& bestPathTime) {

        srand(time(nullptr));

        int chromosomeSize = matrix.getSize();
        vector<vector<int>> population = initializePopulation(populationSize, chromosomeSize);

        vector<int> fitness(populationSize);
        for (int i = 0; i < populationSize; i++) {
            fitness[i] = computePathCost(matrix, population[i]);
        }

        int bestCost = numeric_limits<int>::max();
        int bestIndex = 0;
        for (int i = 0; i < populationSize; i++) {
            if (fitness[i] < bestCost) {
                bestCost = fitness[i];
                bestIndex = i;
            }
        }
        bestPath = population[bestIndex];

        auto start = high_resolution_clock::now();

        while (true) {
            auto now = high_resolution_clock::now();
            auto elapsed = duration_cast<seconds>(now - start).count();
            if (elapsed >= stopCriterion) {
                break;
            }

            vector<vector<int>> newPopulation(populationSize);
            vector<int> newFitness(populationSize);

            for (int i = 0; i < populationSize; i++) {
                int parent1 = tournamentSelection(population, fitness);
                int parent2 = tournamentSelection(population, fitness);

                double r = static_cast<double>(rand()) / RAND_MAX;
                vector<int> offspring = population[parent1];
                if (r < crossoverFactor) {
                    if (crossoverMethod == "PMX") {
                        offspring = pmxCrossover(population[parent1], population[parent2]);
                    } else if (crossoverMethod == "OX") {
                        offspring = oxCrossover(population[parent1], population[parent2]);
                    }
                }

                r = static_cast<double>(rand()) / RAND_MAX;
                if (r < mutationFactor) {
                    if (mutationMethod == "swap") {
                        swapMutation(offspring);
                    } else if (mutationMethod == "insert") {
                        insertionMutation(offspring);
                    }
                }

                newPopulation[i] = offspring;
            }

            for (int i = 0; i < populationSize; i++) {
                newFitness[i] = computePathCost(matrix, newPopulation[i]);
            }

            for (int i = 0; i < populationSize; i++) {
                if (newFitness[i] < bestCost) {
                    bestCost = newFitness[i];
                    bestPath = newPopulation[i];

                    auto best = high_resolution_clock::now();
                    double elapsedBest = duration_cast<milliseconds>(best - start).count() / 1000.0;
                    bestPathTime = elapsedBest;
                }
            }

            population = newPopulation;
            fitness = newFitness;
        }

        return bestCost;
    }

// Metoda pomocnicza odpowiedzialna za obliczanie kosztu sciezki
int Algorithms::computePathCost(const Matrix& matrix, const vector<int>& path) {
    int totalCost = 0;
    int size = path.size();
    for (int i = 0; i < size - 1; i++) {
        totalCost += matrix.getCost(path[i], path[i + 1]);
    }

    totalCost += matrix.getCost(path[size - 1], path[0]);
    return totalCost;
}

// Metoda pomocnicza odpowiedzialna za generowanie losowych sciezek
std::vector<int> Algorithms::generateRandomPath(int size) {
    vector<int> path(size);
    for (int i = 0; i < size; i++) {
        path[i] = i;
    }
    // Tasowanie Fisher-Yates
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(path[i], path[j]);
    }
    return path;
}

// Metoda pomocnicza odpowiedzialna za inicjalizacje populacji
std::vector<std::vector<int>> Algorithms::initializePopulation(int populationSize, int chromosomeSize) {
    vector<vector<int>> population;
    population.reserve(populationSize);
    for (int i = 0; i < populationSize; i++) {
        population.push_back(generateRandomPath(chromosomeSize));
    }
    return population;
}

// Metoda pomocnicza odpowiedzialna za selekcje turniejowa
int Algorithms::tournamentSelection(const vector<vector<int>>& population, const vector<int>& fitness) {
    int size = population.size();
    int i = rand() % size;
    int j = rand() % size;

    return (fitness[i] < fitness[j]) ? i : j;
}

// Metoda pomocnicza odpowiedzialna za metode krzyzowania pmx
std::vector<int> Algorithms::pmxCrossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    int size = parent1.size();
    std::vector<int> child(size, -1);

    int start = rand() % size;
    int end   = rand() % size;
    if (start > end) {
        std::swap(start, end);
    }

    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }

    for (int i = start; i <= end; ++i) {
        int val = parent2[i];

        bool inChild = false;
        for (int j = 0; j < size; j++) {
            if (child[j] == val) {
                inChild = true;
                break;
            }
        }

        if (!inChild) {
            int position = i;

            while (child[position] != -1) {

                int cityToFind = parent1[position];

                int newPos = -1;
                for (int k = 0; k < size; k++) {
                    if (parent2[k] == cityToFind) {
                        newPos = k;
                        break;
                    }
                }
                position = newPos;
            }

            child[position] = val;
        }
    }

    for (int i = 0; i < size; ++i) {
        if (child[i] == -1) {
            child[i] = parent2[i];
        }
    }

    return child;
}

// Metoda pomocnicza odpowiedzialna za metode krzyzowania ox
std::vector<int> Algorithms::oxCrossover(const vector<int>& parent1, const vector<int>& parent2) {
    int size = parent1.size();
    vector<int> child(size, -1);

    int cut1 = rand() % size;
    int cut2 = rand() % size;
    if (cut1 > cut2) swap(cut1, cut2);

    for (int i = cut1; i <= cut2; i++) {
        child[i] = parent1[i];
    }

    int currentPos = (cut2 + 1) % size;
    for (int i = 0; i < size; i++) {
        int idx = (cut2 + 1 + i) % size;
        int val = parent2[idx];

        bool found = false;
        for (int k = cut1; k <= cut2; k++) {
            if (child[k] == val) {
                found = true;
                break;
            }
        }
        if (!found) {
            while (child[currentPos] != -1) {
                currentPos = (currentPos + 1) % size;
            }
            child[currentPos] = val;
        }
    }
    return child;
}

// Metoda pomocnicza odpowiedzialna za mutacje swap
void Algorithms::swapMutation(vector<int>& individual) {
    int size = individual.size();
    int i1 = rand() % size;
    int i2 = rand() % size;
    std::swap(individual[i1], individual[i2]);
}

// Metoda pomocnicza odpowiedzialna za mutacje insert
void Algorithms::insertionMutation(vector<int>& individual) {
    int size = individual.size();
    int from = rand() % size;
    int to = rand() % size;
    if (from == to) return;

    int val = individual[from];
    if (from < to) {
        for (int i = from; i < to; i++) {
            individual[i] = individual[i + 1];
        }
        individual[to] = val;
    } else {
        for (int i = from; i > to; i--) {
            individual[i] = individual[i - 1];
        }
        individual[to] = val;
    }
}

