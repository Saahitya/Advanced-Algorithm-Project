#ifndef PROJECT
#define PROJECT

#include <iostream>
#include <vector>
#include <map>
#include <limits.h>

using namespace std;

struct vertex
{
	int no_of_edges;
	map<int, int> edges;
};

double time_elapsed(struct timespec *start, struct timespec *end);

//Graph Functions
/* Reads a graph as a matrix*/
auto read_graph();
/*Displays a matrix*/
void display(vector<vector<int>> Matrix);
/*Converts a matrix to adjacency list */
auto read_adj_list_from_matrix(vector<vector<int>> graph);
/*Initialise parent matrix */
vector<vector<int>> init_parent(vector<vector<int>> Graph);
/*Initialise the parent vertices from adjacency list*/
vector<vector<int>> init_parent_v(vector<vertex> vertices);
/*Makes routing table from parent matrix*/
vector<vector<int>> create_next_hop(vector<vector<int>> parent);
/*Finds path from source to destination and returns total distance*/
int path_finder(vector<vector<int>> NH, vector<vector<int>> Dist, int src, int dst);

//Routing Algorithms

//Bellman-Ford Algorithm
/*Wrapper to call Bellman Ford's algorithm for every node*/
void Bellman_Ford_wrapper(vector<vertex> vertices, vector<vector<int>> &Distance_Matrix, vector<vector<int>> &Next_Hop);
/*Bellman Ford Algorithm for single source shortest path*/
vector<int> Bellman_Ford(vector< vertex> vertices, vector<vector<int>> &parent_mat, int src);

//Dijkstra Algorithm
/*Wrapper to call Dijkstra's algorithm for every node*/
void Dijkstra_wrapper(vector< vertex > vertices, vector<vector<int>> &Distance_Matrix, vector<vector<int>> &Next_Hop);
/*Dijkstra Algorithm for single source shortest path*/
vector< int> Dijkstras(vector< vertex > vertices,  int src, vector< vector< int>>&parents);

//Floyd-Warshall Algorithm
/*Converts no edge weight 0 to -1*/
vector< vector< int>> fix_matrix(vector< vector< int>> graph);
/*Floyd's all pairs shortest path algorithm*/
void Floyd_Warshall(vector<vector<int>> Graph, vector<vector<int>> &Distance_Matrix, vector<vector<int>> &Next_Hop);
#endif