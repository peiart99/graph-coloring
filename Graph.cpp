//
// Created by Artur on 26.04.2022.
//

#include "Graph.h"

#include <utility>


void Graph::printGraph() {
    std::cout << "======================" << std::endl;
    for(size_t i {0}; i < numberOfVertices; i++)
    {
        std::cout << "Vertex: " << vertices.at(i).getLabel() << " Color: "<< vertices.at(i).getColor() << " -> ";
        for(const auto &adj:vertices.at(i).adjacent)
        {
            std::cout << adj->getLabel() << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "======================" << std::endl;
}


Graph::Graph(int vx)
: numberOfVertices{vx}, numberOfColors{0} {
}

Graph::Graph(const Graph &copy)
: vertices{copy.vertices}, numberOfColors(copy.numberOfColors), numberOfVertices{copy.numberOfVertices} {

}

void Graph::addEdge(Vertex *vx1, Vertex *vx2) {
    vx1->addAdjacent(vx2);
    vx2->addAdjacent(vx1);

}

Graph::Graph(int vx, std::vector<Vertex> vxs)
: numberOfVertices{vx}, vertices{std::move(vxs)} {

}
