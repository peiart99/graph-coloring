#include <iostream>
#include "GraphLoader.h"

int main() {
    GraphLoader loader;
    Graph newGraph = loader.loadInstance("test.txt");
    newGraph.printGraph();
    return 0;
}
