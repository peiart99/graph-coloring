//
// Created by Artur on 08.05.2022.
//

#include "UserInterface.h"

void UserInterface::mainMenu() {
    bool quit {false};
    unsigned short choice{};
    do {
        std::cout << "--------Kolorowanie Grafu v1.1--------\n"
                     "[0] Lista funkcji\n"
                     "[1] Kolorowanie na podstawie pliku (greedy)\n"
                     "[2] Kolorowanie losowych grafow (greedy)\n"
                     "[9] Wyjscie" << std::endl;
        std::cin >> choice;
        switch(choice){
            case 0:
            {
                UserInterface::showDescription();
                break;
            }
            case 1:
            {
                UserInterface::colorFromFile();
                break;
            }
            case 2:
            {
                UserInterface::colorGenerated();
                break;
            }
            case 9:
            {
                quit = true;
                break;
            }
            default:
            {
                std::cout << "Podaj poprawny wybor" << std::endl;
            }
        }
    }while(!quit);

}

void UserInterface::showDescription() {
    std::cout << "Obecna wersja programu wspiera:\n"
                 "-Ladowanie grafu z pliku\n"
                 "-Generowanie losowych grafow o podanej liczbie wierzcholkow i procencie saturacji\n"
                 "-Kolorowanie grafow metoda zachlanna" << std::endl;
}

void UserInterface::colorFromFile() {
    std::string filename;
    GraphLoader loader;
    GraphColoring coloring;
    std::cout << "Podaj nazwe pliku" << std::endl;
    std::cin >> filename;
    Graph graph;
    loader.loadInstance(filename, graph);
    coloring.greedyAlgorithm(graph);
    std::cout << "==Uzyte kolory: " << graph.getNumberOfColors() << "==" << std::endl;
}

void UserInterface::colorGenerated() {
    int vertices{};
    float saturation{};
    std::string filename;
    GraphLoader loader;
    GraphColoring coloring;
    std::cout << "Podaj liczbe wierzcholkow" << std::endl;
    std::cin >> vertices;
    std::cout << "Podaj saturacje" << std::endl;
    std::cin >> saturation;
    std::cout << "Podaj nazwe pliku do zapisania instancji" << std::endl;
    std::cin >> filename;
    Graph graph;
    loader.generateInstance(vertices, saturation, graph);
    coloring.greedyAlgorithm(graph);
    std::cout << "==Uzyte kolory: " << graph.getNumberOfColors() << "==" << std::endl;
    //graph.printGraph();
    loader.saveToFile(graph, filename);
}
