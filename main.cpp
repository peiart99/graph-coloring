#include <iostream>
#include "GraphLoader.h"

int main() {
    GraphLoader loader;
    //Graph newGraph = loader.loadInstance("test_5.txt");
    //newGraph.printGraph();
    Graph newGraph = loader.generateInstance(5);
    //std::cout << newGraph.getVertices() << std::endl;
    newGraph.printGraph();
    Graph newGraph2 = loader.generateInstance(5);
    //std::cout << newGraph2.getVertices() << std::endl;
    newGraph2.printGraph();
    Graph newGraph3 = loader.generateInstance(5);
    //std::cout << newGraph3.getVertices() << std::endl;
    newGraph3.printGraph();
    Graph newGraph4 = loader.generateInstance();
    //std::cout << newGraph4.getVertices() << std::endl;
    newGraph4.printGraph();
    return 0;
}
