#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int strongPasswordChecker(string password) {
    int n = password.length();
    int has_lower = 0, has_upper = 0, has_digit = 0;
    
    //统计缺失的字符类型
    for (char c : password) {
        if (islower(c)) has_lower = 1;
        else if (isupper(c)) has_upper = 1;
        else if (isdigit(c)) has_digit = 1;
    }
    int missing_types = 3 - (has_lower + has_upper + has_digit);
    
    // 长度小于6，通过插入字符解决
    if (n < 6) {
        return max(6 - n, missing_types);
    }
    
    int replace = 0;
    int delete_mod0 = 0, delete_mod1 = 0;
    
    //统计连续字符段的长度，并计算基础替换次数
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && password[j] == password[i]) {
            j++;
        }
        int len = j - i;
        if (len >= 3) {
            replace += len / 3;
            //记录长度对3取模的结果，用于大于20时的贪心删除策略
            if (len % 3 == 0) delete_mod0++;
            else if (len % 3 == 1) delete_mod1++;
        }
        i = j;
    }
    
    //长度在6到20之间，只需考虑替换操作和补齐字符类型
    if (n <= 20) {
        return max(replace, missing_types);
    }
    
    //长度大于20，需要删除多余字符，并用删除来抵消替换次数
    int delete_count = n - 20;
    
    // 优先删除长度%3==0 的连续串中的字符
    replace -= min(delete_count, delete_mod0);
    
    //其次删除长度%3==1 的连续串
    int use_mod1 = min(max(delete_count - delete_mod0, 0), delete_mod1 * 2);
    replace -= use_mod1 / 2;
    
    //最后删除长度%3==2的连续串
    int use_mod2 = max(delete_count - delete_mod0 - use_mod1, 0);
    replace -= use_mod2 / 3;
    
    return delete_count + max(replace, missing_types);
}

int main() {
    string password = "aA1";
    
    cout << "Minimum Operations: " << strongPasswordChecker(password) << endl;

    return 0;
}