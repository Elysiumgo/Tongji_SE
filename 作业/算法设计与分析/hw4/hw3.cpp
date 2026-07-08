#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//耗时、烧毁时刻、价值、原始编号
struct Item {
    int t, d, p, id;
};

//按照烧毁时刻升序排序
bool compareItems(const Item& a, const Item& b) {
    return a.d < b.d;
}

void maxRescueValue(int n, vector<Item>& items) {
    // 按照烧毁时刻对物品进行排序
    sort(items.begin(), items.end(), compareItems);

    //找出所有物品中最晚烧毁的时刻
    int max_time = 0;
    for (int i = 0; i < n; ++i) {
        max_time = max(max_time, items[i].d);
    }

    //dp[i][j] 表示考虑前i个物品，且恰好在时刻j完成抢救时的最大价值
    //初始化为-1表示该时刻的状态尚未达到，dp[0][0]为0
    vector<vector<int>> dp(n + 1, vector<int>(max_time + 1, -1));
    dp[0][0] = 0;

    int max_val = 0;
    int best_time = 0;

    for (int i = 1; i <= n; ++i) {
        int t = items[i - 1].t;
        int d = items[i - 1].d;
        int p = items[i - 1].p;

        for (int j = 0; j <= max_time; ++j) {
            //不抢救当前物品
            dp[i][j] = dp[i - 1][j];

            //抢救当前物品
            //当前时刻 j 必须严格小于烧毁时刻d，且减去抢救时间后的前置状态是合法的
            if (j >= t && j < d && dp[i - 1][j - t] != -1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - t] + p);
            }

            //记录全局最大价值以及对应的完成时刻，用于后续回溯
            if (dp[i][j] > max_val) {
                max_val = dp[i][j];
                best_time = j;
            }
        }
    }

    //回溯寻找具体抢救了哪些物品
    vector<int> rescued_items;
    int curr_time = best_time;
    for (int i = n; i >= 1; --i) {
        int t = items[i - 1].t;
        //如果当前状态的价值不等于上一层同时间的价值，说明必定选择了第i个物品
        if (dp[i][curr_time] != dp[i - 1][curr_time]) {
            rescued_items.push_back(items[i - 1].id);
            curr_time -= t; //时间倒退
        }
    }

    //倒序回溯翻转
    reverse(rescued_items.begin(), rescued_items.end());

    // 输出结果
    cout << max_val << endl;
    cout << rescued_items.size() << endl;
    for (size_t i = 0; i < rescued_items.size(); ++i) {
        cout << rescued_items[i] << (i == rescued_items.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    int n = 3;
    vector<Item> items = {
        {3, 7, 4, 1},
        {2, 6, 5, 2},
        {3, 7, 6, 3}
    };
    
    maxRescueValue(n, items);
    return 0;
}