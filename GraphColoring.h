//
// Created by Artur on 27.04.2022.
//

#ifndef GRAPH_COLORING_GRAPHCOLORING_H
#define GRAPH_COLORING_GRAPHCOLORING_H
#include <utility>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include "Graph.h"
#include "GraphLoader.h"

class GraphColoring {
private:
    int lowestAvailible(const Graph &graph, int vertex);
    void populate(int population_size, std::vector<std::pair<int, std::vector<int>>> &population, int colors, int vertices);
    void newGeneration(int population_size, std::vector<std::pair<int, std::vector<int>>> &population, std::vector<int> &child ,int colors, int vertices);
    void evaluateFitness(const Graph &graph, std::pair<int, std::vector<int>> &chromosome);
    void printPopulation(const std::vector<std::pair<int, std::vector<int>>> &population);
    void parentSelection1(const std::vector<std::pair<int, std::vector<int>>> &population, std::vector<int> &parent1, std::vector<int> &parent2);
    void crossover(const std::vector<int> &parent1, const std::vector<int> &parent2, std::vector<int> &child);
    void mutation1(const Graph &graph, std::vector<int> &child, int colors);
    void mutation2(const Graph &graph, std::vector<int> &child, int colors);
public:
    void greedyAlgorithm(Graph &graph);
    void geneticAlgorithm(Graph &graph, int generation_limit);

};


#endif //GRAPH_COLORING_GRAPHCOLORING_H
