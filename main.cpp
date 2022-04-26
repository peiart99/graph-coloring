#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"

int main() {
    GraphLoader loader;
    GraphColoring coloring;
    //Graph newGraph = loader.loadInstance("test_5.txt");
    //newGraph.printGraph();
    Graph newGraph = loader.generateInstance(5);
    //std::cout << newGraph.getVertices() << std::endl;
    newGraph.printGraph();
    std::pair<Graph, int> result = coloring.greedyAlgorithm(newGraph);
    result.first.printGraph();

    //Graph newGraph2 = loader.generateInstance(5);
    //std::cout << newGraph2.getVertices() << std::endl;
    //newGraph2.printGraph();
    //Graph newGraph3 = loader.generateInstance(5);
    //std::cout << newGraph3.getVertices() << std::endl;
    //newGraph3.printGraph();
    //Graph newGraph4 = loader.generateInstance();
    //std::cout << newGraph4.getVertices() << std::endl;
    //newGraph4.printGraph();
    return 0;
}
