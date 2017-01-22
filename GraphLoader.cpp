#include "GraphLoader.h"
using namespace std;

GraphLoader::GraphLoader(const char *file) {
    ifs.open(file);
    if(!ifs) throw runtime_error("Could not open" + string(file));
}

std::vector<Graph::Vertex> GraphLoader::getVertices() {
    unsigned numOfVertices = 0;
    int a, b;
    ifs >> numOfVertices;

    //Get vector of unique vertices' labels
    vector<int> vec;
    vec.reserve(numOfVertices);
    while(ifs >> a >> b) {
        if(a < 0 || b < 0) throw runtime_error("Labels of vertices must be unsigned numbers");
        vec.push_back(a);
        vec.push_back(b);
    }
    sort(vec.begin(), vec.end());
    auto it = unique(vec.begin(), vec.end());
    vec.erase(it, vec.end());

    //Check if there are isolated vertices
    unsigned vecSize = static_cast<int>(vec.size());
    if(vecSize < numOfVertices) {
        int numOfIsolatedVertices = numOfVertices-vecSize;
        int uniqueLabel = 0;
        for (int i = 0; i < numOfIsolatedVertices; ++i) {
            while(find(vec.begin(), vec.end(), uniqueLabel) != vec.end()) {
                ++uniqueLabel;
            }
            vec.push_back(uniqueLabel);
        }
        sort(vec.begin(), vec.end());
    }
    else if(vecSize > numOfVertices) {
        throw runtime_error("File error, check the number of vertices");
    }

    if(vec.back()+1 != numOfVertices) {
        throw runtime_error("Invalid edge to vertex " + to_string(vec.back())
                            + ", check the number of vertices");
    }

    //Create lists of neighbours
    unordered_map<int, std::list<int>> neighbours;
    neighbours.reserve(vecSize);

    ifs.clear();
    ifs.seekg(ifs.beg);
    ifs.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    while(ifs >> a >> b) {
        if(find(neighbours[a].begin(), neighbours[a].end(), b) == neighbours[a].end()) {
            neighbours[a].push_back(b);
            neighbours[b].push_back(a);
        }
        else throw runtime_error("Duplicate edge between " + to_string(a) + " and " + to_string(b));
    }

    vector<Graph::Vertex> vertices;
    vertices.reserve(vec.size());
    for(int i : vec) {
        vertices.push_back(Graph::Vertex(i, neighbours[i]));
    }
    return vertices;
}
