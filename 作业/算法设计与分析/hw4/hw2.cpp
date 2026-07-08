#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long maxMatrixScore(int n, int m, vector<vector<int>>& matrix) {
    long long total_score = 0;
    
    for (int row = 0; row < n; ++row) {
        //dp[i][j]表示当前行剩下区间[i,j]的元素时把它们全取完能获得的最大得分
        vector<vector<long long>> dp(m, vector<long long>(m, 0));
        
        //区间长度为1时，肯定是最后一次（第m次）取走该元素
        for (int i = 0; i < m; ++i) {
            dp[i][i] = (long long)matrix[row][i] * (1LL << m); // 1LL << m 相当于 2^m
        }
        
        //从小到大递推区间长度L
        for (int L = 2; L <= m; ++L) {
            for (int i = 0; i <= m - L; ++i) {
                int j = i + L - 1;
                int k = m - L + 1; //当前处于第几次取数
                
                //尝试取左端点，或者取右端点
                long long pick_left = dp[i + 1][j] + (long long)matrix[row][i] * (1LL << k);
                long long pick_right = dp[i][j - 1] + (long long)matrix[row][j] * (1LL << k);
                
                //取两种策略的最大值
                dp[i][j] = max(pick_left, pick_right);
            }
        }
        //将每一行的最大得分累加到总得分中
        total_score += dp[0][m - 1];
    }
    
    return total_score;
}

int main() {
    int n = 2;
    int m = 3;
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {3, 4, 2}
    };
    
    cout << "Maximum Total Score: " << maxMatrixScore(n, m, matrix) << endl;

    return 0;
}