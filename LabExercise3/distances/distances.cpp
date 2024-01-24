#include<bits/stdc++.h>   
using namespace std;   
  
//Disjoint Sets   
struct DisjointSets   
{   
    int *parent, *rnk;   
    int n;   
    
    // Constructor.   
    DisjointSets(int n)   
    {   
        // Allocate memory   
        this->n = n;   
        parent = new int[n+1];   
        rnk = new int[n+1];   
    
        for (int i = 0; i <= n; i++)   
        {   
            rnk[i] = 0;   
    
            //every element is parent of itself   
            parent[i] = i;   
        }   
    }   
  
    int find(int u)   
    {   
        if (u != parent[u])   
            parent[u] = find(parent[u]);   
        return parent[u];   
    }   
    
    void merge(int x, int y)   
    {   
        x = find(x), y = find(y);   
  
        if (rnk[x] > rnk[y])   
            parent[y] = x;   
        else   
            parent[x] = y;   
    
        if (rnk[x] == rnk[y])   
            rnk[y]++;   
    }   
};  
  
// Make the output  
void printBinary(unsigned long int bin[],int M)  
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
  
    while (output.top() == 0 )   
    {   
        output.pop();   
    }   
  
    while (!output.empty())   
    {   
    	cout << output.top();   
 		output.pop();   
    }   
  
    cout << "\n";  
  
    return;  
}  
  
    
// Graph Structure  
struct Graph   
{   
    int N, M;   
    vector< pair<int, pair<int, int>> > edges;   
  
    //MST stuff  
    vector< pair<int, pair<int, int>> > MSTedges;   
    list<int> *MSTadj;   
  
    // Constructor   
    Graph(int N, int M)   
    {   
        this->N = N;   
        this->M = M;   
        MSTadj = new list<int>[N];   
  
    }   
    
    // Utility function to add an edge   
    void addEdge(int u, int v, int w)   
    {   
        edges.push_back({w, {u, v}});   
    }   
    
    // Function to find MST using Kruskal's   
  
    void BinaryDistances();   
    void CalculateChildsDFS(int s,vector<unsigned long int> &NumOfChilds);  
};   
    
   
  
void Graph::CalculateChildsDFS(int s, vector<unsigned long int> &NumOfChilds)  
{  
    // DFS implementation in order to find all childs of each subtree  
  
    // Initially mark all verices as not visited   
    vector<bool> visited(N, false);   
  
    // Create a stack for DFS   
    stack<int> stack;   
    
    // Push the current source node  
    stack.push(s);   
    visited[s] = true;   
  
    int p;  
  
    while (!stack.empty())   
    {  
        s = stack.top();  
        bool flag=false; //flag = true means that s has unvisited childern  
  
        for (auto i = MSTadj[s].begin(); i != MSTadj[s].end(); ++i)   
        {  
            if (!visited[*i])   
            {  
                stack.push(*i);  
                visited[*i] = true;   
                flag=true;  
                break;   
            }  
        }  
  
        if (flag == false)  
        {  
            p = stack.top();  
            stack.pop();  
            if (!stack.empty())  
            {  
                s = stack.top();  
                NumOfChilds[s] += NumOfChilds[p];  
            }  
        }  
  
    }  
}  
  
  
    
void Graph::BinaryDistances()   
{   
    //Step 1: Kruskal Implementation in order  to find MST  
    // Sort edges in increasing order on basis of cost   
    sort(edges.begin(), edges.end());   
  
    // Create disjoint sets   
    DisjointSets ds(N);   
  
    // Iterate through all sorted edges   
    vector< pair<int, pair<int, int>> >::iterator it;   
    for (it=edges.begin(); it!=edges.end(); it++)   
    {   
        int u = it->second.first;   
        int v = it->second.second;   
        int w = it->first;  
    
        int set_u = ds.find(u);   
        int set_v = ds.find(v);   
  
        if (set_u != set_v)   
        {   
            // Edge added to MST  
            MSTedges.push_back({w, {u, v}});  
            MSTadj[u].push_back(v);  
            MSTadj[v].push_back(u);  
                          
            ds.merge(set_u, set_v);   
        }   
    }   
    
  
  
    //STEP 2: Calculate childs of all subtrees   
    vector<unsigned long int> NumOfChilds(N,1);   
    CalculateChildsDFS(0, NumOfChilds);  
  
  
    //STEP 3: Count how many times edge with weight 2^i is in a path   
    //and store it to bin[i]  
    unsigned long int bin[M];  
    // Initilize bin with zero.  
    for (int i=0; i<M; i++)  
    {  
        bin[i] =0;  
    }  
    for (it=MSTedges.begin(); it!=MSTedges.end(); it++)   
    {   
        int u = it->second.first;   
        int v = it->second.second;   
        int w = it->first;  
  
        unsigned long int a=NumOfChilds[u];  
        if (NumOfChilds[u]>NumOfChilds[v])  
        {  
            a=NumOfChilds[v];  
        }  
          
        bin[w]=a*(N-a);  
    }  
  
    //STEP 4: Print resulat to binary form   
    printBinary(bin,M);  
  
    return ;  
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
    Graph g(N,M);   
    
    int a,b,c;  
    for (int i=0; i<M; i++)  
    {  
        cin >> a;  
        cin >> b;  
        cin >> c;  
        g.addEdge(a-1,b-1,c);   
    }  
    
    g.BinaryDistances();   
    
      return 0;   
}  