//
// Created by Artur on 26.04.2022.
//

#ifndef GRAPH_COLORING_GRAPH_H
#define GRAPH_COLORING_GRAPH_H
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include "Vertex.h"


class Graph {
private:
    int numberOfVertices;
    int numberOfColors;

public:
    std::vector<Vertex> vertices;
    explicit Graph(int vx = 0);
    Graph(const Graph &copy);
    ~Graph() = default;
    void addEdge(Vertex *vx1, Vertex *vx2);
    [[nodiscard]] std::vector<Vertex> getVertices() const {return vertices;};
    [[nodiscard]] int getNumberOfVertices() const {return numberOfVertices;};
    [[nodiscard]] int getNumberOfColors() const {return numberOfColors;};
    void setNumberOfColors(int value) {numberOfColors = value;};
    void setNumberOfVertices(int value) {numberOfVertices = value;};
    void printGraph();
};


#endif //GRAPH_COLORING_GRAPH_H
