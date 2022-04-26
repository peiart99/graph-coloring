#include <iostream>
#include "GraphLoader.h"

int main() {
    GraphLoader loader;
    Graph newGraph = loader.loadInstance("test_5.txt");
    newGraph.printGraph();
    return 0;
}
