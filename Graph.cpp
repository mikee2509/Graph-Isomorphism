//#include <iostream>
#include "Graph.h"

using namespace std;

Graph::~Graph() {
    for(Vertex* v : vertices) {
        delete v;
    }
}

//void Graph::print() {
//    for(Vertex* v : vertices) {
//        cout << v->number << ": ";
//        for(int i : v->neighbours) {
//            cout << i << " ";
//        }
//        cout << endl;
//    }
//}
