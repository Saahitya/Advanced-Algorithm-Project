#include "centralrouting.h"

double time_elapsed(struct timespec *start, struct timespec *end) 
{
	double t;
	t = (end->tv_sec - start->tv_sec); // diff in seconds
	t += (end->tv_nsec - start->tv_nsec) * 0.000000001; //diff in nanoseconds
	return t;
}

auto read_graph() 
{
    int N;
    int i, j, temp;
    cin >> N;
    vector< vector< int> > graph(N, vector< int >(N, -1));
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++){
            cin >> temp;
            if(temp != -1)  graph[i][j] = temp;
        }
    }
	return graph;
}

void display(vector<vector<int>> Matrix)
{
	int i, j;
	int n = Matrix.size();
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
		  cout << Matrix[i][j] << " ";
		}

		cout << endl;
	}
	cout << endl;
}

auto read_adj_list_from_matrix(vector<vector<int>> graph) 
{
	int N;
	int i, j;
	N = graph.size();
	int dest, cost;
	vector< vertex > vertices(N);
	vertex *vert;
	for(i = 0; i < N; i++) 
	{
		vert = new vertex();
		vert->no_of_edges = 0;
		for(j = 0; j < N; j++)
		{
			cost = graph[i][j];
			if(cost!=0)
			{
				vert->edges[j] = cost;
				vert->no_of_edges++;
			}
		}
		vertices[i] = *vert;
	}
	return vertices;
}

vector<vector<int>> init_parent(vector<vector<int>> Graph)
{
	int i, j;
	int n = Graph.size();
	vector<vector<int>> parent(n,vector<int> (n));
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(Graph[i][j]!=(INT_MAX/2-1) && Graph[i][j] != 0)
				parent[i][j] = i;

			else
				parent[i][j] = -1;
		}
	}
	return parent;
}

vector<vector<int>> init_parent_v(vector<vertex> vertices)
{
  int i, j;
  int n= vertices.size();
  vector<vector<int>>parent;
  
  for(i=0;i<n;i++){
  	vector<int> a(n, -1);
  	parent.push_back(a);
  }
  for(i=0; i<n; i++)
  {
    for(auto e : vertices[i].edges)
    {
      parent[i][e.first] = i;
    }
  }
  return parent;
}

vector<vector<int>> create_next_hop(vector<vector<int>> parent)
{
	int i, j;
	int n = parent.size();

	vector<vector<int>>next_hop(n,vector<int> (n));

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
	  		next_hop[i][j] = parent[j][i];
	}
	return next_hop;
}

int path_finder(vector<vector<int>> NH, vector<vector<int>> Dist, int src, int dst)
{
	int d = 0;
	while(src != dst || NH[src][dst]!=-1)
	{
		cout << src << "-> ";
		src = NH[src][dst];
		d += Dist[src][dst];
	}
	cout << dst;
	return d;
}

int main() 
{
	struct timespec start;
	struct timespec end;
	vector< vector< int>> graph = read_graph();
    vector<vertex> vertices =  read_adj_list_from_matrix(graph);
    vector< vector< int>> B_distance_matrix, B_next_hop;
    vector< vector< int>> D_distance_matrix, D_next_hop;
    vector< vector< int>> F_distance_matrix, F_next_hop;

	clock_gettime(CLOCK_REALTIME, &start); //start timestamp
    Bellman_Ford_wrapper(vertices, B_distance_matrix, B_next_hop);
   	clock_gettime(CLOCK_REALTIME, &end); //end timestamp
	printf("Bellman Ford: %lf sec\n", time_elapsed(&start, &end)); 

	clock_gettime(CLOCK_REALTIME, &start); //start timestamp	   
    Dijkstra_wrapper(vertices, D_distance_matrix, D_next_hop);  
	clock_gettime(CLOCK_REALTIME, &end); //end timestamp
	printf("Dijkstra: %lf sec\n", time_elapsed(&start, &end)); 

	clock_gettime(CLOCK_REALTIME, &start); //start timestamp	   
    Floyd_Warshall(graph, F_distance_matrix, F_next_hop);
	clock_gettime(CLOCK_REALTIME, &end); //end timestamp
	printf("Floyd-Warshall: %lf sec\n", time_elapsed(&start, &end)); 
    
    //display(B_distance_matrix);
    //display(D_distance_matrix);
    //display(F_distance_matrix);
    //display(B_next_hop);
    //display(D_next_hop);
    //display(F_next_hop);    
    return 0;
}