//
// Created by Artur on 26.04.2022.
//

#include "Graph.h"

#include <utility>


void Graph::printGraph() {
    std::cout << "======================" << std::endl;
    for(size_t i {0}; i < number_of_vertices; i++)
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
: number_of_vertices{vx}, number_of_colors{0} {
}

Graph::Graph(const Graph &copy)
: vertices{copy.vertices}, number_of_colors(copy.number_of_colors), number_of_vertices{copy.number_of_vertices} {

}

void Graph::addEdge(Vertex *vx1, Vertex *vx2) {
    vx1->addAdjacent(vx2);
    vx2->addAdjacent(vx1);

}

void Graph::findOptimalIndices() {
    for(int i{0}; i < vertices.size(); i++)
    {
        optimalIndices.push_back(-1);
        for(int j{0}; j < vertices.at(i).adjacent.size(); j++)
        {
            if(vertices.at(i).adjacent.at(j)->getLabel() > vertices.at(i).getLabel())
            {
                optimalIndices.at(i) = j;
                break;
            }
        }
    }
}
