
﻿
// CSCI 335 Homework #6
// Your name: Sadab Hafiz
// Graph class which uses adjacency list to create directed graphs.
// Implements dijkstra's shortest path algorithm according to lecture slides 20.  

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>

// Start of Graph class
class Graph{
    public:
        
        // Create a directed graph based on information from a file named @filename
        void ReadGraph(string filename){
            // Make graph empty before reading data from file
            MakeEmpty();
            // Read file named filename
            ifstream graphfile(filename);
            
            // Get the first line from graphfile and set number_of_vertices based on the int in first line
            string each_line, first_line;
            getline(graphfile,first_line);
            number_of_vertices=stoi(first_line);

            // While reading each line from the graphfile, make and store vertices in private data member @graph_data 
            while(getline(graphfile,each_line)){
                // Create Point @a_point to hold information about a vertex 
                stringstream read_line(each_line);
                float number;
                Point a_point;
                // Get the @vertex for @a_point from input
                read_line>>a_point.vertex;
                // Get the adjacency vertex information, and store them in @connected_points_list 
                while(read_line>>number){
                    // Create a Point for each adjacent vertex
                    Point connected_point;
                    // Get the vertex number and weight from input. Set @prev_vertex of each adjacent vertex to -1 
                    connected_point.vertex=number;
                    read_line>>connected_point.weight;
                    connected_point.prev_vertex=-1;

                    // Store adjacent vertices in @connected_points_list of each vertex
                    a_point.connected_points_list.push_back(connected_point);
                }
                // Store vertex in graph_date
                graph_data.push_back(a_point);
            }
        }

        // Sets @number_of_vertices to 0 and makes @graph_data empty
        void MakeEmpty(){
            number_of_vertices=0;
            graph_data.clear();
        }

        // Takes two vertices and prints weight if @vertex1 is connected to @vertex2
        // If the vertices are not connected, prints "not_connected"
        void CheckConnection(int vertex1, int vertex2){
            // Return if @query_vertex is not in graph_data
            if(listVerticesIndex(vertex1)==-1){
                return;
            }

            // Store vertices adjacent to @vertex1 in @connected_points
            vector <Point> connected_points=graph_data[listVerticesIndex(vertex1)].connected_points_list;
            
            // If there are no adjacent vertices, print "not_connected"
            if(connected_points.empty() or listVerticesIndex(vertex2)==-1){
                cout<<vertex1<<" "<<vertex2<<": not_connected "<<endl;
                return;
            }

            // Iterate through the adjacent vertices 
            for(size_t j=0;j<connected_points.size();j++){
                // If @vertex2 is located in @connected_points, print "connected" and the weight of the edge
                if(connected_points[j].vertex==vertex2){
                    cout<<vertex1<<" "<<vertex2<<": connected "<<connected_points[j].weight<<endl;
                    // Return if @vertex2 is adjacent to @vertex1
                    return;
                }            
            }
            // If @vertex2 is not adjacent to vertex1, print "not_connected"
            cout<<vertex1<<" "<<vertex2<<": not_connected "<<endl;
        }
        
        // Runs DikstraShortestPath() algorithm on this graph 
        // Prints the path from @query_vertex to each vertex and also prints the cost
        // Prints not_possible if @query_vertex can't reach a vertex
        void PrintPathCost(int query_vertex){
            // Return if @query_vertex is not in graph_data
            if(listVerticesIndex(query_vertex)==-1){
                return;
            }
            // Run DijkstraShortestPath()  using @query_vertex as starting vertex
            DijkstraShortestPath(query_vertex);
            
            // Iterate through all vertices
             
            for(int i=0;i<number_of_vertices;i++){
                // @curr_vertex points to graph_data[i]
                Point *curr_vertex=&graph_data[i];
                cout<<graph_data[i].vertex<<": ";
                
                // If the smallest cost, stored in @weight, is infinity(9999999), reaching that point is not possible
                if(curr_vertex->weight==9999999){
                    cout<<"not_possible"<<endl;
                    continue;
                }
                
                // Store the full path of @curr_vertex in it's @path vector by tracking the parent vertices
                // while @curr_vertex has a parent, add the parent to path of graph_date[i] and set curr_vertex to point to its @prev_vertex
                while(curr_vertex->prev_vertex!=-1){
                    graph_data[i].path.push_back(graph_data[listVerticesIndex(curr_vertex->prev_vertex)]);
                    curr_vertex=&graph_data[listVerticesIndex(curr_vertex->prev_vertex)];
                }

                // Print the path of graph_data[i]
                for(int j=graph_data[i].path.size()-1;j>=0;j--){
                    cout<<graph_data[i].path[j].vertex<<" ";
                }
                cout<<graph_data[i].vertex<< " ";

                // Call setprecision(1) to print one decimal place and print the cost, which is @weight, of graph_data[i] 
                cout<<std::fixed;
                cout<<"cost: "<<std::setprecision(1)<<graph_data[i].weight<<" "<<endl;
            }
        }

    private:
        // Struct Point holds information about each vertex
        struct Point{
            int vertex; 
            // vector with adjacent points
            vector<Point> connected_points_list; 
            // weight represents cost of shortest path for individual vertices and it represents edge weight for adjacent Points
            // Cost of shortest path is assigned after running DijkstraShortestPath()
            float weight;  
            // Used to keep track of whether shortest path to the Point exists
            bool known; 
            // Holds the shortest path after running DijkstraShortestPath() and PrintPathCost()
            vector<Point> path; 
            // Holds parent vertex
            int prev_vertex;    
            // < operator overloaded to work with BinaryHeap class
            // Returns true if this.weight is smaller than @a_point.weight. Otherwise returns false
            bool operator<(Point &a_point) const{
                return weight < a_point.weight;
            }
        };
        // Data member to hold number of vertices
        int number_of_vertices;
        // Data member to hold all Points in graph
        vector<Point> graph_data;
        
        // Finds the index of @vertex in @graph_data. Returns -1 if vertex is not in @graph_data
        int listVerticesIndex(int vertex){
            // Iterate through graph_data
            for(int i=0;i<graph_data.size();i++){
                // If @vertex is found return the index @i of @vertex in graph_data
                if(graph_data[i].vertex==vertex){
                    return i;
                }
            }
            // Return -1
            return -1;
        }

        // Dijkstra's shortest path algorithm starting from @query_vertex
        void DijkstraShortestPath(int query_vertex){
            // Create a priority que of vertices using BinaryHeap class
            BinaryHeap<Point> prique;
            
            // Set @weight of all vertices to infinity(9999999)
            // Set @known of all vertices to false
            // Set @prev_index (parent) of all vertices to -1
            for(size_t t=0;t<number_of_vertices;t++){
                graph_data[t].weight=9999999;
                graph_data[t].known=false;
                graph_data[t].prev_vertex=-1;
            }

            // Insert the query_vertex in @prique after setting it's weight to 0
            Point query_point=graph_data[listVerticesIndex(query_vertex)];
            query_point.weight=0.0;
            prique.insert(query_point);
            
            // Indefinite loop
            for( ; ; ){
                
                // If priority que is not empty and there is atleast one unknown path, set Point @v to smallest Point in @prique
                Point v;
                bool success=false;
                while(!prique.isEmpty() && !success){
                    v=prique.findMin();
                    prique.deleteMin();
                    if(!v.known){
                        success=true;
                    }
                }
                // Break out of indefinite loop if shortest path for all vertices has been found
                if(!success){
                    break;
                }

                // Set known to true for the corresponding vertex to v in graph_data
                graph_data[listVerticesIndex(v.vertex)].known=true;
                
                // Iterate through the adjacent vertices of v
                for(int i=0;i<v.connected_points_list.size();i++){
                    // Set w to an adjacent vertex of v
                    Point w=v.connected_points_list[i];
                    // If shortest path of w is unknown 
                    if(!graph_data[listVerticesIndex(w.vertex)].known){
                        // If (v.weight+w.weight) is less than the current shortest path weight of corresponding vertex of w in graph_data
                        if(v.weight+w.weight<graph_data[listVerticesIndex(w.vertex)].weight){
                            // Set the weight of corresponding vertex of w in graph_data equal to (v.weight+w.weight)
                            graph_data[listVerticesIndex(w.vertex)].weight=v.weight+w.weight;
                            // Insert the corresponding vertex of w in graph_data into priority que
                            prique.insert(graph_data[listVerticesIndex(w.vertex)]);
                            // Set v.vertex as the parent(@prev_node) of corresponding vertex of w in graph_data 
                            graph_data[listVerticesIndex(w.vertex)].prev_vertex=v.vertex;
                        }
                    }
                }
            }
            // Set the weight of query_vertex in graph_data to 0
            graph_data[listVerticesIndex(query_vertex)].weight=0;
        }
}; 
// End of Graph class
#endif