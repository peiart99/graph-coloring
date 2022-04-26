//
// Created by Artur on 26.04.2022.
//

#ifndef GRAPH_COLORING_GRAPHLOADER_H
#define GRAPH_COLORING_GRAPHLOADER_H
#include <fstream>
#include <iostream>
#include <utility>
#include "Graph.h"

class GraphLoader {
private:
    std::fstream in_file;
public:
    GraphLoader() = default;
    Graph loadInstance(const std::string &filename);
};


#endif //GRAPH_COLORING_GRAPHLOADER_H
