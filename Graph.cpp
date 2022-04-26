//
// Created by Artur on 26.04.2022.
//

#include "Graph.h"


void Graph::printGraph() {
    std::cout << "======================" << std::endl;
    for(size_t i {0}; i < vertices; i++)
    {
        std::cout << "Vertex: " << i + 1 << " -> ";
        for(const auto &adj:adjacency.at(i + 1))
        {
            std::cout << adj << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "======================" << std::endl;
}

Graph::Graph(int vx, std::map<int, std::set<int>> adj)
: vertices{vx}, adjacency{adj} {

}
