//
// Created by Artur on 26.04.2022.
//

#ifndef GRAPH_COLORING_GRAPH_H
#define GRAPH_COLORING_GRAPH_H
#include <map>
#include <set>
#include <iostream>



class Graph {
private:
    int vertices;
    std::map<int, std::set<int>> adjacency;

public:
    Graph(int vx, std::map<int, std::set<int>> adj);
    void printGraph();
};


#endif //GRAPH_COLORING_GRAPH_H
