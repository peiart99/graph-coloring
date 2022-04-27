## A University Project for Combinatorial Optimization class

The goal of the project is to explore solutions to the **Graph Coloring Problem**.

The fist algorithm that will be implemented is the greedy algorithm. After that the task is to implement a chosen **metaheuristic** and compare it's efficiency to the previously mentioned greedy algorithm.

### Current functionality:
- Loading a graph from a file (format below)
- Generating a random graph by providing the number of vertices and the saturation
- Coloring a graph with the greedy algorithm

### To-do list (development branch):
- Implementing a metaheuristic (to be chosen)
- Creating a UI to make working with this program easier (automating gathering large samples of data)


###The enforced format for graph instances:

The first line represents the number of vertices. All of the lines after that represent the connections between 2 vertices.
```
5
1 2
1 5
2 3
3 4
4 5
```
