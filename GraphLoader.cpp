#include "GraphLoader.h"
using namespace std;

GraphLoader::GraphLoader(const char *file) {
    ifs.open(file);
    if(!ifs) throw runtime_error("Could not open" + string(file));
}

std::vector<Graph::Vertex *> GraphLoader::getVertices() {
    unsigned numOfVertices = 0;
    int a, b;
    ifs >> numOfVertices;

    //Get vector of unique vertices' labels
    vector<int> vec;
    vec.reserve(numOfVertices);
    while(ifs >> a >> b) {
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
        for (int i = 0; i < numOfIsolatedVertices; ++i) {
            vec.push_back(vec.back()+1);
        }
    }
    else if(vecSize > numOfVertices) {
        throw runtime_error("File error");
    }

    //Create lists of neighbours
    unordered_map<int, std::list<int>> neighbours;
    neighbours.reserve(vecSize);

    ifs.clear();
    ifs.seekg(ifs.beg);
    ifs.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    while(ifs >> a >> b) {
        neighbours[a].push_back(b);
        neighbours[b].push_back(a);
    }

    Graph::Vertex *temp;
    vector<Graph::Vertex*> vertices;
    vertices.reserve(vec.size());
    for(int i : vec) {
        neighbours[i].sort();
        temp = new Graph::Vertex(i, neighbours[i]);
        vertices.push_back(temp);
    }
    return vertices;
}
