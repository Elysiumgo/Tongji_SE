#include <bits/stdc++.h>
#include<vector>
using namespace std;

//将数组按从大到小排列
int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[left]; // 选取最左侧为基准
    int l = left, r = right;
    
    while (l < r) {
        //从右向左找第一个大于基准的数
        while (l < r && nums[r] <= pivot) r--;
        nums[l] = nums[r];
        //从左向右找第一个小于基准的数
        while (l < r && nums[l] >= pivot) l++;
        nums[r] = nums[l];
    }
    nums[l] = pivot;
    return l; //返回基准值的最终位置
}

//快速选择函数
int quickSelect(vector<int>& nums, int left, int right, int k) {
    if (left == right) return nums[left];

    int pos = partition(nums, left, right);
    int target = k - 1; //第k大对应的索引是k-1

    if (pos == target) {
        return nums[pos];
    } else if (pos > target) {
        //在左区间找
        return quickSelect(nums, left, pos - 1, k);
    } else {
        //在右区间找
        return quickSelect(nums, pos + 1, right, k);
    }
}

int main(){
    int n,k;
    vector<int> nums;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        nums.push_back(x);
    }
    //以上为处理输入的部分
   if (k > 0 && k <= n) {
        cout << quickSelect(nums, 0, n - 1, k) << endl;
    } else {
        cout << "Invalid k" << endl;
    }
    return 0;
}