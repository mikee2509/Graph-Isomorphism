#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>
#include <vector>
#include <algorithm>

class Graph {
public:
    class Vertex;

private:
    std::vector<Vertex> vertices;
    unsigned long numOfVertices;

public:
    Graph() : numOfVertices(0) {}
    Graph(std::vector<Vertex> v);
    Graph(const Graph& other) : vertices(other.vertices), numOfVertices(other.numOfVertices) {}

    bool operator==(const Graph &rhs) const;
    bool operator!=(const Graph &rhs) const;

    std::vector<std::pair<int, int>> isIsomorphic(const Graph &other) const;
    bool doDegreesMatch(const Graph &other) const;
    void relabelGraph(const int *labels);
};

class Graph::Vertex {
    friend class Graph;
    int number;
    unsigned long degree;
    std::list<int> neighbours;

public:
    Vertex(int num, std::list<int> ngh) : number(num), degree(ngh.size()), neighbours(ngh) {
        neighbours.sort();
    }

    bool operator==(const Vertex &rhs) const;
    bool operator!=(const Vertex &rhs) const;
};


#endif //GRAPHS_GRAPH_H
