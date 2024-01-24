#include<iostream>
using namespace std;

int main()
{
    // Read input
    int N,M,K,X; //number of crossroads
    cin >> N;
    cin >> M; // Grid dimentions NxM
    cin >> K; // Number of crossings
    cin >> X; // Maximum Number of crossings


    int C[N*M] ;
    for (int i = 0; i < N*M; i++ ) 
        C[i] = -1;
    
    int s,e;
    for (int i = 0; i < K; i++)
    {
        cin >> s;
        cin >> e;
        C[s] = e;
    }

    // DP[i*j][k] is the number of paths with k crossings from (i,j) to (0,0)
    int DP[N*M][X+1];

    // Initialization

    // Start
    DP[0][0] = 1;

    // First line
    for (int j = 1; j < M; j++)
    {
        if (C[j]==-1) 
            DP[j][0] = DP[j-1][0] % 1000000103;
        else 
            DP[j][0] = 0;
    }

    //The rest
    for (int i = 1; i < N; i++)
    {
        if (C[i*M] == -1) 
            DP[i*M][0] = DP[(i-1)*M][0] % 1000000103;
        else 
            DP[i*M][0] = 0;

        for (int j = 1; j < M; j++)
        {
            if (C[i*M+j] == -1) 
                DP[i*M+j][0] = ( DP[(i-1)*M+j][0]+DP[i*M+j-1][0] ) % 1000000103;
            else 
                DP[i*M+j][0] = 0;
        }
    }

    // k>0

    for (int k=1; k<X+1; k++)
    {
        // Start
        DP[0][k]=0;

        // First line
        for (int j = 1; j <M; j++)
        {
            if (C[j] == -1) 
                DP[j][k] = DP[j-1][k] % 1000000103 ;
            else 
                DP[j][k] = DP[C[j]][k-1] % 1000000103 ;
        }

        //The rest
        for (int i=1; i<N; i++)
        {
            if (C[i*M] == -1) 
                DP[i*M][k] = DP[(i-1)*M][k] % 1000000103 ;
            else 
                DP[i*M][k] = DP[C[i*M]][k-1] % 1000000103;

            for (int j=1; j<M; j++)
            {
                if (C[i*M+j] == -1) 
                    DP[i*M+j][k] = ( DP[(i-1)*M+j][k] + DP[i*M+j-1][k] ) % 1000000103;
                else 
                    DP[i*M+j][k] = DP[C[i*M+j]][k-1] % 1000000103;
            }
        }
       
    }

    long int sum=0;

    for (int k=0; k<X+1; k++)
        sum += DP[N*M-1][k];

    cout << sum  % 1000000103 << "\n" ;

    return 0;
}





