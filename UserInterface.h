//
// Created by Artur on 08.05.2022.
//

#ifndef GRAPH_COLORING_USERINTERFACE_H
#define GRAPH_COLORING_USERINTERFACE_H
#include <iostream>
#include "GraphLoader.h"
#include "GraphColoring.h"
#include "Graph.h"

class UserInterface {
public:
    void mainMenu();
    void showDescription();
    void colorFromFile();
    void colorGenerated();
};


#endif //GRAPH_COLORING_USERINTERFACE_H
