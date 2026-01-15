#include<iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <climits>
#include <limits>
using namespace std;


class CatalanCalculator {
private:
    static const int MAX_SAFE_N = 35;  // long long安全范围
    

public:
    // 递推公式Cn = Cn-1 × (4n-2) / (n+1)
   static bool calculate(int n, long long& result) {
        if (n < 0|| n > MAX_SAFE_N)
            return false;
        
        if (n <= 1) {
            result = 1;
            return true;
        }
        result = 1;
        for (int i = 1; i <= n; ++i) {

            if (result > LLONG_MAX / (4 * i - 2)) {
                return false;  // 乘法前检查溢出
            }
            result = result * (4ll * i - 2);
            result = result / (i + 1);
        }
        return true;

    }

    // 动态规划方法：Cₙ =求和[Cᵢ × Cₙ₋₁₋ᵢ]
   static bool calculateDP(int n, long long& result) {
       if (n < 0 || n > MAX_SAFE_N)
           return false;

       if (n <= 1) {
           result = 1;
           return true;
       }

       vector<long long> dp(n + 1, 0);
       dp[0] = 1;
       dp[1] = 1;

       for (int i = 2; i <= n; ++i) {
           dp[i] = 0;
           for (int j = 0; j < i; ++j) {
               // 溢出检查
               if (dp[j] > 0 && dp[i - 1 - j] > LLONG_MAX / dp[j]) {
                   return false;
               }
               long long product = dp[j] * dp[i - 1 - j];

               if (dp[i] > LLONG_MAX - product) {
                   return false;
               }
               dp[i] += product;
           }
       }

       result = dp[n];
       return true;
   }
   static int getMaxSafeN() {
       return MAX_SAFE_N;
   }

   static bool isSafe(int n) {
       return (n >= 0 && n <= MAX_SAFE_N);
   }
};





int main() {
    cout << "卡特兰数计算器 - 安全范围: n = 0 到 " << CatalanCalculator::getMaxSafeN() << "\n\n";

    // 测试正常值
    cout << "测试案例:" << endl;
    vector<int> test_values = { 0, 1, 5, 10, 15, 20 };

    for (int n : test_values) {
        long long result;
        bool success = CatalanCalculator::calculate(n,result);
        cout << "C(" << n << ") = ";
        if (success) {
            cout << result;
        }
        else {
            cout << "计算失败";
        }
        cout << endl;
    }


    cout << endl << "以下为手动输入测试：" << endl;
    
    int num;
    vector<int> numbers;
    cout << "卡特兰数计算器 - 安全范围: n = 0 到 " << CatalanCalculator::getMaxSafeN() << "\n\n"; 
    cout << "请输入要求的卡特兰数序号（输入负数退出）：";
    while (cin >> num) {
        if (num < 0) 
            break;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入错误，请重新输入（输入负数退出）：";
            continue;
        }
        numbers.push_back(num);
    }


    for (int n : numbers) {
        long long result;
        bool success = CatalanCalculator::calculate(n, result);
        cout << "C(" << n << ") = ";
        if (success) {
            cout << result;
        }
        else {
            cout << "计算失败";
        }
        cout << endl;
    }

    

    return 0;
}




