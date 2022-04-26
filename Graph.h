//
// Created by Artur on 26.04.2022.
//

#ifndef GRAPH_COLORING_GRAPH_H
#define GRAPH_COLORING_GRAPH_H
#include <map>
#include <vector>
#include <iostream>



class Graph {
private:
    int vertices;
    std::map<int, std::vector<int>> adjacency;

public:
    Graph(int vx, std::map<int, std::vector<int>> adj);
    void printGraph();
};


#endif //GRAPH_COLORING_GRAPH_H
