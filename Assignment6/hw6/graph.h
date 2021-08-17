#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <list>
#include <iostream>
#include <iomanip>

using namespace std;

// Graph class
//
// CONSTRUCTION: with an optional vertex-count "vertices"
class Graph {
    public:

        // default constructor
        Graph() : vertices{0} {}

        /** Constructor
         * @param vertices the number of vertices in the graph */
        Graph(int vertices) {
            this->vertices = vertices;
            for (int i = 0; i <= vertices; i++) {
                listVertices.push_back(Vertex());
            }
        }

        // add new edge to graph
        void addEdge(int x, int y, float wei) {
            // establish new vertex
            Vertex new_vertex(y, wei);
            // add to adjacent list
            listVertices[x].adjacentList.push_back(new_vertex);
            // set value of vertex
            listVertices[x].vertex = x;
        }

        // print the graph 
        void printGraph() {
            // Iterate through each vertex
            cout << "Number of Vertices: " << vertices << endl << endl;

            cout << "Vertex #  |    adjacentNode, weight   |" << endl;
            // loop through each vertex
            for (int i = 1; i <= vertices; i++) {
                cout << "Vertex: " << i << " | ";
                // loop through each connected vertex
                for (Vertex current_vertex : listVertices[i].adjacentList) {
                    cout << current_vertex.vertex << ", " << current_vertex.weight << " | ";
                }
                cout << endl;
            }
        }

        // test if adjacent, return the weight if connected
        float areAdjacent(int a, int b) {
            int test = listVertices[a].adjacentList.size();

            // loop through adjacent vertices, return weight if connected
            for (Vertex current_vertex : listVertices[a].adjacentList) 
                if (current_vertex.vertex == b)
                    return current_vertex.weight;

            return -1;
        }

        // find shortest path dijkstra algorithm wrapper
        void findShortestPath(int startVertex) {

            // arbitrary large number, aptly named of course
            int beegNoomber = 10000; 

            // if the startVertex is invalid, dip
            if (startVertex < 1 || startVertex > listVertices.size()) {
                cout << "Invalid vertex. " << endl;
                return;
            }

            // Find shortest path
            Dijkstra(startVertex);

            // Iterate through vertices list and output the shortest paths

            for (int i = 1; i <= vertices; i++) {
                Vertex curr_vertex = listVertices[i];
                cout << curr_vertex.vertex << ": ";

                // if the weight is the beegNoomber, it's impossible to reach! 
                if (curr_vertex.weight = beegNoomber) 
                    cout << "not_possible" << endl;
                else { // otherwise, proceed:

                    int previous = curr_vertex.previous_in_path;

                    // construct the path from the results of Dijkstra.
                    // store in shortest_path vector, and ouput:
                    while (previous != -1) {
                        
                        // find previous vertex
                        Vertex previousVertex = listVertices[previous];
                        // push this vertex into the shortest path 
                        listVertices[i].shortest_path.push_back(previousVertex);
                        // set the value of curr_vertex to the preivousVertex
                        curr_vertex = previousVertex;

                    }

                    /*********************************/
                    /*             OUTPUT            */
                    /*********************************/

                    for (int j = listVertices[i].shortest_path.size()-1; j >= 0; j--) {
                        cout << listVertices[i].shortest_path[j].vertex << " ";
                    }
                    cout << listVertices[i].vertex;

                    cout << setprecision(1) << fixed;

                    cout << " cost: " << listVertices[i].weight << endl;
                }
            }
        }

        // dijkstra shortest path algorithm
        void Dijkstra(int startVertex) {

            // arbitrary large number, aptly named of course
            int beegNoomber = 10000;

            // setup the binary heap of vertexes
            BinaryHeap<Vertex> container;

            // reset values for our pathfinding
            for (int i = 1; i <= vertices; i++) {
                listVertices[i].visited = false;
                listVertices[i].weight = beegNoomber;
                listVertices[i].previous_in_path = -1;
            }

            // Insert our start point into the container
            Vertex startPoint = listVertices[listVerticesIndex(startVertex)];
            startPoint.weight = 0;
            container.insert(startPoint);

            cout << "inserted " << startPoint.vertex << " successfully into the container" << endl;

            // might as well make a while loop but the texbook wants
            // to be special and darn it I do too #indefiniteLoopGang
            for ( ; ; ) {
                Vertex curr_vertex;
                bool gottem = false;

                // while the container is not empty and we haven't gottem yet
                while(!container.isEmpty() && !gottem) {
                    curr_vertex = container.findMin();
                    container.deleteMin();

                    if (!curr_vertex.visited) {
                        gottem = true;
                    }
                }

                if (container.isEmpty())
                    cout << "Empty container..." << endl;

                // we gottem! Shortest path found
                if (!gottem) { break; }

                // we been there, tellem in the list boi
                listVertices[listVerticesIndex(curr_vertex.vertex)].visited = true;

                // Now we need to scan the adjacentList of curr_vertex:
                for ( Vertex adjacent_vertex : curr_vertex.adjacentList ) {

                    // cout << "Looking at: " << adjacent_vertex.vertex << endl;

                    // if the vertex is not visited
                    if (!listVertices[listVerticesIndex(adjacent_vertex.vertex)].visited) {

                        // get the sum of the weights
                        int sumWeight = adjacent_vertex.weight + curr_vertex.weight;

                        // if it is less than the vertex weight, continue
                        if (sumWeight < listVertices[listVerticesIndex(adjacent_vertex.vertex)].weight) {
                            
                            // set new value of weight, add to the binary heap, and set the previous to the current vertex.
                            listVertices[listVerticesIndex(adjacent_vertex.vertex)].weight = sumWeight;
                            container.insert(listVertices[listVerticesIndex(adjacent_vertex.vertex)]);
                            listVertices[adjacent_vertex.vertex].previous_in_path = curr_vertex.vertex;

                        } // end if2
                    } // end if1
                } // end adjacentList scanning
            } // end indefinite for loop

            listVertices[startVertex].weight = 0;
        }

        int getNumVertices() {
            return vertices;
        }

        int getSizeVector() {
            return listVertices.size();
        }

        int listVerticesIndex(int targetVertex){
            // loop through listVertices
            for(int i = 0; i < listVertices.size(); i++){
                if(listVertices[i].vertex == targetVertex){ // return the index if the vertices match
                    return i; 
                }
            }
            return -1;
        }

    private:   

        // Vertex struct
        struct Vertex {
            // data members
            int vertex;
            float weight;
            bool visited = false;

            list<Vertex> adjacentList;

            // constructors
            Vertex() : vertex{0} , weight{0.0} { }
            Vertex(int v, float w) : vertex{v} , weight{w} { }

            int previous_in_path;
            vector<Vertex> shortest_path;

            // overload operator < for comparison in our binary heap
            bool operator<(Vertex &v) const { return (weight < v.weight); }
        };

        // list of vertices in the graph
        vector<Vertex> listVertices;
        //number of vertices in the graph
        int vertices;
};

#endif