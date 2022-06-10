//
// Created by Artur on 27.04.2022.
//

#include "GraphColoring.h"
#include "Utility.h"
#include <chrono>
#include <thread>

int countUniqueColors(const Graph &graph) {
    std::unordered_set<int> unique_colors;
    for(const auto &vx : graph.vertices)
    {
        if(vx.getColor() != 0)
            unique_colors.insert(vx.getColor());
    }
    return unique_colors.size();
}

int countUniqueColorsChromosome(const std::vector<int> &chromosome)
{
    std::unordered_set<int> unique_colors;
    for(auto color: chromosome)
    {
        unique_colors.insert(color);
    }
    return unique_colors.size();
}

int GraphColoring::lowestAvailible(const Graph &graph, int vertex)
{
    int lowest{};
    std::vector<int> colors(graph.getNumberOfVertices(), 0);
    for(int i {0}; i < graph.vertices.at(vertex).adjacent.size(); i++)
    {
        if(graph.vertices.at(vertex).adjacent.at(i)->getColor() != 0)
            colors.at(graph.vertices.at(vertex).adjacent.at(i)->getColor() - 1) = 1;
    }
    for(int j {0}; j < colors.size(); j++)
    {
        if(colors.at(j) == 0)
        {
            return j + 1;
        }
    }

    return lowest;
}

void GraphColoring::greedyAlgorithm(Graph &graph) {
    int lowest {1};
    for(int i {0}; i < graph.getNumberOfVertices(); i++)
    {
        if(i > 0)
        {
            lowest = GraphColoring::lowestAvailible(graph, i);
            graph.vertices.at(i).setColor(lowest);
        }else
        {
            graph.vertices.at(i).setColor(1);
        }

    }
    graph.setNumberOfColors(countUniqueColors(graph));
}

void GraphColoring::geneticAlgorithm(Graph &graph, int generation_limit, int colors_to_try, std::string filename) {
    bool gen_limit_reached {false};
    do {
        Population pop(200, colors_to_try);
        bool solution_found {false};
        int fitness_counter {0};
        int prev_fitness {0};
        int stagnant_counter {0};
        bool stagnant {false};
        int generation {0};
        pop.generatePopulation(graph);
        pop.sortPopulation();
        //pop.print();
        if(pop.getBestFitness() == 0)
        {
            solution_found = true;
        }
        generation++;
        prev_fitness = pop.getBestFitness();

        while(!solution_found && generation < generation_limit)
        {
            generation++;
            if(stagnant_counter > 0)
            {
                pop.selection2();
                stagnant_counter--;
            }else
            {
                pop.selection1();
            }
            pop.shufflePopulation();
            pop.crossover(generation);
            pop.evaluateAllFitness();
            pop.sortPopulation();
            if(generation % 10 == 0)
            {
                std::cout << "Generation: " << generation << std::endl;
                std::cout << "Best Fitness: " << pop.getBestFitness() << std::endl;
            }
            if(pop.getBestFitness() == 0)
            {
                solution_found = true;
            }
            if(pop.getBestFitness() == prev_fitness)
            {
                fitness_counter++;
            }else
            {
                prev_fitness = pop.getBestFitness();
                fitness_counter = 0;
                stagnant = false;
            }
            if(fitness_counter > 100)
            {
                stagnant = true;
                stagnant_counter = 10;
                fitness_counter = 0;
            }

        }
        if(!solution_found)
        {
            gen_limit_reached = true;
        }

        pop.population.at(0).print();
        pop.population.at(0).saveToFile(filename);
        colors_to_try--;
    }while(!gen_limit_reached);
}