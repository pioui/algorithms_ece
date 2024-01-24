#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define rep(i,n) for (int i = 0; i < (n); i++)  
#define rrep(i,n) for (int i = (n)-1; i >= 0; i--)
#define rap(i,a,n) for (int i = a; i < (n); i++) 
#define rrap(i,n,a) for (int i = (n)-1; i >= a; i--) 
#define LL_MAX 9223372036854775807

typedef vector<int> vi;  
typedef pair<int,int> ii;  
typedef vector<ii> vii;  
typedef list<int> li;  
typedef unordered_map<int,int> mii;

vii v;
/*
 * for every planet, v will include:
 * 1) first: the diameter
 * 2) second: the height
 */

vector<vector<vi>> adj;
/*
 * adjacency list for the trees per planet
 */

//dfs1: find the height and one point of the diameter for the kk-th planet (0-indexed)

vector<bool> vis;
//help vector for visited in the dfs functions

vi dist;
//help vector for distance in the dfs functions

ii dfs1(int kk, int par, int mx, int mxnode) {
    for (auto j: adj[kk][par]) {
        if (vis[j]) continue;
        vis[j] = true;
        dist[j] = dist[par]+1;
        if (dist[j] > mx) {
            mx = dist[j];
            mxnode = j;
        }
        ii p = dfs1(kk,j,mx,mxnode);
        if (p.first > mx) {
            mx = p.first;
            mxnode = p.second;
        }
    }
    return (ii{mx,mxnode});
}

int dfs2(int kk, int par, int mx) {
    for (auto j: adj[kk][par]) {
        if (vis[j]) continue;
        vis[j] = true;
        dist[j] = dist[par]+1;
        mx = max(dist[j], mx);
        mx = max(mx, dfs2(kk,j,mx));
    }
    return mx;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k,a;
    cin >> k;
    ii p;
    v.clear();
    adj.assign(k,vector<vi>());
    rep(kk,k) {
        int n;
        cin >> n;
        adj[kk].assign(n,vi());
        if (n == 1) cin >> a;
        rep(i,n-1) {
            cin >> a;
            a--;
            adj[kk][i+1].push_back(a);
            adj[kk][a].push_back(i+1);
        }
        vis.assign(n,false);
        vis[0] = true;
        dist.assign(n,-1);
        dist[0] = 0;
        p = dfs1(kk,0,0,0);
        //until now:
        //p.first = height from root
        //p.second = the node that is the edge of the diameter
        vis.assign(n,false);
        vis[p.second] = true;
        dist.assign(n,-1);
        dist[p.second] = 0;
        v.push_back(ii{dfs2(kk,p.second,0),p.first});

        //job finished for planet kk (0-indexed)
    }

    //debugging lines
    /*
    cout << "Diameters are:\n";
    rep(kk,k) cout << v[kk].first << ' ';
    cout << '\n';
    cout << "Heights are:\n";
    rep(kk,k) cout << v[kk].second << ' ';
    cout << '\n';
    */

    int maxd = -1; //looking for the maximum diameter
    rep(kk,k) if (v[kk].first > maxd) maxd = v[kk].first;

    //we will call the heightval the two heights that combined with their
    //maximum distance give the potential best possible value for the trip

    //making the first parse for the heightval (the best distance is from left to right)
    int mxhv = -1;
    int curbest = v[0].second + k - 1;
    rap(kk,1,k) {
        mxhv = max(mxhv, curbest + v[kk].second);
        curbest = max(curbest-1, v[kk].second+k-1);
    }

    //making the second parse for the heightval
    curbest = v[0].second + 1;
    rap(kk,1,k) {
        mxhv = max(mxhv, curbest + v[kk].second);
        curbest = max(curbest+1, v[kk].second+1);
    }

    cout << max(mxhv,maxd) << '\n';

    return 0;
    //compile: g++ -std=c++14 -O2 -Wall NAME.cpp -o NAME
}
