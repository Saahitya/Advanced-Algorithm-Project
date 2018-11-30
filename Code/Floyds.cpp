#include"centralrouting.h"

void Floyd_Warshall(vector<vector<int>> Graph, vector<vector<int>> &Distance_Matrix, vector<vector<int>> &Next_Hop)
{
	int i, j, k, n = Graph.size();
	Graph = fix_matrix(Graph);
	vector<vector<int>> parent = init_parent(Graph);
	for(k=0; k<n; k++)
	{
		for(i=0; i<n; i++)
		{
			for(j=0; j<n; j++)
			{
				if(Graph[i][j] > (Graph[i][k] + Graph[k][j]))
				{
					Graph[i][j] = Graph[i][k] + Graph[k][j];
					parent[i][j] = parent[k][j];
				}
			}
		}
	}
	vector<vector<int>>  next_hop = create_next_hop(parent);
	Distance_Matrix = Graph;
	Next_Hop = next_hop;
}



vector< vector< int>> fix_matrix(vector< vector< int>> graph)
{	
	for(int i=0; i<graph.size(); i++)
	{
		for(int j=0; j<graph.size(); j++)
		{
			if(i!=j && graph[i][j] == 0)
				graph[i][j] = INT_MAX/2-1;
		}
	}
	return graph;
}
