#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minSecondsToRemoveGems(int n, vector<int>& colors) {
    if (n == 0) return 0;
    
    //初始化
    vector<vector<int>> dp(n, vector<int>(n, 1e9));
    
    //长度为1的区间
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    
    //长度为2的区间
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i+1] = (colors[i] == colors[i+1]) ? 1 : 2;
    }
    
    //从小到大枚举区间长度L
    for (int L = 3; L <= n; ++L) {
        for (int i = 0; i <= n - L; ++i) {
            int j = i + L - 1;
            
            //如果首尾元素相等，可以随内部最后一次消除一起带走
            if (colors[i] == colors[j]) {
                dp[i][j] = dp[i+1][j-1];
            }
            
            //枚举分割点，将区间分为两部分分别消除
            for (int k = i; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
            }
        }
    }
    
    return dp[0][n-1];
}
int main() {
    //测试案例
    int n1 = 3;
    vector<int> colors1 = {1, 2, 1};
    cout << "Test Case 1 Output: " << minSecondsToRemoveGems(n1, colors1) << endl;

    //测试案例2
    int n2 = 7;
    vector<int> colors2 = {1, 4, 4, 2, 3, 2, 1};
    cout << "Test Case 2 Output: " << minSecondsToRemoveGems(n2, colors2) << endl;

    return 0;
}