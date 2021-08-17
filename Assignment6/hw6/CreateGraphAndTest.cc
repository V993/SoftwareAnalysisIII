// CSCI 335 Homework #6

// Your name: Leonardo Matone

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include "graph.h"

using namespace std;

int testGraphDriver(int argc, char **argv) {


    cout << setprecision(1) << fixed;
    
    /***********************************************************************************/
    /**                           PARSE INPUT/BUILD GRAPH                             **/
    /***********************************************************************************/
    
    // establish fstream to parse input graph file
    string currentLine;
    fstream graphInput(argv[1]);
    
    // get first line for number of vertices
    getline(graphInput, currentLine);
    int vertices = stoi(currentLine);

    // setup graph of 'vertices' number of vertices
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

        // cout << "Adding directed edge: " << vertex << " -> " << adjacentVertex << endl;
        // add the new adjacent vertex to our graph with weight:
        aGraph.addEdge(vertex, adjacentVertex, weight);
      } // line done
    } // input done

    // print graph: 
    // aGraph.printGraph();

    /***********************************************************************************/
    /**                          PARSE QUERY/TEST ADJACENCY                           **/
    /***********************************************************************************/

    // begin parsing queries:
    fstream queries(argv[2]);

    // parse the query
    while(getline(queries, currentLine)) {

      string currentValue;
      stringstream parseLine(currentLine);

      // get first vertex
      parseLine >> currentValue;
      int firstVertex = stoi(currentValue);

      // get second vertex
      parseLine >> currentValue;
      int secondVertex = stoi(currentValue);

      cout << firstVertex << " " << secondVertex << ": ";

      float adjacent = aGraph.areAdjacent(firstVertex, secondVertex);


      if (adjacent != -1.0)
        cout << "connected " << adjacent << endl;
      else
        cout << "not_connected" << endl;

    } // input done

    return 0;
}

// Do not modify anything below this line

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << " <ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    testGraphDriver(argc, argv);

    return 0;
}
