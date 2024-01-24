
#include <bits/stdc++.h> 
using namespace std; 
  

//Print Vector
void print(std::vector<int>  &input)
{
    for (auto const& i: input) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return ; 

}

void lightparent(std::vector<int> cur,std::vector<bool> &Lighted, std::vector<int> adj[], int &number)
{
    int min = *min_element(cur.begin(), cur.end());
    if(!Lighted[min])
    {
        number++;
        Lighted[min]=true;
    }
    return;
}

int NumberOfLights(std::vector<int>  adj[],int N)
{

    //If i-th crossroad is lighted
    std::vector<bool> Lighted(N+1,false); 

    int number=0;
    
    for(int i=N;i>0;i--)
    {
        //If it is not lighted put a light in its parent 
        if (!Lighted[i])
        {
            lightparent(adj[i], Lighted, adj,number);
        }
    }

    return number;
}
  
int main() 
{ 
    // Read input
    int N; //number of crossroads
    std::cin >> N;

    int K;
    std::cin >> K; //number of lighted roads
  
    // Adjacency list 
    std::vector<int> adj[N+1]; 
    int u,v;
    for(int i=1;i<N;i++)
    {
        std::cin >> u ;
        std::cin >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //Number of lights
    int num=NumberOfLights(adj,N);
    std::cout<< num <<"\n"; 
  
    return 0; 
} 
