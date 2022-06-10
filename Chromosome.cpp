//
// Created by Artur on 08.06.2022.
//

#include "Chromosome.h"

Chromosome::Chromosome(Graph* graphptr, int vertices, int colors)
: genes(vertices, 0), fitness{-1}, graph{graphptr}, max_colors{colors} {

}

void Chromosome::randomizeGenes() {
    for(int i {0}; i < genes.size(); i++)
    {
        genes.at(i) = util::generateRandomNumber(1, max_colors);
    }

}

void Chromosome::evaluateFitness() {
    int currentVertexColor {0};
    int fitness_score {0};
    for(int i{0}; i < graph->vertices.size(); i++)
    {
        currentVertexColor = genes.at(i);
        for(int j{graph->optimalIndices.at(i)}; j < graph->vertices.at(i).adjacent.size(); j++)
        {
            if(j == -1)
            {
                break;
            }
            if(genes.at(graph->vertices.at(i).adjacent.at(j)->getLabel() - 1) == currentVertexColor)
            {
                fitness_score++;
            }
        }
    }
    fitness = fitness_score;
}

bool Chromosome::operator<(const Chromosome &rhs) {
    if(rhs.fitness > fitness)
        return true;
    else
        return false;
}

bool Chromosome::operator>(const Chromosome &rhs) {
    if(rhs.fitness < fitness)
        return true;
    else
        return false;
}

void Chromosome::resetData(const std::vector<int> &new_genes, int new_fitness) {
    Chromosome::setGenes(new_genes);
    Chromosome::setFitness(new_fitness);
}

void Chromosome::print() {
    std::cout << "Fitness: " << fitness << " Genes: ";
    for(int i {0}; i < genes.size(); i++)
    {
        std::cout << genes.at(i) << ", ";
    }
    std::cout << std::endl;
}

void Chromosome::mutate(double probability) {
    double check = util::generateRandomFloat(0.0, 1.0);
    int position {0};
    if(check <= probability)
    {
        position = util::generateRandomNumber(0, genes.size() - 1);
        genes.at(position) = util::generateRandomNumber(1, max_colors);
    }
}
