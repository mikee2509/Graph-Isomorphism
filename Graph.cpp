#include "Graph.h"

using namespace std;

Graph::Graph(std::vector<Vertex> v) : numOfVertices(v.size()) {
    vertices = v;
    sort(vertices.begin(), vertices.end(),
         [](const Vertex &a, const Vertex &b){ return a.degree < b.degree; });
}

bool Graph::operator==(const Graph &rhs) const {
    return numOfVertices == rhs.numOfVertices &&
           is_permutation(vertices.begin(), vertices.end(), rhs.vertices.begin());
}

bool Graph::operator!=(const Graph &rhs) const {
    return !(rhs == *this);
}

std::vector<std::pair<int, int>> Graph::isIsomorphic(const Graph &other) const {
    std::vector<std::pair<int, int>> bijection;
    if (!doDegreesMatch(other))
        return bijection;

    Graph copy;
    int permutation[numOfVertices];
    for(int i = 0; i < numOfVertices; i++)
        permutation[i] = i;

    do {
        copy = *this;
        copy.relabelGraph(permutation);
        if(other == copy) {
            for (int i = 0; i < numOfVertices; ++i)
                bijection.push_back(make_pair(i, permutation[i]));
            break;
        }
    } while(std::next_permutation(permutation, permutation+numOfVertices));

    return bijection;
}

bool Graph::doDegreesMatch(const Graph &other) const {
    return is_permutation(vertices.begin(), vertices.end(), other.vertices.begin(), other.vertices.end(),
                          [](const Vertex &a, const Vertex &b){ return a.degree==b.degree; });
}

void Graph::relabelGraph(const int *labels) {
    for (int i = 0; i < numOfVertices; ++i) {
        vertices[i].number = labels[vertices[i].number];
        for(auto it = vertices[i].neighbours.begin(); it!=vertices[i].neighbours.end(); ++it) {
            *it = labels[*it];
        }
    }
}

bool Graph::Vertex::operator==(const Graph::Vertex &rhs) const {
    return number == rhs.number &&
           degree == rhs.degree &&
           is_permutation(neighbours.begin(), neighbours.end(), rhs.neighbours.begin());
}

bool Graph::Vertex::operator!=(const Graph::Vertex &rhs) const {
    return !(rhs == *this);
}
