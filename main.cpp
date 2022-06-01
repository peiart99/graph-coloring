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
    loader.generateInstance(10, 0.5, graph);
    graph.printGraph();
    color.geneticAlgorithm(graph, 10000);

    return 0;
}
