#include "centralrouting.h"

vector< int> Dijkstras(vector< vertex > vertices,  int src, vector< vector< int>>&parents) 
{

    int numNodes=vertices.size();
    vector <int> dist(numNodes);
    dist[src]=0;
    vector <int> q;
    int v,minv,minvIndex;

    for(v=0;v<numNodes;v++)
    {
        if(v!=src)
        {
            dist[v]=INT_MAX;
        }
        q.push_back(v);
    }

    while(!q.empty())
    {
        minv=q[0];
        minvIndex=0;
        for(int i=1; i<q.size(); i++)
        {
            if(dist[q[i]]<dist[minv])
            {
                minv=q[i];
                minvIndex=i;
            }
        }
        q.erase(q.begin()+minvIndex);

        vertex current=vertices[minv];
        for(auto elem : current.edges) 
        {
            int u=elem.first;
            int weight=elem.second;
            int alt = dist[minv]+weight;
            if(alt < dist[u])
            {
                dist[u] = alt;
                parents[src][u]=minv;
            }
        }
    }
    return dist;
}

void Dijkstra_wrapper(vector< vertex > vertices, vector<vector<int>> &Distance_Matrix, vector<vector<int>> &Next_Hop)
{
    int i,n=vertices.size();
    vector< vector< int>> parent = init_parent_v(vertices);
    vector<vector<int>> Dist_Mat;

    for(i=0;i<n;i++)
    {
        Dist_Mat.push_back(Dijkstras(vertices,i,parent));
    }
    vector< vector< int>> next_hop = create_next_hop(parent);
    Distance_Matrix = Dist_Mat;
    Next_Hop = next_hop;
}