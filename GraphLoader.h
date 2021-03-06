//
// Created by Artur on 26.04.2022.
//

#ifndef GRAPH_COLORING_GRAPHLOADER_H
#define GRAPH_COLORING_GRAPHLOADER_H
#include <fstream>
#include <iostream>
#include <utility>
#include "Graph.h"
#include <ctime>
#include <random>
#include <chrono>
#include <algorithm>

class GraphLoader {
private:
    std::fstream in_file;
public:
    GraphLoader() = default;
    void loadInstance(const std::string &filename, Graph &graph);
    void generateInstance(int vertices, float saturationPercent, Graph &graph);
    void saveToFile(const Graph &graph, std::string filename);

};


#endif //GRAPH_COLORING_GRAPHLOADER_H
