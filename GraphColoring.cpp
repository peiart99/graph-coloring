//
// Created by Artur on 27.04.2022.
//

#include "GraphColoring.h"
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

void GraphColoring::geneticAlgorithm(Graph &graph, int generation_limit) {
    std::vector<std::pair<int, std::vector<int>>> population;
    std::vector<int> parent1;
    std::vector<int> parent2;
    std::vector<int> child;
    std::vector<int> winner;
    int vertices;
    int colors;
    int population_size {50};
    int generation_count {0};
    int mutation_check {0};
    int mutation_rate {70}; // 0 - 100 (0% - 100%)
    bool solution_found {false};
    bool lowest_found {false};
    bool mut2 {false};
    GraphColoring::greedyAlgorithm(graph);
    vertices = graph.getNumberOfVertices();
    colors = graph.getNumberOfColors();
    do {
        population.clear();
        generation_count = 0;
        solution_found = false;
        parent1.clear();
        parent2.clear();
        child.clear();
        GraphColoring::populate(population_size, population, colors, vertices);
        //GraphColoring::printPopulation(population);
        for(int k {0}; k < population.size(); k++)
        {
            GraphColoring::evaluateFitness(graph, population.at(k));
        }
        generation_count++;
        std::sort(population.begin(), population.end());
        if(population.at(0).first == 0)
        {
            winner = population.at(0).second;
            colors = countUniqueColorsChromosome(winner) - 1;
            continue;
        }
        else
        {
            for(int i{0}; i < generation_limit; i++)
            {
                auto start = std::chrono::high_resolution_clock::now();
                std::cout << generation_count << std::endl;
                parent1.clear();
                parent2.clear();
                child.clear();
                mutation_check = generateRandomNumber(1,100);
                if(population.at(0).first > 4)
                {
                    GraphColoring::parentSelection1(population, parent1, parent2);
                    GraphColoring::crossover(parent1, parent2, child);
                    if(mutation_check < mutation_rate)
                        GraphColoring::mutation1(graph, child, colors);

                    mut2 = false;
                }else
                {
                    //parent2 = population.at(1).second;
                    //GraphColoring::crossover(parent1, parent2, child);
                    //if(mutation_check < 70)
                    GraphColoring::mutation2(graph, population.at(0).second, colors);
                    GraphColoring::evaluateFitness(graph, population.at(0));
                    mut2 = true;
                }
                GraphColoring::newGeneration(population_size,population,child,colors,vertices, mut2);
                auto startF = std::chrono::high_resolution_clock::now();
//                for(int j {population_size/2}; j < population.size(); j++)
//                {
//                    GraphColoring::evaluateFitness(graph, population.at(j));
//                }
                for(int j {(population_size/2) + 3} ; j < population.size(); j += 4)
                {
                    std::thread fitness1(&GraphColoring::evaluateFitness, this, std::ref(graph), std::ref(population.at(j-3)));
                    std::thread fitness2(&GraphColoring::evaluateFitness, this, std::ref(graph), std::ref(population.at(j-2)));
                    std::thread fitness3(&GraphColoring::evaluateFitness, this, std::ref(graph), std::ref(population.at(j-1)));
                    std::thread fitness4(&GraphColoring::evaluateFitness, this, std::ref(graph), std::ref(population.at(j)));

                    fitness1.join();
                    fitness2.join();
                    fitness3.join();
                    fitness4.join();
                }
                GraphColoring::evaluateFitness(graph, population.at(49));
                auto stopF = std::chrono::high_resolution_clock::now();
                auto durationF = std::chrono::duration_cast<std::chrono::milliseconds>(stopF - startF);
                std::cout << "Elapsed time(Fitness): " << durationF.count() << " ms" << std::endl;
                std::sort(population.begin(), population.end());
                generation_count++;
                if(population.at(0).first == 0)
                {
                    solution_found = true;
                    break;
                }
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                std::cout << "Elapsed time(Generation): " << duration.count() << " ms" << std::endl;
            }

            if(solution_found)
            {
                std::cout << "Wygrane generacja: " << generation_count << std::endl;
                winner = population.at(0).second;
                colors = countUniqueColorsChromosome(winner) - 1;
            }else
            {
                std::cout << "PRzegrane tje" << std::endl;
                lowest_found = true;
            }
        }
//        std::cout << "Fitness: " << population.at(0).first << " Chromosome: ";
//        for(auto lel : population.at(0).second)
//        {
//            std::cout << lel << ", ";
//        }
//        std::cout << std::endl;
//        std::cout << "Kolory: " << countUniqueColorsChromosome(population.at(0).second) << std::endl;
    }while(!lowest_found);

    for(auto lel : winner)
    {
        std::cout << lel << ", ";
    }
    std::cout << std::endl;
    std::cout << "Kolory: " << countUniqueColorsChromosome(winner) << std::endl;

}

void GraphColoring::populate(int population_size, std::vector<std::pair<int, std::vector<int>>> &population, int colors, int vertices) {
    //auto start = std::chrono::high_resolution_clock::now();
    for(int i {0}; i < population_size; i++)
    {
        population.emplace_back(std::make_pair(-1, std::vector<int>()));
        for(int j{0}; j < vertices; j++)
        {
            population.at(i).second.push_back(generateRandomNumber(1, colors));
        }
    }
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout << "Elapsed time(Populate): " << duration.count() << " ms" << std::endl;
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
        std::cout << "Fitness: " << population.at(i).first << " Chromosome: ";
        for(int j {0}; j < population.at(i).second.size(); j++)
        {
            std::cout << population.at(i).second.at(j) << ", ";
        }
        std::cout << std::endl;
    }
}

void GraphColoring::parentSelection1(const std::vector<std::pair<int, std::vector<int>>> &population,
                                     std::vector<int> &parent1, std::vector<int> &parent2) {
    //auto start = std::chrono::high_resolution_clock::now();
    parent1.clear();
    parent2.clear();
    int t1, t2, t3, t4;
    do {
        t1 = generateRandomNumber(0, population.size() - 1);
        t2 = generateRandomNumber(0, population.size() - 1);
        t3 = generateRandomNumber(0, population.size() - 1);
        t4 = generateRandomNumber(0, population.size() - 1);
    }while(t1 == t2 || t1 == t3 || t1 == t4 || t2 == t3 || t2 == t4 || t3 == t4);
    //std::cout << "chosen. t1 = " << t1 << " t2 = " << t2 << " t3 = " << t3 << " t4 = " << t4 << std::endl;
    if(population.at(t1).first <= population.at(t2).first)
    {
        parent1 = population.at(t1).second;
        //std::cout << "parent1: " << t1 << std::endl;
    }else
    {
        parent1 = population.at(t2).second;
        //std::cout << "parent1: " << t2 << std::endl;
    }
    if(population.at(t3).first <= population.at(t4).first)
    {
        parent2 = population.at(t3).second;
        //std::cout << "parent2: " << t3 << std::endl;
    }else
    {
        parent2 = population.at(t4).second;
        //std::cout << "parent2: " << t4 << std::endl;
    }
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout << "Elapsed time(Parent): " << duration.count() << " ms" << std::endl;
}

void GraphColoring::crossover(const std::vector<int> &parent1, const std::vector<int> &parent2, std::vector<int> &child) {
    //auto start = std::chrono::high_resolution_clock::now();
    int cross_point {};
    cross_point = generateRandomNumber(1, parent1.size() - 2);
    //std::cout << "Cross point: " << cross_point << std::endl;
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
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout << "Elapsed time(Crossover): " << duration.count() << " ms" << std::endl;
}

void GraphColoring::mutation1(const Graph &graph, std::vector<int> &child, int colors) {
    //auto start = std::chrono::high_resolution_clock::now();
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
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout << "Elapsed time(Mutation1): " << duration.count() << " ms" << std::endl;
}

void
GraphColoring::newGeneration(int population_size, std::vector<std::pair<int, std::vector<int>>> &population, std::vector<int> &child ,int colors,
                             int vertices, bool enterChild) {
    auto startCl = std::chrono::high_resolution_clock::now();
    int start = population_size / 2;
    if(!enterChild)
    {
        population.at(start) = std::make_pair(-1, child);
        start++;
    }
    for(int i {start}; i < population_size; i++)
    {
        population.at(i) = std::make_pair(-1, std::vector<int>());
        for(int j{0}; j < vertices; j++)
        {
            population.at(i).second.push_back(generateRandomNumber(1, colors));
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - startCl);
    //std::cout << "Elapsed time(NewGen): " << duration.count() << " ms" << std::endl;

}

void GraphColoring::mutation2(const Graph &graph, std::vector<int> &child, int colors) {
    auto start = std::chrono::high_resolution_clock::now();
    int mutated{};
    bool fit {true};
    for(int i{0}; i < graph.vertices.size(); i++)
    {
        fit = true;
        for(int j{0}; j < graph.vertices.at(i).adjacent.size(); j++)
        {
            if(child.at(graph.vertices.at(i).adjacent.at(j)->getLabel() - 1) == child.at(i))
            {
                fit = false;
            }
        }
        if(!fit)
        {
            mutated = generateRandomNumber(1, colors);
            child.at(i) = mutated;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout << "Elapsed time(Mutation2): " << duration.count() << " ms" << std::endl;
}


