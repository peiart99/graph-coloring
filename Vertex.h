//
// Created by Artur on 08.05.2022.
//

#ifndef GRAPH_COLORING_VERTEX_H
#define GRAPH_COLORING_VERTEX_H
#include <vector>
#include <memory>
#include <utility>

class Vertex {
private:
    int label;
    int color;
public:
    std::vector<Vertex*> adjacent;
    Vertex(int labelVal, int colorVal);
    ~Vertex() = default;
    void addAdjacent(Vertex* vxPtr);
    [[nodiscard]] int getLabel() const {return label;};
    [[nodiscard]] int getColor() const {return color;};
    void setColor(int newColor) {color = newColor;};
    bool operator<(const Vertex &rhs);
    bool operator>(const Vertex &rhs);
};


#endif //GRAPH_COLORING_VERTEX_H
