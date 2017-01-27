#include <iostream>
#include "GraphLoader.h"

using namespace std;

void printUsage(char* exe);

int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            printUsage(argv[0]);
            return -1;
        }

        GraphLoader gl1(argv[1]),
                    gl2(argv[2]);

        Graph graph1(gl1.getVertices()),
              graph2(gl2.getVertices());


        vector<pair<int, int>> iso = graph1.isIsomorphic(graph2);
        if(iso.empty()) {
            cout << "Not isomorphic" << endl;
        }
        else {
            cout << "Isomorphic: " << endl;
            for(pair<int, int> p : iso) {
                cout << p.first << " --> " << p.second << endl;
            }
        }

    } catch (runtime_error e) {
        cout << e.what() << endl;
        return -1;
    }
    return 0;
}

void printUsage(char* exe) {
    cout << "Usage: " << exe << " graph1.txt graph2.txt" << endl;
}