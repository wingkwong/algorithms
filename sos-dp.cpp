// SOS DP (Subset Sum Over Subsets Dynamic Programming) is a technique used to efficiently solve problems 
// that involve iterating over all subsets of a set.

// ref: https://codeforces.com/blog/entry/45223

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1 << 20;

vector<int> dp(MAXN);

void sos_dp(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        dp[1 << i] = a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
}

int main() {
    vector<int> a = {1, 2, 3};
    sos_dp(a);
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        cout << "Subset " << mask << ": " << dp[mask] << endl;
        // Subset 0: 0
        // Subset 1: 1
        // Subset 2: 2
        // Subset 3: 3
        // Subset 4: 3
        // Subset 5: 4
        // Subset 6: 5
        // Subset 7: 6
    }
    return 0;
}