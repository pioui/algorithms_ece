#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Binary Index tree for prefix maximum queries
class Fenwick {
    private:
        vector<int> val;
    public:
        Fenwick(int n) : val(n+1, 0) {}

        // Sets value at position i to maximum of its current value and 
        void inc(int i, int v) {
            for (++i; i < val.size(); i += i & -i) val[i] = max(val[i], v);
        }

        // Calculates prefix maximum up to index i
        int get(int i) {
            int res = 0;
            for (++i; i > 0; i -= i & -i) res = max(res, val[i]);
            return res;
        }
};

// Binary searches index of v from sorted vector vec
int bins(const vector<int>& vec, int v) {
    int low = 0;
    int high = (int)vec.size() - 1;
    while(low != high) {
        int mid = (low + high) / 2;
        if (vec[mid] < v) low = mid + 1;
        else high = mid;
    }
    return low;
}

// Compresses the range of values to [0, m), and returns m
int compress(vector<int>& vec) {
    vector<int> ord = vec;
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());
    for (int& v : vec) v = bins(ord, v);
    return ord.size();
}

// Returns length of longest strictly increasing subsequence with at most k exceptions
int lisExc(int k, vector<int> vec) {
    int n = vec.size();
    int m = compress(vec);
    vector<int> dp(n, 0);
    for (int j = 0;; ++j) {
        Fenwick fenw(m+1); // longest subsequence with at most j exceptions ending at this value
        int max_exc = 0; // longest subsequence with at most j-1 exceptions ending before this
        for (int i = 0; i < n; ++i) {
            int off = 1 + max(max_exc, fenw.get(vec[i]));
            max_exc = max(max_exc, dp[i]);

            dp[i] = off;
            fenw.inc(vec[i]+1, off);
        }
        if (j == k) return fenw.get(m);
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> vec(n);
    for (int i = 0; i < n; ++i) cin >> vec[i];

    int res = lisExc(k, vec);
    cout << res << '\n';
}