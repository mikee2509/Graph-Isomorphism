#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <list>
#include <vector>

class Graph {
public:
    class Vertex;

private:
    std::vector<Vertex*> vertices;
    unsigned long numOfVertices;

public:
    Graph(std::vector<Vertex*> v) : vertices(v), numOfVertices(v.size()) {}
    virtual ~Graph();

//    void print();
};

class Graph::Vertex {
    friend class Graph;
    int number;
    std::list<int> neighbours;

public:
    Vertex(int num, std::list<int> ngh) : number(num), neighbours(ngh) {}
};


#endif //GRAPHS_GRAPH_H
