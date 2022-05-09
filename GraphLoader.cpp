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
    int verticesNum {0};
    int key {0};
    int val {0};
    if(!in_file)
    {
        std::cerr << "Error reading file - loading default instance" << std::endl;
        return {5, {{1, 0}, {2, 0}, {3,0}, {4,0}, {5,0}}};
    }

    in_file >> verticesNum; // The first line of the file contains the total number of vertices
    Graph newGraph(verticesNum);
    for(int i {0}; i < verticesNum; i++)
    {
        newGraph.vertices.emplace_back(i + 1, 0);
    }
    while(in_file >> key >> val)
    {
        Vertex *vx1 = &newGraph.vertices.at(key - 1);
        Vertex *vx2 = &newGraph.vertices.at(val - 1);
        newGraph.addEdge(vx1, vx2);
    }

    in_file.close();
    for(int j {0}; j < newGraph.getNumberOfVertices(); j++)
    {
        std::sort(newGraph.vertices.at(j).adjacent.begin(), newGraph.vertices.at(j).adjacent.end());
        newGraph.vertices.at(j).adjacent.erase(std::unique(newGraph.vertices.at(j).adjacent.begin(), newGraph.vertices.at(j).adjacent.end()), newGraph.vertices.at(j).adjacent.end());
    }
    return newGraph;
}

Graph GraphLoader::generateInstance(int vertices, float saturationPercent) {
    std::map<int, std::set<int>> adjacency;
    int max_edges {(vertices * (vertices - 1))/2}; // the formula for the maximum amount of edges in a graph
    int no_of_connections = max_edges * saturationPercent; // calculate the number of edges with a given saturation
    int tempValue;
    int tempVx;
    Graph newGraph(vertices);
    // insert the vertices into the graph
    for(int l {0}; l < vertices; l++)
    {
        newGraph.vertices.emplace_back(l + 1, 0);
        adjacency.insert({l + 1, {}});
    }

    for(int i {0}; i < no_of_connections; i++)
    {
        do
        {
            tempVx = generateRandomNumber(1, vertices);
            tempValue = generateRandomNumber(1, vertices);
        }while(tempValue == tempVx ||  adjacency.at(tempVx).count(tempValue) != 0);

        adjacency.at(tempVx).insert(tempValue);
        adjacency.at(tempValue).insert(tempVx);

        Vertex *vx1 = &newGraph.vertices.at(tempVx - 1);
        Vertex *vx2 = &newGraph.vertices.at(tempValue - 1);
        newGraph.addEdge(vx1, vx2);

    }
    for(int j {0}; j < newGraph.getNumberOfVertices(); j++)
    {
        std::sort(newGraph.vertices.at(j).adjacent.begin(), newGraph.vertices.at(j).adjacent.end());
    }
    return newGraph;
}

// If no arguments are given - generate a 100% saturated graph with a random number of vertices from the 5-500 range
Graph GraphLoader::generateInstance() {
    return generateInstance(generateRandomNumber(5, 500), 1.0);
}

void GraphLoader::saveToFile(const Graph &graph, std::string filename) {
    in_file.open("..\\Instances\\" + filename, std::fstream::out);
    in_file << graph.getNumberOfVertices() << std::endl;
    int verticesChecked {0};
    for(int i{0}; i < graph.getNumberOfVertices(); i++)
    {
        for(int j{0}; j < graph.vertices.at(i).adjacent.size(); j++)
        {
            if(graph.vertices.at(i).adjacent.at(j)->getLabel() > verticesChecked)
            {
                in_file << graph.vertices.at(i).getLabel() << " " << graph.vertices.at(i).adjacent.at(j)->getLabel() << std::endl;
            }

        }
        verticesChecked++;
    }

    in_file.close();

}
