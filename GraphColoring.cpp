//
// Created by Artur on 27.04.2022.
//

#include "GraphColoring.h"

int countUnique(const std::vector<int> &colors) {
    std::unordered_set<int> unique_colors(colors.begin(), colors.end());
    return unique_colors.size();
}

int GraphColoring::lowestAvailible(const Graph &graph, int vertex)
{
    int count {1};
    std::set<int> adjacent = graph.getAdjacency().at(vertex);
    std::set<int> colors;
    for(const auto &vx: adjacent)
    {
        if(vx > vertex)
            break;
        colors.emplace(graph.getColors().at(vx-1));
    }
    while(true)
    {
        if(colors.count(count) == 0)
        {
            return count;
        }
        count++;
    }
}

void GraphColoring::greedyAlgorithm(Graph &graph) {
    int lowest {1};
    for(int i {0}; i < graph.getVertices(); i++)
    {
        if(i > 0)
        {
            lowest = GraphColoring::lowestAvailible(graph, i + 1);
            graph.setColors(lowest, i);
        }else
        {
            graph.setColors(1, i);
        }

    }
    graph.setNumberOfColors(countUnique(graph.getColors()));
}
