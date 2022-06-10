//
// Created by Artur on 08.06.2022.
//

#ifndef GRAPH_COLORING_CHROMOSOME_H
#define GRAPH_COLORING_CHROMOSOME_H
#include <utility>
#include <vector>
#include "Graph.h"
#include "Utility.h"

class Chromosome {
private:
    int fitness;
    int max_colors;
    Graph* graph;
public:
    std::vector<int> genes;
    Chromosome(Graph* graphptr, int vertices, int colors);
    ~Chromosome() = default;
    void print();
    void randomizeGenes();
    void resetData(const std::vector<int> &new_genes, int new_fitness);
    void evaluateFitness();
    void mutate(double probability);
    [[nodiscard]] int getFitness() const {return fitness;};
    void setGenes(const std::vector<int> &newGenes) {genes = newGenes;};
    int getSize() {return genes.size();};
    void setFitness(int new_fitness) {fitness = new_fitness;};
    void setMaxColors(int new_colors) {max_colors = new_colors;};
    bool operator<(const Chromosome &rhs);
    bool operator>(const Chromosome &rhs);


};


#endif //GRAPH_COLORING_CHROMOSOME_H
