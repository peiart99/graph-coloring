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
#include "Population.h"

class GraphColoring {
private:
    int lowestAvailible(const Graph &graph, int vertex);
public:
    void greedyAlgorithm(Graph &graph);
    void geneticAlgorithm(Graph &graph, int generation_limit, int colors_to_try, std::string filename);

};


#endif //GRAPH_COLORING_GRAPHCOLORING_H
