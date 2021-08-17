// CSCI 335 Homework #6

// Your name: Leonardo Matone
 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "graph.h"

using namespace std;

int findPathDriver(int argc, char **argv) {

    /***********************************************************************************/
    /**                           PARSE INPUT/BUILD GRAPH                             **/
    /***********************************************************************************/
    
    // establish fstream to parse input graph file
    string currentLine;
    fstream graphInput(argv[1]);
    
    // get first line for number of vertices
    getline(graphInput, currentLine);
    int vertices = stoi(currentLine);

    // setup graph of 'vertices' number
    Graph aGraph(vertices);

    // Parse the input
    while(getline(graphInput, currentLine)) {
      // Parse the line:
      string currentValue;
      stringstream parseLine(currentLine);

      // get the first vertex in the line, convert to int
      parseLine >> currentValue;
      int vertex = stoi(currentValue);

      // parse remainder of line
      while(parseLine >> currentValue) {
        // the save the next vertex: 
        int adjacentVertex = stoi(currentValue);

        // get/save the weight, convert to float
        parseLine >> currentValue;
        float weight = stof(currentValue);

        // add the new adjacent vertex to our graph with weight:
        aGraph.addEdge(vertex, adjacentVertex, weight);
      } // line done
    } // input done

    // print graph: 
    // aGraph.printGraph();

    /***********************************************************************************/
    /**                             FIND SHORTEST PATH                                **/
    /***********************************************************************************/
    
    int startingVertex = stoi(argv[2]);

    aGraph.findShortestPath(startingVertex);

    return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    findPathDriver(argc, argv);

    return 0;
}
