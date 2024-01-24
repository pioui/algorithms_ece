#include <iostream>
#include <vector>
#include <algorithm>

// Binary searches index 
int BSIndex(const std::vector<int>& c, int v) 
{
    int left = 0;
    int right = (int)c.size() - 1;
    while( right - left > 1 ) 
    {
        int mid = (left + right) / 2;
        if (c[mid] < v) 
        {
            left = mid + 1;
        }
        else right = mid;
    }
    return left;
}

int BSIndexLIS(std::vector<int>& v, int right, int value)   
{   
    int left=-1;  
    while (right - left > 1)   
    {   
        int mid = left + (right - left) / 2;   
        if (v[mid] >= value)   
            right = mid;   
        else  
            left = mid;   
    }   
        
    return right;   
}   

int BSIndexLDS(std::vector<int>& v, int right, int value)   
{   
    int left=-1;  
    while (right - left > 1)   
    {   
        int mid = left + (right - left) / 2;   
        if (v[mid] <= value)   
            right = mid;   
        else  
            left = mid;   
    }   
        
    return right;   
} 
      
// Print Vector 
// Not Usefull for Grader xD 
void print(std::vector<int> const &input)  
{  
    for (auto const& i: input) {  
        std::cout << i << " ";  
    }  
    std::cout << "\n";  
    return ;   
}  
      
// Calculate Longest Increasing Subsequences Lengths l for vector c with 
// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
void LISLength(std::vector<int>& c,std::vector<int>& l)   
{   
    if (c.size() == 0)   
        return ;   
        
    std::vector<int> tail(c.size(), 0);   
    l.push_back(0);
    l.push_back(1);
    int length = 1;   
    int prev=c[0];  
    tail[0] = c[0];   
    for (size_t i = 1; i < c.size(); i++) {     
      
        // Smallest value goes to the tail  
        if (c[i] < tail[0])   
        tail[0] = c[i];   
        
        // Biggest value until now extedts the subsequence  
        else if (c[i] > tail[length - 1])   
            tail[length++] = c[i];   
        
        // Find where c[i] can be inserted as end with BS search  
        else{  
            int index=BSIndexLIS(tail,length - 1, c[i]);
            tail[index] = c[i];  
            }
        // Store the biggest length in the vector  
        l.push_back(length);  
        prev=c[i];   
    }  
    return ;        
}   
      
// Calculate Longest Decreasing Subsequences Lengths l for vector c   
void LDSLength(std::vector<int>& c,std::vector<int>& l)   
{   
    if (c.size() == 0)   
        return ;   
        
    std::vector<int> tail(c.size(), 0);   
    l.push_back(0);
    l.push_back(1);
    int length = 1;   
    int prev=c[0];  
    tail[0] = c[0];   
    for (size_t i = 1; i < c.size(); i++) {   
        // Biggest value goes to the tail  
        if (c[i] > tail[0])   
            tail[0] = c[i];   
      
        // Smallest value until now extedts the subsequence  
        else if (c[i] < tail[length - 1])   
            tail[length++] = c[i];   
      
        // Find where c[i] can be inserted as end with BS search  
        else
        {  
            int index=BSIndexLDS(tail,length - 1, c[i]);
            tail[index] = c[i];  
        } 
        // Store the biggest length in the vector  
        l.push_back(length);  
        prev=c[i];   
        }   
    return ;   
}  

// Binary Index tree for prefix maximum queries
class BITree 
{
    private:
        std::vector<int> value;
    public:
        BITree(int n) : value(n+1, 0) {}
        void update(int i, int v) 
        {
            for (++i; i < value.size(); i += i & -i) 
            {
                value[i] = std::max(value[i], v);
            }
        }
        int get(int i) 
        {
            int val = 0;
            for (++i; i > 0; i -= i & -i) 
            {
                val = std::max(val, value[i]);
            }
            return val;
        }
};

// Deletes the duplicate values and returns the new length
int Unique(std::vector<int>& c) {
    //Sort credits
    std::vector<int> sorted = c;
    sort(sorted.begin(), sorted.end());
    //Put duplicate values in the end
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    for (int& v : c) 
    {
        v = BSIndex(sorted, v);
    }
    return sorted.size();
}

// Returns length of LIS subsequence with at most k exceptions
// https://stackoverflow.com/questions/59474521/longest-k-sequential-increasing-subsequences/59521736?noredirect=1&fbclid=IwAR3C8LJE7HAg1XULFxrYeInUNtUIjUeZIyJjt6t4rHkgwffJlkhdcaMG2Ks#comment105255444_59521736
int LISkLength(std::vector<int> c, int k) {
    //Recursion using DP
    int m = Unique(c);
    std::vector<int> DP(c.size(), 0);
    for (int j = 0; j<k+1; ++j )
    {
        // Length of longest subsequence with at most j-1 exceptions ending before i-th element
        int maxleft = 0; 
        // Length of longest subsequence with at most j exceptions ending at i-th element
        BITree bittree(m+1); 
        for (int i = 0; i < c.size(); ++i) 
        {
            int off = 1 + std::max(maxleft, bittree.get(c[i]));
            maxleft = std::max(maxleft, DP[i]);
            DP[i] = off;
            bittree.update(c[i]+1, off);
        }
        if (j == k) 
        {
            return bittree.get(m);
        }
    }
}

int main() {


//Read Input  
int N;  
std::cin >> N;  

int k;  
std::cin >> k;  

std::vector<int> credits;  
int input;  
for (int i=0;i<N;i++)  
{  
    std::cin >> input;  
    credits.push_back(input);
}  

//Calculate LIS with k Exceptions 
if (k>1)  
{   
    std::cout << LISkLength(credits,k) << '\n';
}
//Calculate LIS with 1 Exception
else 
{
    //Calculate Length of LIS for each subsequence from start of credits  
    std::vector<int> lengths;  
    LISLength(credits,lengths);   
      
    //Calculate Length of LDS for each subsequence until end of credits  
    std::reverse(credits.begin(),credits.end());  
    std::vector<int> lengths_r;  
    LDSLength(credits,lengths_r);   
    std::reverse(lengths_r.begin(),lengths_r.end());  
      
    //Calculate the sum  
    std::vector<int> sums;  
    for (int i = 0; i < lengths.size(); i++)   
    {  
        sums.push_back(lengths[i]+lengths_r[i]);  
    }  
    
    // Find the max element   
    std::cout << *max_element(sums.begin(), sums.end()) <<"\n" ; 
}
return 0;
}