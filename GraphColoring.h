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

class GraphColoring {
public:
    std::pair<Graph, int> greedyAlgorithm(Graph graph);
};


#endif //GRAPH_COLORING_GRAPHCOLORING_H
