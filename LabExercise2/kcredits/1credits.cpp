    #include <iostream>   
    #include <vector>   
    #include <algorithm>      
      
    // Binary search left is always -1  
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
      
    //Print Vector  
    void print(std::vector<int> const &input)  
    {  
        for (auto const& i: input) {  
            std::cout << i << " ";  
        }  
        std::cout << "\n";  
        return ;   
      
    }  
      
    //Calculate Longest Increasing Subsequences Lengths l for vector c with nlogn complexity    
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
      
    //Calculate Longest Decreasing Subsequences Lengths l for vector c with nlogn complexity    
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
        
    int main()   
    {  
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
      
        //Calculate Length of LIS for each subsequence from start of credits  
      
        std::vector<int> lengths;  
        LISLength(credits,lengths);   
        //print(lengths);  
      
        //Calculate Length of LDS for each subsequence until end of credits  
        std::reverse(credits.begin(),credits.end());  
        std::vector<int> lengths_r;  
        LDSLength(credits,lengths_r);   
        std::reverse(lengths_r.begin(),lengths_r.end());  
        //print(lengths_r);  
      
        //Calculate the sum  
        std::vector<int> sums;  
        for (int i = 0; i < lengths.size(); i++)   
        {  
            sums.push_back(lengths[i]+lengths_r[i]);  
        }  
        //print(sums);  
      
        // Find the max element   
        std::cout << *max_element(sums.begin(), sums.end()) <<"\n" ;   
        for (int j = 0;; ++j) 
        {
            print j;
        }
        return 0;   
    }   