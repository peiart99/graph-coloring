#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"
#include "UserInterface.h"

int main() {
    //UserInterface UI;
    //UI.mainMenu();
    GraphLoader loader;
    GraphColoring color;
    Graph graph;
    //loader.generateInstance(100, 0.5, graph);
    loader.loadInstance("gc500.txt", graph);
    //graph.printGraph();
    color.geneticAlgorithm(graph, 20000, 68);

    return 0;
}
