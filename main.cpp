#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"

int main() {
    GraphLoader loader;
    GraphColoring coloring;
    Graph newGraph = loader.loadInstance("test_36.txt");
    Graph newGraph2 = loader.loadInstance("test_128.txt");
    Graph newGraph3 = loader.loadInstance("test_500.txt");
    Graph newGraph4 = loader.loadInstance("test_1000.txt");
    Graph newGraph5 = loader.loadInstance("test_450.txt");
    //Graph newGraph = loader.generateInstance(500);
    std::pair<Graph, int> result = coloring.greedyAlgorithm(newGraph);
    std::cout << result.second << " kolorow" << std::endl;
    result = coloring.greedyAlgorithm(newGraph2);
    std::cout << result.second << " kolorow" << std::endl;
    result = coloring.greedyAlgorithm(newGraph3);
    std::cout << result.second << " kolorow" << std::endl;
    result = coloring.greedyAlgorithm(newGraph4);
    std::cout << result.second << " kolorow" << std::endl;
    result = coloring.greedyAlgorithm(newGraph5);
    std::cout << result.second << " kolorow" << std::endl;
    //result.first.printGraph();
    //newGraph.printGraph();
    //Graph newGraph = loader.generateInstance(5);
    //std::cout << newGraph.getVertices() << std::endl;
    //newGraph.printGraph();
    //std::pair<Graph, int> result = coloring.greedyAlgorithm(newGraph);
    //result.first.printGraph();

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
