#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"

int main() {
    GraphLoader loader;
    GraphColoring coloring;
    Graph newGraph = loader.generateInstance(500, 0.5); // first argument - number of vertices to generate, second argument - saturation (0.1 - 1.0)
    //Graph loadedGraph = loader.loadInstance("test_128.txt");
    coloring.greedyAlgorithm(newGraph);
    //newGraph.printGraph();
    std::cout << "Kolory: " << newGraph.getNumberOfColors() << std::endl;
    return 0;
}
