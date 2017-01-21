#ifndef GRAPHS_GRAPHLOADER_H
#define GRAPHS_GRAPHLOADER_H

#include "Graph.h"
#include <algorithm>
#include <unordered_map>
#include <list>
#include <fstream>

class GraphLoader {
    std::ifstream ifs;
public:
    GraphLoader(const char* file);
    std::vector<Graph::Vertex*> getVertices();
};


#endif //GRAPHS_GRAPHLOADER_H
