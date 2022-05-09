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

void GraphLoader::loadInstance(const std::string &filename, Graph &graph) {
    in_file.open("..\\Instances\\" + filename);
    int verticesNum {0};
    int key {0};
    int val {0};
    if(!in_file)
    {
        std::cerr << "Error reading file - loading default instance" << std::endl;
    }

    in_file >> verticesNum; // The first line of the file contains the total number of vertices
    graph.setNumberOfVertices(verticesNum);
    for(int i {0}; i < verticesNum; i++)
    {
        graph.vertices.emplace_back(i + 1, 0);
    }
    while(in_file >> key >> val)
    {
        Vertex *vx1 = &graph.vertices.at(key - 1);
        Vertex *vx2 = &graph.vertices.at(val - 1);
        graph.addEdge(vx1, vx2);
    }

    in_file.close();
    for(int j {0}; j < graph.getNumberOfVertices(); j++)
    {
        std::sort(graph.vertices.at(j).adjacent.begin(), graph.vertices.at(j).adjacent.end());

        // Delete duplicates (in case the file is of a different format - such cases exist among the provided files)
        // Some files do not mention the same connection multiple times (for example 1->5 assures that 5->1 exists, hence the latter is not in the file)
        // However there are files that allow duplicates (for example both 1->5 and 5->1 are present in the file)
        graph.vertices.at(j).adjacent.erase(std::unique(graph.vertices.at(j).adjacent.begin(), graph.vertices.at(j).adjacent.end()), graph.vertices.at(j).adjacent.end());
    }
}

void GraphLoader::generateInstance(int vertices, float saturationPercent, Graph &graph) {
    std::map<int, std::set<int>> adjacency; // A helper map used to help keep track of current connections.
    int max_edges {(vertices * (vertices - 1))/2}; // the formula for the maximum amount of edges in a graph
    int no_of_connections = max_edges * saturationPercent; // calculate the number of edges with a given saturation
    int tempValue;
    int tempVx;
    graph.setNumberOfVertices(vertices);
    // insert the vertices into the graph
    for(int l {0}; l < vertices; l++)
    {
        graph.vertices.emplace_back(l + 1, 0);
        adjacency.insert({l + 1, {}});
    }

    for(int i {0}; i < no_of_connections; i++)
    {
        do
        {
            tempVx = generateRandomNumber(1, vertices);
            tempValue = generateRandomNumber(1, vertices);
        }while(tempValue == tempVx ||  adjacency.at(tempVx).count(tempValue) != 0); // Helper map used to check if a connection already exist. A relic from the previous, vastly different version. To be changed.

        adjacency.at(tempVx).insert(tempValue);
        adjacency.at(tempValue).insert(tempVx);

        Vertex *vx1 = &graph.vertices.at(tempVx - 1);
        Vertex *vx2 = &graph.vertices.at(tempValue - 1);
        graph.addEdge(vx1, vx2);

    }
    for(int j {0}; j < graph.getNumberOfVertices(); j++)
    {
        std::sort(graph.vertices.at(j).adjacent.begin(), graph.vertices.at(j).adjacent.end());
    }
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
