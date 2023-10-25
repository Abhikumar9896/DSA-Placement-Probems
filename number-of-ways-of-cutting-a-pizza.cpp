class Solution {
private:
    static constexpr int kMod = 1'000'000'007;
    vector<vector<int>> dp;
    vector<vector<int>> sum;

public:
    int ways(vector<string> &pizza, int k) {
        const int M = pizza.size();
        const int N = pizza[0].size();
        dp.resize(M, vector<int>(N));
        sum.resize(M + 1, vector<int>(N + 1));
        
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + (pizza[i][j] == 'A');
            }
        }
        
        return max(0, dfs(0, 0, k - 1, M, N));
    }

    int dfs(int m, int n, int k, const int M, const int N) {
        if (k == 0) {
            return containApples(m, M, n, N) ? 1 : 0;
        }
        
        if (dp[m][n] >= 0) {
            return dp[m][n];
        }
        
        dp[m][n] = 0;
        
        // Make horizontal cuts
        for (int i = m + 1; i < M; ++i) {
            if (containApples(m, i, n, N)) {
                dp[m][n] = (dp[m][n] + dfs(i, n, k - 1, M, N)) % kMod;
            }
        }
        
        // Make vertical cuts
        for (int j = n + 1; j < N; ++j) {
            if (containApples(m, M, n, j)) {
                dp[m][n] = (dp[m][n] + dfs(m, j, k - 1, M, N)) % kMod;
            }
        }
        
        return dp[m][n];
    }

    bool containApples(int r1, int r2, int c1, int c2) {
        return sum[r2][c2] - sum[r2][c1] - sum[r1][c2] + sum[r1][c1] > 0;
    }
};
