//
// Created by Artur on 08.06.2022.
//

#ifndef GRAPH_COLORING_POPULATION_H
#define GRAPH_COLORING_POPULATION_H
#include <vector>
#include <algorithm>
#include "Chromosome.h"
#include "Graph.h"
#include "Utility.h"
#include <thread>

class Population {
private:
    int population_size;
    int max_colors;
    int best_fitness;
public:
    std::vector<Chromosome> population;
    Population(int size, int col);
    void print();
    void generatePopulation(Graph &graph);
    void shufflePopulation();
    void sortPopulation();
    void selection1();
    void selection2();
    void crossover(int generation);
    void evaluateAllFitness();
    void setBestFitness(int new_best_fitness) {best_fitness = new_best_fitness;};
    [[nodiscard]] int getBestFitness() const {return best_fitness;};
};


#endif //GRAPH_COLORING_POPULATION_H
