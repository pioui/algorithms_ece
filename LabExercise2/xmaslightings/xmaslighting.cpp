//xmaslighting

/*f(v,b,k)   =  the minimum number of lightings that the subtree with root v 
				needs inorder k of its roads to be shiny. 
				b = 'The parent of v is lighted' 




			  |if b=0:  Σ f(vc,0,kc),   sum(kc)=k      for all childs (v is not lighted)
f(v,b,k)= min |if b=0:  Σ 1+f(vc,1,kc), sum(kc)=k-1-Nc for all childs (v is lighted)
              |if b=1:  Σ f(vc,0,kc),   sum(kc)=k      for all childs (v is not lighted)
              |if b=1:  Σ 1+f(vc,1,kc), sum(kc)=k-Nc   for all childs (v is lighted)
			  |if k=0:  0



			  |Σ f(vc,0,kc),   sum(kc)=k      for all childs c (v is not lighted)
f(v,b,k)= min |Σ 1+f(vc,1,kc), sum(kc)=k-b-Nc for all childs c (v is lighted)
			  
			  if k=0:  0
			  if k <= Nc+1-b: 1
			  if k>Nr: +oo


if v is a leaf it doen't worth to light it =(

*/

#include<iostream>
#include <bits/stdc++.h> 
#include<vector>

int INF=200;

//Print Vector
void print(std::vector<int>  &input)
{
    for (auto val: input) 
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
    return ; 

}
//Print Vector of Vectors
void print(std::vector<std::vector<int>> &input)
{
    for (auto row: input) 
    {
        for (auto val : row) 
        {
            std::cout << val << " ";
        }
        std::cout << '\n';
    }
    return;
}

 
//Calculate the number of roads of all the sub-trees
void calculateRoads(std::vector<std::vector<int>> adj, std::vector<int> &numRoads)
{
	numRoads[0]=0;
	std::vector<int> cur;
	for( int i=numRoads.size()-1;i>0;i--)
	{
		cur.clear();
	    cur=adj[i];
		if (i==1)
		{
			numRoads[i]=cur.size();
		}
		else
		{
        	int min = *min_element(cur.begin(), cur.end());
        	numRoads[i]=cur.size()-1;
			for (auto j: cur) 
	    	{
	    		if(j!=min)
	    		{
	    			numRoads[i]+=numRoads[j];
	    		}
    		}
        }
	}
}


//Find all combinations that sums to num
void CombinationsWork(int arr[], int index, int num, int reducedNum,std::vector<std::vector<int>> &comp) 
{ 
    if (reducedNum < 0) 
        return; 
  
    if (reducedNum == 0) 
    { 
        std::vector<int> c;
        for (int i = 0; i < index; i++) 
        {
            c.push_back(arr[i]);
        }
        comp.push_back(c);
        return; 
    } 
  
    int prev = (index == 0)? 1 : arr[index-1]; 
  
    for (int k = prev; k <= num ; k++) 
    { 
        arr[index] = k; 
        CombinationsWork(arr, index + 1, num, reducedNum - k,comp); 
    } 
} 
void Combinations(int n,std::vector<std::vector<int>> &comp) 
{ 
    int arr[n]; 
    CombinationsWork(arr, 0, n, n,comp); 
} 


//Find all permutations
void PermutationsWork(std::vector<int> a, int n, std::vector<std::vector<int>> &per) 
{ 
    std::vector<int> p;
    for (int i = 0; i < n; i++) { 
        p.push_back(a[i]);
    } 
    per.push_back(p);
} 
  
void Permutations(std::vector<int> a, int n,std::vector<std::vector<int>> &per) 
{ 
  
    std::sort(a.begin(), a.end()); 
      do { 
        PermutationsWork(a, n,per); 
    } while (std::next_permutation(a.begin(), a.end())); 
} 


//Find all the ways to share k roads to Nc childs
void Share(std::vector<std::vector<int>> &fullper,int Nc, int k) 
{ 
    //Find all Cobinations that sums to k
    std::vector<std::vector<int>> comp;
    Combinations(k,comp);

    //Fill with zeros until Nc
    //Creates fullcomp that has all combinations that sums to k zero padded until Nc
    std::vector<std::vector<int>> fullcomp; 
    for (auto c: comp)
    {
        if (c.size()<=Nc)
        {
            while(c.size()<Nc)
            {
                c.push_back(0);
            }
            fullcomp.push_back(c);
        }
    }

    //Creates fullper that has all permutations that sums to k zero padded until Nc
    std::vector<std::vector<int>> per;
    for (auto a: fullcomp)
    {
    	per.clear();
        int n = a.size();
        Permutations(a, n,per);
        for (auto p : per)
        {
            fullper.push_back(p);
        }
    }
    return ; 
} 

int MinShare(std::vector<std::vector<int>> share, std::vector<int> adj, std::vector<std::vector<std::vector<int>>> DP,int b, bool root)
{
	
	
	int min=INF;
	int sum;
	int parent = *min_element(adj.begin(),adj.end());
	if(root) parent = 0; 
	for(auto comp: share)
	{
		sum=0;
		for(int i=0; i<comp.size(); i++)
		{
			if (adj[i]==parent) continue;
			sum+=DP[b][adj[i]][comp[i]];
		}
		if(sum<min)
		{
			min=sum;
		}
	}
	return min;
}


//Calculate the number of Lights you need if you want to light k roads
int NumberOfLights(std::vector<std::vector<int>> adj,int N, int k)
{
	std::vector<int> numRoads(N+1,0); //The subtree with root i has numRoads[i] roads.
	calculateRoads(adj,numRoads);
	std::vector<int> a;
    //int DP[2][N+1][k+1] ; //includes 0 for convinience ;)
    std::vector< std::vector<std::vector<int>>> DP(2, std::vector<std::vector<int>>(N+1, std::vector<int>(k+1)));    
    std::vector<std::vector<int>> share;
    int dp0,dp1;

    for ( int i=N; i>1; i-- ) 		//Light the i-th crossroad 
    {
    	a.clear();
    	a = adj[i];
    	for ( int j=0; j<k; j++ )   //Light from 0 to k streets for each subtree 
    	{
    		//0 lighted Streets need no lights
    		if (j==0)
    		{
    			DP[0][i][j]=0;
    			DP[1][i][j]=0;
    		}
    		//One subtree cannot have more lighted streets that the total streets it has(+1 for its father)
    		else if (j > numRoads[i]+1)
    		{
    			DP[0][i][j]=INF;
    			DP[1][i][j]=INF;
    		}
    		//Share the number of lighted streets to childs 
    		else
    		{
    			share.clear();

    			//b=0 unlighted parent
    			Share(share,a.size()-1,j); 				//don't light j crossroad
    			dp0 = MinShare(share,a,DP,0,false);

    			share.clear();

    			Share(share,a.size()-1,j-a.size()-1);   //light j crossroad
    			dp1 = MinShare(share,a,DP,1,false);

    			DP[0][i][j]=std::min(dp0,dp1);  //choose the best

    			//b=1 lighted parent
    			//don't light j crossroad : dp0
    			share.clear();
    			Share(share,a.size()-1,j-a.size());     //light j crossroad
    			dp1 = MinShare(share,a,DP,1,false);

    			DP[1][i][j]=std::min(dp0,dp1);   //choose the best
    		}
    	}
    }
    // Root
	for(int j=0; j<k; j++)
	{
		//b=0 unlighted parent

		share.clear();
    	Share(share,adj[1].size(),j); 				//don't light j crossroad
    	dp0 = MinShare(share,a,DP,0,true);
		share.clear();

		Share(share,a.size()-1,j-a.size());       //light j crossroad
		dp1 = MinShare(share,a,DP,1,true);

		DP[0][1][j]=std::min_element(dp0,dp1);      //choose the best

		//b=1 lighted parent
		//root hasn't a parent
		DP[1][1][j]=INF;
	}

	return DP[0][1][k];
}


int main()
{
	// Read input
    int N; //number of crossroads
    std::cin >> N;

    int k;
    std::cin >> k; //number of lighted roads
  
    // Adjacency list 
    std::vector<std::vector<int>> adj(N+1); 
    int u,v;
    for(int i=1;i<N;i++)
    {
        std::cin >> u ;
        std::cin >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

	//Number of lights
    int num=NumberOfLights(adj,N,k);
    std::cout<< num <<"\n"; 

	return 0;
}

