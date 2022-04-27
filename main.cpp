#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"
#include <chrono>

int main() {
    GraphLoader loader;
    GraphColoring coloring;
    Graph newGraph = loader.generateInstance(5, 0.5);
    coloring.greedyAlgorithm(newGraph);
    newGraph.printGraph();
    std::cout << "Kolory: " << newGraph.getNumberOfColors() << std::endl;
//    Graph newGraph = loader.loadInstance("test_36.txt");
//    Graph newGraph2 = loader.loadInstance("test_128.txt");
//    Graph newGraph3 = loader.loadInstance("test_500.txt");
//    Graph newGraph4 = loader.loadInstance("test_1000.txt");
//    Graph newGraph5 = loader.loadInstance("test_450.txt");
    //Graph newGraph = loader.generateInstance(500);

//    coloring.greedyAlgorithm(newGraph);
//    std::cout << newGraph.getNumberOfColors() << " kolorow" << std::endl;
//    coloring.greedyAlgorithm(newGraph2);
//    std::cout << newGraph2.getNumberOfColors() << " kolorow" << std::endl;
//    coloring.greedyAlgorithm(newGraph3);
//    std::cout << newGraph3.getNumberOfColors() << " kolorow" << std::endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    coloring.greedyAlgorithm(newGraph4);
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
//    std::cout << "DURATION: " << duration.count() << " SECONDS" << std::endl;
//    std::cout << newGraph4.getNumberOfColors() << " kolorow" << std::endl;
//    coloring.greedyAlgorithm(newGraph5);
//    std::cout << newGraph5.getNumberOfColors() << " kolorow" << std::endl;

    return 0;
}
