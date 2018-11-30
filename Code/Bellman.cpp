#include "centralrouting.h"

vector<int> Bellman_Ford(vector< vertex> vertices, vector<vector<int>> &parent_mat, int src) 
{
      vector<int> distances(vertices.size());
      vector<int> shortest_hop(vertices.size());
      vector<int> parent(vertices.size());
      for (int i = 0; i < vertices.size(); i++)  
      {
          distances[i] = INT_MAX;
          parent[i] = -1;
      }
      distances[src] = 0;
      int check_flag;
      for (int i = 1; i < vertices.size(); i++) 
      {
            check_flag = 0;
            for(int j = 0; j <  vertices.size(); j++) 
            {
                for(auto elem : vertices[j].edges) 
                {
                    int u = j; 
                    int v = elem.first; 
                    int weight = elem.second; 
                    if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) 
                    {
                        distances[v] = distances[u] + weight;
                        shortest_hop[u] = j;
                        parent[v] = u;
                        check_flag = 1;
                    }
                }
            }
            if(check_flag == 0)
                break;
      }
      parent_mat.push_back(parent);
      return distances;
}

void Bellman_Ford_wrapper(vector<vertex> vertices, vector<vector<int>> &Distance_Matrix, vector<vector<int>> &Next_Hop)
{
    vector<vector<int>> Dist_Mat;
    vector<vector<int>> Parent;
    for(int i = 0; i<vertices.size(); i++)
    {
        Dist_Mat.push_back(Bellman_Ford(vertices, Parent, i));
    }
    vector<vector<int>>  next_hop= create_next_hop( Parent);
    Distance_Matrix = Dist_Mat;
    Next_Hop = next_hop;  
}
