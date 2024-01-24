#include<bits/stdc++.h> 
using namespace std; 
# define INF 0x3f3f3f3f 
# define PRINT false

// g++ ring.cpp -o ring
// ./ring

class Graph 
{ 
    int N;    // Number of vertices  
    list<int> *adj; // Agjacency list
    void DFShelp(int v, bool visited[], int &last, int length, int &maxlength); // recursive function for DFS
public: 
    Graph(int N);  // Constructor 
    void addEdge(int u, int v); // Function to add an edge to graph 
    void Metrics(int &D, int &H); // Function to calculate Height (H) and Diameter(D) of a tree graph 
    void DFS(int v, int &last, int &maxlength);  //DFS starting from v to find last visited vertex and maximum length
    void Delete();
}; 

  
Graph::Graph(int N) 
{ 
    // Memory allocation
    this->N = N; 
    adj = new list<int>[N]; 
    if (PRINT) cout << "Tree with " << N << " nodes\n";
} 
void Graph::addEdge(int u, int v) 
{ 
    if ( u >= N || v >= N )
    {
        if (PRINT) cout << "I cannot add edge (" << u << "," << v << ")\n";
        return;
    }

    adj[u].push_back(v); 
    adj[v].push_back(u); 
    if (PRINT) cout << "Edge (" << u << "," << v << ") added\n";
}


void Graph::DFShelp(int v, bool visited[], int &last, int length, int &maxlength) 
{ 
    // Mark the current node as visited  
    visited[v] = true; 

    // Update maximum length and last node
    if ( length > maxlength ) 
        {
            maxlength = length;
            last = v;
        }
  
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            DFShelp(*i, visited, last, length+1, maxlength); 
} 
  
void Graph::DFS(int v, int &last, int &maxlength) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[N]; 
    for (int i = 0; i < N; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function 
    DFShelp(v, visited, last, 0, maxlength); 
} 


void Graph::Metrics(int &D, int &H)
{
    // Initialization
    H = 0;
    D = 0;
    if (N==1) return;
    // DFS starting from root = 0 to find: 1. Height 2.one edge of diameter 
    int last = 0;
    DFS(0, last, H);
    if (PRINT) cout << "Height starting from : "<< 0 << " is " << H << "\n";

    // DFS starting from last to find diameter
    int u = last;
    DFS(last, u, D);
    if (PRINT) cout << "Diameter: starting from : "<< last << " is " << D << "\n";
}


void LongestPath( vector<int> &D, vector<int> &H, int K)
{
    // Max Diameter
    int Dmax = *max_element(D.begin(), D.end());

    // Max Interplanet Length greedy
    int Lmax = -1;
    int M = H[0] + K - 1;
    for (int i = 1; i < K; i++)
    {
        Lmax = max(Lmax, M + H[i]);
        M = max(M - 1, H[i] + K - 1);
    }

    //making the second parse for the heightval
    M = H[0] + 1;
    for (int i = 1; i < K; i++) 
    {
        Lmax = max(Lmax, M + H[i]);
        M = max(M + 1, H[i] + 1);
    }

/*
    // Max Interplanet Length brute force

    int Lmax = 0;
    int M = 0;

    for ( int i = 0; i < K; i++)
    {
        for( int j=0; j < K; j++ )
        {
            if (i==j) continue;
            M = max( Lmax, max( abs(i-j), K-abs(i-j) ) + H[i] + H[j] );
            if (M > Lmax) Lmax = M;
        }
    }
*/

    if (PRINT) cout << "Longest Path : " ;
    cout << max(Lmax, Dmax) << "\n";
}

  
int main() 
{ 
    // Read input
    int K; // Number of planets
    cin >> K; 

    vector<int> D(K); // Diameters of trees
    vector<int> H(K); // Heights of trees
    
    int Ni; // Number of towns in planet i
    int j;

    // Create and find Height and Diameter for the K trees.
    for (int i = 0; i < K; i++)
    {
        cin >> Ni;
        Graph g(Ni); // planet i's Tree

        if (Ni == 1) cin >> Ni;
        else
        {
            for (int l = 1; l < Ni; l++)
            {
                cin >> j;
                g.addEdge(l,j-1);
            }
        }
        g.Metrics(D[i], H[i]);
    }   

    if (PRINT) cout << "All Heights: "; 
    for (int i = 0; i < K; i++ ) if (PRINT) cout << H[i] << " "; if (PRINT) cout  << "\n";
    if (PRINT) cout << "All Diameters: "; 
    for (int i = 0; i < K; i++ ) if (PRINT) cout << D[i] << " "; if (PRINT) cout  << "\n";

    // Find Longest Path
    LongestPath(D, H, K);

    return 0; 
} 
