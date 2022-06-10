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
    int number_of_vertices;
    int number_of_colors;

public:
    std::vector<Vertex> vertices;
    std::vector<int> optimalIndices;
    explicit Graph(int vx = 0);
    Graph(const Graph &copy);
    ~Graph() = default;
    void addEdge(Vertex *vx1, Vertex *vx2);
    [[nodiscard]] std::vector<Vertex> getVertices() const {return vertices;};
    [[nodiscard]] int getNumberOfVertices() const {return number_of_vertices;};
    [[nodiscard]] int getNumberOfColors() const {return number_of_colors;};
    void setNumberOfColors(int value) { number_of_colors = value;};
    void setNumberOfVertices(int value) { number_of_vertices = value;};
    void findOptimalIndices();
    void printGraph();
};


#endif //GRAPH_COLORING_GRAPH_H
