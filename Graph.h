//
// Created by Artur on 26.04.2022.
//

#ifndef GRAPH_COLORING_GRAPH_H
#define GRAPH_COLORING_GRAPH_H
#include <map>
#include <set>
#include <vector>
#include <iostream>



class Graph {
private:
    int vertices;
    std::vector<int> colors;
    std::map<int, std::set<int>> adjacency;

public:
    Graph(int vx, std::map<int, std::set<int>> adj);
    Graph(const Graph &copy);
    [[nodiscard]] int getVertices() const {return vertices;};
    [[nodiscard]] std::map<int, std::set<int>> getAdjacency() const {return adjacency;};
    [[nodiscard]] std::vector<int> getColors() const {return colors;};
    void setColors(int value, int index) {colors.at(index) = value;};
    void printGraph();
};


#endif //GRAPH_COLORING_GRAPH_H
