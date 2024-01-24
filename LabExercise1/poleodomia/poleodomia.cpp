#include<iostream>
#include<algorithm>
#include <stack> 
using namespace std;

void calculate_left_cost(unsigned long long int heights[],int N,unsigned long long int cost[])
{
    stack <int> numbers;
    numbers.push(heights[0]);

    stack <int> indices;
    indices.push(0);


    cost[0]=numbers.top();

    for (int i=1;i<N;i++)
    {
    	while (heights[i]>numbers.top())
    	{
    		numbers.pop();
    		indices.pop();
    		if (numbers.empty()) 
    			{
    				break;
    			}
    	}

    	if (!numbers.empty())
    	{
    		cost[i]=cost[indices.top()]+(i-indices.top())*heights[i];
    	}
    	else
    	{
    		cost[i]=(i+1)*heights[i];
    	}
   		numbers.push(heights[i]);
   		indices.push(i);
    }
}

void calculate_right_cost(unsigned long long int heights[],int N,unsigned long long int cost[])
{
    stack <int> numbers;
    numbers.push(heights[N-1]);

    stack <int> indices;
    indices.push(N-1);


    cost[N-1]=numbers.top();

    for (int i=N-2;i>-1;i--)
    {
        while (heights[i]>numbers.top())
        {
            numbers.pop();
            indices.pop();
            if (numbers.empty()) 
                {
                    break;
                }
        }

        if (!numbers.empty())
        {
            cost[i]=cost[indices.top()]+(indices.top()-i)*heights[i];
        }
        else
        {
            cost[i]=(N-i)*heights[i];
        }
        numbers.push(heights[i]);
        indices.push(i);
    }
}




int main()
{
	// Read input
	int N;
	cin >> N;

	int k;
	unsigned long long int H[N];
	for(int i=0;i<N;i++)
	{
		cin >> H[i];
	}

    unsigned long long int left_cost[N];
    calculate_left_cost(H,N,left_cost);

    unsigned long long int right_cost[N];
    calculate_right_cost(H,N,right_cost);
    
    unsigned long long total_cost[N];

    for (int c = 0; c < N; c++) 
    {
    total_cost[c] = left_cost[c] + right_cost[c]-H[c];
    }

    unsigned long long int* min; 

    min = std::min_element(total_cost, total_cost + N); 
  
    cout << *min << "\n"; 


    return 0;
}

