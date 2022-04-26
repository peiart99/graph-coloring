//
// Created by Artur on 26.04.2022.
//

#include "GraphLoader.h"

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

    return {vertices, adjacency};
}
