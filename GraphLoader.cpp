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

    in_file >> vertices; // The first line of the file contains the total number of vertices
    for(int i {0}; i < vertices; i++)
    {
        adjacency.insert(std::pair<int, std::set<int>>(i + 1, {}));
    }
    while(in_file)
    {
        in_file >> key;
        in_file >> val;
        adjacency.at(key).insert(val);
        adjacency.at(val).insert(key);
    }

    in_file.close();
    return {vertices, adjacency};
}

Graph GraphLoader::generateInstance(int vertices, float saturationPercent) {
    std::map<int, std::set<int>> adjacency;
    int max_edges {(vertices * (vertices - 1))/2}; // the formula for the maximum amount of edges in a graph
    int no_of_connections = max_edges * saturationPercent; // calculate the number of edges with a given saturation
    int tempValue;
    int tempVx;
    // insert the vertices into the graph
    for(int l {0}; l < vertices; l++)
    {
        adjacency.insert({l + 1, {}});
    }

    for(int i {0}; i < no_of_connections; i++)
    {
        do
        {
            tempVx = generateRandomNumber(1, vertices);
            tempValue = generateRandomNumber(1, vertices);
        }while(tempValue == tempVx || adjacency.at(tempVx).count(tempValue) != 0);

        adjacency.at(tempVx).insert(tempValue);
        adjacency.at(tempValue).insert(tempVx);


    }
    return {vertices, adjacency};
}

// If no arguments are given - generate a 100% saturated graph with a random number of vertices from the 5-500 range
Graph GraphLoader::generateInstance() {
    return generateInstance(generateRandomNumber(5, 500), 1.0);
}
