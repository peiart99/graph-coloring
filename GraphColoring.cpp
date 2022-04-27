//
// Created by Artur on 27.04.2022.
//

#include "GraphColoring.h"

int countUnique(std::vector<int> colors) {
    std::unordered_set<int> unique_colors(colors.begin(), colors.end());
    return unique_colors.size();
}

int lowestAvailible(const Graph &graph, int vertex)
{
    std::set<int> colors;
    int lowest {0};
    std::map<int, std::set<int>> adjacency = graph.getAdjacency();
    for(auto &adj: adjacency.at(vertex))
    {
        colors.insert(graph.getColors().at(adj-1));
    }
    for(int i {1}; i < graph.getColors().size(); i++)
    {
        if(colors.count(i) == 0)
        {
            lowest = i;
            return lowest;
        }
    }
    return lowest;
}

std::pair<Graph, int> GraphColoring::greedyAlgorithm(Graph graph) {
    int lowest {0};
    for(int i {0}; i < graph.getVertices(); i++)
    {
        lowest = lowestAvailible(graph, i + 1);
        graph.setColors(lowest, i);
    }
    return {graph, countUnique(graph.getColors())};
}
