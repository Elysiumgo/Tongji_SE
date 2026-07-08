#include <iostream>
#include <vector>
#include <algorithm>
#include<numeric>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {
            return false;
        }
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[target];
    }

};

int main() {
    Solution solution;
    vector<int> nums = {1, 2, 3, 5};
    bool result = solution.canPartition(nums);
    cout << (result ? "true" : "false") << endl; 
    return 0;
}