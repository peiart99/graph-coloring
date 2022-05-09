#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"
#include "UserInterface.h"

int main() {
    GraphLoader loader;
//    GraphColoring coloring;
    //Graph newGraph = loader.generateInstance(100, 0.5); // first argument - number of vertices to generate, second argument - saturation (0.1 - 1.0)
    //loader.saveToFile(newGraph, "905test3.txt");
    Graph loadedGraph = loader.loadInstance("queen6.txt");
//    coloring.greedyAlgorithm(newGraph);
    loadedGraph.printGraph();
//    std::cout << "Kolory: " << newGraph.getNumberOfColors() << std::endl;

    //UserInterface UI;
    //UI.mainMenu();


    return 0;
}
