struct Vertex  {
        // element of the vertex, the identifier
        Object element;

        // vector containing all adjacent vertices
        vector<Vertex> adjacentVertices; 

        // vector containing the weights of each adjacent vertex. 
        // position-sensitive, i.e. the ith member of adjacentVertices
        // has a weight found in the ith member of weights.
        vector<float> weights; 

        // constructors:
        Vertex( const Object & ele, const vector<Vertex> & adj, const vector<Vertex> & wei ) 
            : element{ele}, adjacentVertices{adj}, weights{wei} { }
        Vertex( const Object && ele, const vector<Vertex> && adj, const vector<Vertex> && wei )
            : element{ std::move(ele) }, adjacentVertices{ std::move(adj) }, weights{ std::move(wei) } { } 
    }




// old implementation:

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <list>

using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

class Graph {
    public:
        /** Constructor
         * @param vertices the number of vertices in the graph */
        Graph(int vertices) {
            this->vertices = vertices;
            adjacentList = new list< Vertex >[vertices+1];
        }

        void addEdge(int x, int y, float wei) {
            // for undirected graphs
            // pair<int, float> firstPair(x, wei);
            // pair<int, float> secondPair(y, wei);

            Vertex new_vertex(y, wei);
            adjacentList[x].push_back(new_vertex);

            // for undirected graphs
            // adjacentList[y].push_back(firstPair);
        }

        void printGraph() {
            // Iterate through each vertex
            cout << "Number of Vertices: " << vertices << endl << endl;

            cout << "Vertex #  |    adjacentNode, weight   |" << endl;
            for (int i = 1; i <= vertices; i++) {
                cout << "Vertex: " << i << " | ";
                for (Vertex current_vertex : adjacentList[i]) {
                    cout << current_vertex.vertex << ", " << current_vertex.weight << " | ";
                }
                cout << endl;
            }
        }

        float areAdjacent(int a, int b) {
            int test = adjacentList[a].size();

            for (Vertex current_vertex : adjacentList[a]) 
                if (current_vertex.vertex == b)
                    return current_vertex.weight;

            return -1.0;
        }

        void findPaths(int startVertex) {

            int beegNoomber = 10000;

            // setup
            for (int i = 0; i < vertices; i++) {
                adjacentList[i].distance = 0;
            }


            adjacentList[startVertex].distance = 0;

//             while (true) {
//             Vertex v = smallest unknown distance vertex; // How?
//             if (v == NOT_A_VERTEX) break;
//             v.known_ = true;
//             for each Vertex w adjacent to v {
//             if (!w.known_) {
//             const auto new_distance_through_v = v.distance_ + c(v,w);
//             if (new_distance_through_v < w.distance_) {
//             w.distance_ = new_distance_through_v; // Decrease w.distance_
//             w.previous_in_path_ = v;
//             }
//             }
//             } // end of for each Vertex w…
// } // end of while (true)

        }

        int getNumVertices() {
            return vertices;
        }

        /** Bool Operator
         * @param rhs the rvalue of the < operator
         * @brief operates based on regular string comparison between the 
         * lvalue and rvalue recognition_sequence_ strings. */
        // bool operator<(const int vertex) {
        //     return (this.)
        // }

    private:   

        struct Vertex {
            int vertex;
            float weight;
            bool visited = false;

            Vertex(const int v, const float w) 
            : vertex{v} , weight{w} { }

        };

        list< Vertex > *adjacentList;

        int vertices;
};

#endif