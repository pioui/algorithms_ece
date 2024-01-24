#include<bits/stdc++.h> 
using namespace std; 

class Graph 
{ 
    int N;    // Number of vertices 
    list<int> *adj; 
    vector< pair<int, pair<int, int>> > edges; 
    void DFS(int v, bool visited[]); 

public: 
    // Constructor 
    Graph(int N);   
  
    // Αdd an edge (u,v) with weight w to graph 
    void addEdge(int u, int v, int w); 
  
    // Returns true if graph is connected 
    bool isConnected(int &a); 
  
    void reverseDeleteMST(int bin[]); 

    void print();

}; 
  

Graph::Graph(int N) 
{ 
    this->N = N; 
    adj = new list<int>[N]; 
} 

void Graph::print()
{
    for (int i=0;i<N;i++)
    {
        list<int> a = adj[i];
        cout << i << ' ';
        for (auto it = a.begin(); it != a.end(); ++it) 
            cout << *it  ;
        cout << "\n";
    }
    return;
}
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[u].push_back(v); 
    adj[v].push_back(u);  
    edges.push_back({w, {u, v}}); 
} 
  
void Graph::DFS(int v, bool visited[]) 
{ 
    // Mark the current node as visited 
    visited[v] = true; 
  
    // Recur for all the vertices adjacent to 
    // this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            DFS(*i, visited); 
} 
  
// Returns true if given graph is connected, else false 
// a is the number of non reachable vertices 
bool Graph::isConnected(int &a) 
{ 
    bool visited[N]; 
    memset(visited, false, sizeof(visited)); 
  
    // Find all reachable vertices from first vertex 
    DFS(0, visited); 
  
    bool flag=true;
    for (int i=1; i<N; i++) 
        if (visited[i] == false)  
            {
                flag = false; 
                a++;
            }

  
    return flag; 
} 
  

void Graph::reverseDeleteMST(int bin[]) 
{ 
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end()); 
    
    //cout << "Edges in MST\n"; 
  
    // Iterate through all edges
    for (int i=edges.size()-1; i>=0; i--) 
    { 
        int u = edges[i].second.first; 
        int v = edges[i].second.second; 
        
        // Remove edge from undirected graph 
        // check for double edges if the length decreases more than 1
        int lu = adj[u].size();

        adj[u].remove(v); 
        adj[v].remove(u); 

        int lu_ = adj[u].size();

        // If betweeen two vertices are more than 1 edges then is certainly connected.
        if (lu_ != lu-1)
        {
            for (int l=0; l<lu-lu_-1; l++)
            {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        else
        {
            int a=0;
            bool con = isConnected(a);

            // Adding the edge back if removing it 
            // causes disconnection. In this case this  
            // edge becomes part of MST. 
            if (con == false) 
            { 
                adj[u].push_back(v); 
                adj[v].push_back(u); 
  
                // This edge is part of MST 
                //cout << "(" << u << ", " << v << ") \n"; 
                //cout << edges[i].first << "\n";
                //cout << a << "x" << N-a << "\n\n";

                bin[edges[i].first]=a*(N-a);
            } 
        }
    } 
  
} 

void printBinary(int bin[],int M)
{
    stack<int> output;
    for (int i = 0; i<M-1 ; i++)
    {
        bin[i+1] += bin[i] / 2;
        output.push(bin[i] % 2);
    }

    int b=bin[M-1];
    while( b != 0)
    {
        output.push(b % 2);
        b=b/2;  
    }


    while (!output.empty()) 
    { 
        cout << output.top(); 
        output.pop(); 
    } 

    cout << "\n";

    return;
}
  
int main() 
{ 
    // Number of vertices
    int N;
    cin >> N; 

    // Number of edges
    int M;
    cin >> M; 

    //Create Graph
    Graph g(N); 
  
    int a,b,c;
    for (int i=0; i<M; i++)
    {
        cin >> a;
        cin >> b;
        cin >> c;
        g.addEdge(a-1,b-1,c); 
    }

    // bin[i] is the number of times edges with weight 2^i is in shortest path.
    int bin[M];
    // Initilize bin with zero.
    for (int i=0; i<M; i++)
    {
        bin[i] =0;
    }
    //g.print();
    // Use reverse Kruskal algorithm to calculate MST
    g.reverseDeleteMST(bin);
    //g.print();
    
    //Decimal Result
    /*
    int sum=0;
    int n=1;
    for (int i=0; i<M; i++) 
    {
        cout << bin[i] << "\n";
        sum+=bin[i]*n;
        n=n*2;
    }
    cout << "Decimal sum is :" << sum << "\n";
    */

    // Print binary result
    printBinary(bin,M);

    return 0; 
} 
