//
// Created by Artur on 27.04.2022.
//

#include "GraphColoring.h"

int countUniqueColors(const Graph &graph) {
    std::unordered_set<int> unique_colors;
    for(const auto &vx : graph.vertices)
    {
        if(vx.getColor() != 0)
            unique_colors.insert(vx.getColor());
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

void GraphColoring::geneticAlgorithm(Graph &graph, int generation_limit) {
    std::vector<std::pair<int, std::vector<int>>> population;
    std::vector<int> parent1;
    std::vector<int> parent2;
    std::vector<int> child;
    int vertices;
    int colors;
    int population_size {10};
    GraphColoring::greedyAlgorithm(graph);
    vertices = graph.getNumberOfVertices();
    colors = graph.getNumberOfColors();
    GraphColoring::populate(population_size, population, colors, vertices);
    //GraphColoring::printPopulation(population);
    for(int k {0}; k < population.size(); k++)
    {
        GraphColoring::evaluateFitness(graph, population.at(k));
    }
    std::sort(population.begin(), population.end());
    GraphColoring::printPopulation(population);
    GraphColoring::parentSelection1(population, parent1, parent2);

    for(auto lel : parent1)
    {
        std::cout << lel << ", ";
    }
    std::cout << std::endl;
    for(auto lel : parent2)
    {
        std::cout << lel << ", ";
    }
    std::cout << std::endl;
    GraphColoring::crossover(parent1, parent2, child);
    for(auto lel : child)
    {
        std::cout << lel << ", ";
    }
    std::cout << std::endl;
    GraphColoring::mutation1(graph, child, colors);
    for(auto lel : child)
    {
        std::cout << lel << ", ";
    }
    std::cout << std::endl;
    GraphColoring::newGeneration(population_size,population,child,colors,vertices);
    GraphColoring::printPopulation(population);
}

void GraphColoring::populate(int population_size, std::vector<std::pair<int, std::vector<int>>> &population, int colors, int vertices) {
    for(int i {0}; i < population_size; i++)
    {
        population.emplace_back(std::make_pair(-1, std::vector<int>()));
        for(int j{0}; j < vertices; j++)
        {
            population.at(i).second.push_back(generateRandomNumber(1, colors));
        }
    }
}


void GraphColoring::evaluateFitness(const Graph &graph, std::pair<int, std::vector<int>> &chromosome) {
    int fitness_score {0};
    int currentVertexColor {0};
    for(int i{0}; i < graph.vertices.size(); i++)
    {
        currentVertexColor = chromosome.second.at(i);
        for(int j{0}; j < graph.vertices.at(i).adjacent.size(); j++)
        {
            if(chromosome.second.at(graph.vertices.at(i).adjacent.at(j)->getLabel() - 1) == currentVertexColor)
            {
                fitness_score++;
            }
        }
    }
    chromosome.first = fitness_score / 2;
}

void GraphColoring::printPopulation(const std::vector<std::pair<int, std::vector<int>>> &population) {
    for(int i {0}; i < population.size(); i++)
    {
        std::cout << "Fitness: " << population.at(i).first << " Chromosome:";
        for(int j {0}; j < population.at(i).second.size(); j++)
        {
            std::cout << population.at(i).second.at(j) << ", ";
        }
        std::cout << std::endl;
    }
}

void GraphColoring::parentSelection1(const std::vector<std::pair<int, std::vector<int>>> &population,
                                     std::vector<int> &parent1, std::vector<int> &parent2) {
    parent1.clear();
    parent2.clear();
    int t1, t2, t3, t4;
    do {
        t1 = generateRandomNumber(0, population.size() - 1);
        t2 = generateRandomNumber(0, population.size() - 1);
        t3 = generateRandomNumber(0, population.size() - 1);
        t4 = generateRandomNumber(0, population.size() - 1);
    }while(t1 == t2 || t1 == t3 || t1 == t4 || t2 == t3 || t2 == t4 || t3 == t4);
    std::cout << "chosen. t1 = " << t1 << " t2 = " << t2 << " t3 = " << t3 << " t4 = " << t4 << std::endl;
    if(population.at(t1).first <= population.at(t2).first)
    {
        parent1 = population.at(t1).second;
        std::cout << "parent1: " << t1 << std::endl;
    }else
    {
        parent1 = population.at(t2).second;
        std::cout << "parent1: " << t2 << std::endl;
    }
    if(population.at(t3).first <= population.at(t4).first)
    {
        parent2 = population.at(t3).second;
        std::cout << "parent2: " << t3 << std::endl;
    }else
    {
        parent2 = population.at(t4).second;
        std::cout << "parent2: " << t4 << std::endl;
    }
}

void GraphColoring::crossover(const std::vector<int> &parent1, const std::vector<int> &parent2, std::vector<int> &child) {
    int cross_point {};
    cross_point = generateRandomNumber(1, parent1.size() - 2);
    std::cout << "Cross point: " << cross_point << std::endl;
    for(int i {0}; i < parent1.size(); i++)
    {
        if(i <= cross_point)
        {
            child.push_back(parent1.at(i));
        }else
        {
            child.push_back(parent2.at(i));
        }
    }
}

void GraphColoring::mutation1(const Graph &graph, std::vector<int> &child, int colors) {
    std::set<int> colorsInUse;
    int mutated{};
    bool fit {true};
    for(int i{0}; i < graph.vertices.size(); i++)
    {
        fit = true;
        colorsInUse.clear();
        for(int j{0}; j < graph.vertices.at(i).adjacent.size(); j++)
        {
            if(child.at(graph.vertices.at(i).adjacent.at(j)->getLabel() - 1) == child.at(i))
            {
                fit = false;
            }
            colorsInUse.insert(child.at(graph.vertices.at(i).adjacent.at(j)->getLabel() - 1));
        }
        if(!fit && colorsInUse.size() < colors)
        {
            do
            {
                mutated = generateRandomNumber(1, colors);
            }while(colorsInUse.count(mutated) != 0);
            child.at(i) = mutated;
        }
    }



}

void
GraphColoring::newGeneration(int population_size, std::vector<std::pair<int, std::vector<int>>> &population, std::vector<int> &child ,int colors,
                             int vertices) {
    int start = population_size / 2;
    population.at(start) = std::make_pair(-1, child);
    start++;
    for(int i {start}; i < population_size; i++)
    {
        population.at(i) = std::make_pair(-1, std::vector<int>());
        for(int j{0}; j < vertices; j++)
        {
            population.at(i).second.push_back(generateRandomNumber(1, colors));
        }
    }

}


