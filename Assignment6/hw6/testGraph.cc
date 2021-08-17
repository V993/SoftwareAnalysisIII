#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include "graph.h"

using namespace std;

int main() {

    Graph testGraph(10);

    cout << testGraph.getNumVertices() << endl;
    cout << testGraph.getSizeVector() << endl;

    testGraph.addEdge(4, 1, 10.5);
    testGraph.addEdge(4, 2, 70.5);
    testGraph.addEdge(4, 5, 80.5);
    testGraph.addEdge(2, 1, 20.5);
    testGraph.addEdge(3, 2, 30.5);
    testGraph.addEdge(1, 2, 40.5);
    testGraph.addEdge(5, 1, 50.5);
    testGraph.addEdge(7, 1, 60.5);

    testGraph.printGraph();

}