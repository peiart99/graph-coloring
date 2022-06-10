//
// Created by Artur on 08.06.2022.
//

#include "Population.h"

Population::Population(int size, int col)
: population_size{size}, max_colors{col}
{

}

void Population::generatePopulation(Graph &graph) {
    for(int i{0}; i < population_size; i++)
    {
        population.emplace_back(&graph, graph.getNumberOfVertices(), max_colors);
        population.at(i).randomizeGenes();
        population.at(i).evaluateFitness();
    }
}

void Population::shufflePopulation() {
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(population), std::end(population), rng);
}

void Population::print() {
    std::cout << "========================================================================================" << std::endl;
    for(int i {0}; i < population.size(); i++)
    {
        population.at(i).print();
    }
    std::cout << "========================================================================================" << std::endl;
}

void Population::sortPopulation() {
    std::sort(population.begin(), population.end());
    best_fitness = population.at(0).getFitness();
}

void Population::selection1() {
    std::vector<Chromosome> new_population;
    for(int i {0}; i < 2; i++)
    {
        Population::shufflePopulation();
        for(int j{0}; j < population_size - 1; j+=2)
        {
            if(population.at(j) < population.at(j+1))
            {
                new_population.push_back(population.at(j));
            }else
            {
                new_population.push_back(population.at(j+1));
            }
        }
    }

    if(new_population.size() == population_size)
    {
        //std::cout << "Selection1: Passed" << std::endl;
        population = new_population;
        Population::sortPopulation();
    }else
    {
        std::cout << "Selection1: ERROR(size is wrong)" << std::endl;
    }

}

void Population::selection2() {
    std::vector<Chromosome> new_population;
    std::vector<double> fitness_prob(population_size, 0);
    int total_fitness {0};
    double lower_bound {0.0};
    double total_fitness_real {0.0};
    double current_real {0.0};
    double roulette {0.0};
    for(auto &specimen : population)
    {
        total_fitness += specimen.getFitness();
    }
    for(int i {0}; i < population.size(); i++)
    {
        current_real = static_cast<double>(population.at(i).getFitness()) / total_fitness;
        fitness_prob.at((population_size - 1) - i) = current_real + total_fitness_real;
        //std::cout << "Prob: " << fitness_prob.at((population_size - 1) - i) << std::endl;
        total_fitness_real += current_real;
    }
    for(int j{0}; j < population.size(); j++)
    {
        roulette = util::generateRandomFloat(0.0, 1.0);
        //std::cout << roulette << std::endl;
        lower_bound = 0;
        for(int k{0}; k < population.size(); k++)
        {
            if(k < population.size() - 1)
            {
                lower_bound = fitness_prob.at(k + 1);
            }
            else
            {
                lower_bound = 0.0;
            }
            if(roulette <= fitness_prob.at(k) && roulette > lower_bound)
            {
                new_population.push_back(population.at(k));
                break;
            }
        }

    }

    if(new_population.size() == population_size)
    {
        //std::cout << "Selection2: Passed" << std::endl;
        population = new_population;
        Population::sortPopulation();
    }else
    {
        std::cout << "Selection2: ERROR(size is wrong)" << std::endl;
    }
}

void Population::crossover(int generation) {
    std::vector<Chromosome> new_population;
    int cross_point {0};
    int temp {0};
    for(int i {0}; i < population.size() - 1; i += 2)
    {
        if(best_fitness > 4)
        {
        cross_point = util::generateRandomNumber(1, population.at(i).getSize() - 1);
        //std::cout << cross_point << std::endl;
        for(int j {cross_point}; j < population.at(i).getSize(); j++)
        {
            temp = population.at(i).genes.at(j);
            population.at(i).genes.at(j) = population.at(i+1).genes.at(j);
            population.at(i+1).genes.at(j) = temp;

        }

            population.at(i).mutate(0.2);
            population.at(i+1).mutate(0.2);
        }else
        {
            population.at(i).mutate(0.9);
            population.at(i+1).mutate(0.9);
        }
    }
}

void Population::evaluateAllFitness() {
    for(int i {0}; i < population.size(); i+=4)
    {
        std::thread t1(&Chromosome::evaluateFitness, &population.at(i));
        std::thread t2(&Chromosome::evaluateFitness, &population.at(i+1));
        std::thread t3(&Chromosome::evaluateFitness, &population.at(i+2));
        std::thread t4(&Chromosome::evaluateFitness, &population.at(i+3));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}

