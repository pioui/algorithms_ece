// Dijkstra
// Code from edited from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/


#include<bits/stdc++.h> 
using namespace std; 
# define INF 0x3f3f3f3f 

  

class Graph 
{ 
    int N;    // Number of vertices  

    list< pair<int, int> > *adj; 

  
public: 
    Graph(int N);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int u, int v, int w); 
  
    // prints shortest path from C points
    void MultiDijkstra(vector<int> &C, vector<int> &D); 

    // finds the time of the race T
	void RacingTime ( vector<int> &T, int K, int L, vector<int> &C);

}; 
  
// Allocates memory for adjacency list 
Graph::Graph(int N) 
{ 
    this->N = N; 
    adj = new list< pair<int, int> >[N]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[u].push_back(make_pair(v, w)); 
    adj[v].push_back(make_pair(u, w)); 
} 
  
// Prints shortest paths from C to all other vertices 
void Graph::MultiDijkstra(vector<int> &C, vector<int> &D) 
{ 
 
    set< pair<int, int> > setds;

    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(N, INF); 

  
    // Insert all source vertices in Set and initialize its 
    // distance as 0. 
    for( auto c : C)
    {
    	setds.insert(make_pair(0, c)); 
    	dist[c] = 0;
    }

  
    /* Looping till all shortest distance are finalized 
       then setds will become empty */
    while (!setds.empty()) 
    { 
   
        pair<int, int> tmp = *(setds.begin()); 
        setds.erase(setds.begin()); 
        int u = tmp.second; 
          list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second; 
              if (dist[v] > dist[u] + weight) 
            { 

                if (dist[v] != INF) 
                    setds.erase(setds.find(make_pair(dist[v], v))); 

                dist[v] = dist[u] + weight; 
                setds.insert(make_pair(dist[v], v)); 
            }
        } 

    } 

    D = dist;
    
}

void Graph::RacingTime ( vector<int> &T, int K, int L, vector<int> &C)
{

	int RacingTime = 0, StopsTime = 0;
	int v ,w;

	// Time with no stops;
	for (int i = 0; i<K-1; i++)
	{
		for (auto j : adj[T[i]])
		{
			v = j.first; 
            w = j.second; 
            if ( v == T[i+1])
            {
            	RacingTime += w;
            	continue;
            }

		}
	}


	//Stops time:

	vector<int> D;
    MultiDijkstra(C,D);

	vector<int> Stops;
	for (int i = 1; i<K-1; i++)
	{
		Stops.push_back(D[T[i]]);
	}

	nth_element(Stops.begin(), Stops.begin() + L-1, Stops.end()); 

	for (int i = 0; i < L; ++i) 
	{ 
		StopsTime += Stops[i]; 
	} 
	cout << RacingTime+StopsTime << "\n"; 
}

  
int main() 
{ 

	// Read input
    int N, M, K, L, B; //number of towns in Tatoine
    cin >> N; //number of towns in Tatoine
  	cin >> M; //number of roads in Tatoine
    cin >> K; //number of racing roads in Tatoine
    cin >> L; //number of anefodiasmon in Tatoine
    cin >> B; //number of fuel stations in Tatoine

    Graph g(N); 

    int u, v, w; // Vertices given from 1 to N but we tranform it to 0 to N-1!
    for (int i = 0; i < M; i++)
    {
        cin >> u;
        cin >> v;
        cin >> w;
        g.addEdge(u-1, v-1, w); 
    }

    
    vector<int> T;
    for (int i = 0; i < K; i++)
    {
    	cin >> u;
    	T.push_back(u-1);
    }

    vector<int> C;
    for (int i = 0; i < B; i++)
    {
    	cin >> u;
    	C.push_back(u-1);
    }    
    
    g.RacingTime(T, K, L, C);

  
    return 0; 
} 
