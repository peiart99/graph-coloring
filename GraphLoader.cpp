//
// Created by Artur on 26.04.2022.
//

#include "GraphLoader.h"

int generateRandomNumber(int min_value, int max_value)
{
    std::default_random_engine eng;
    unsigned long int t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    eng.seed(t);
    static std::mt19937 gen(eng());
    std::uniform_int_distribution<> dist(min_value,max_value);
    return dist(gen);
}
Graph GraphLoader::loadInstance(const std::string &filename) {
    in_file.open("..\\Instances\\" + filename);
    int vertices {0};
    int key {0};
    int val {0};
    std::map<int, std::set<int>> adjacency;
    if(!in_file)
    {
        std::cerr << "Error reading file - loading default instance" << std::endl;
        return {5, {{1,{2,5}},{2,{3,1}},{3,{2,4}},{4,{3,5}},{5,{4,1}}}};
    }

    in_file >> vertices;
    for(int i {0}; i < vertices; i++)
    {
        adjacency.insert(std::pair<int, std::set<int>>(i + 1, {}));
    }
    while(in_file)
    {
        in_file >> key;
        in_file >> val;
        adjacency.at(key).insert(val);
    }

    // The enforced model instance doesn't include entries for the last vertex. The loop below searches through n-1 vertices and looks if they are adjacent to the nth vertex.
    // This way the adjacency list graph representation is more clear and easier to work with when already loaded.
    for(const auto &adjval: adjacency)
    {
        if(adjval.second.count(vertices) > 0)
        {
            adjacency.at(vertices).insert(adjval.first);
        }
    }

    in_file.close();
    return {vertices, adjacency};
}

Graph GraphLoader::generateInstance(int vertices) {
    std::map<int, std::set<int>> adjacency;
    int no_of_connections;
    int tempValue;
    for(size_t l {0}; l < vertices; l++)
    {
        adjacency.insert({l + 1, {}});
    }
    for(size_t i {0}; i < vertices; i++)
    {
        no_of_connections = generateRandomNumber(1, vertices-1);
        for(size_t k {0}; k < no_of_connections; k++)
        {
            tempValue = generateRandomNumber(1, vertices-1);
            while(tempValue == i + 1)
            {
                tempValue = generateRandomNumber(1, vertices-1);
            }
            adjacency.at(i + 1).insert(tempValue);
            adjacency.at(tempValue).insert(i + 1);
        }

    }
    return {vertices, adjacency};
}

Graph GraphLoader::generateInstance() {
    return generateInstance(generateRandomNumber(5, 50));
}
