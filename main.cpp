#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"
#include "Chromosome.h"
#include <chrono>
#include "UserInterface.h"
#include "Utility.h"
#include "Population.h"


int main() {
    UserInterface UI;
    UI.mainMenu();
//    GraphLoader loader;
//    GraphColoring color;
//    Graph graph;
//    //loader.generateInstance(100, 0.5, graph);
//    loader.loadInstance("le450_5a.txt", graph);
//    color.geneticAlgorithm(graph, 10000, 8);
    return 0;


}
// 5, 3, 4, 6, 7, 2, 6, 7, 2, 1, 5, 3, 1, 5, 3, 4, 6, 7, 4, 6, 7, 2, 1, 5, 2, 1, 5, 3, 4, 6, 3, 4, 6, 7, 2, 1, - queen6 - 7 colors
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36