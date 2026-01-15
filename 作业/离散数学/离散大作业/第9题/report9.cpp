#include <iostream>
#include <vector>

using namespace std;




bool is_group(int G_size, const vector<vector<int>>& operation_table) {
    if (G_size <= 0) return false;

    //封闭性
    //检查运算表的每个结果是否都在集合G中[0,G_size-1]
    cout << "检查封闭性...";
    for (int i = 0; i < G_size; ++i) {
        for (int j = 0; j < G_size; ++j) {
            int result = operation_table[i][j];
            if (result < 0 || result >= G_size) {
                cout << " [失败]" << endl;
                return false;
            }
        }
    }
    cout << "[通过]" << endl;

    //结合律
    //检查(a*b)*c=a*(b*c)是否对所有a,b,c成立
    cout << "检查结合律...";
    for (int a = 0; a < G_size; ++a) {
        for (int b = 0; b < G_size; ++b) {
            for (int c = 0; c < G_size; ++c) {
                int ab = operation_table[a][b];
                int abc_left = operation_table[ab][c]; // (a * b) * c

                int bc = operation_table[b][c];
                int abc_right = operation_table[a][bc]; // a * (b * c)

                if (abc_left != abc_right) {
                    cout << " [失败: (" << a << "*" << b << ")*" << c << " != " << a << "*(" << b << "*" << c << ")]" << endl;
                    return false;
                }
            }
        }
    }
    cout << "[通过]" << endl;

    //单位元
    //寻找元素e
    cout << "检查单位元...";
    int identity_element = -1;
    bool identity_found = false;
    for (int e = 0; e < G_size; ++e) {
        bool is_identity = true;
        for (int a = 0; a < G_size; ++a) {
            // 检查e*a=a和a*e=a
            if (operation_table[e][a] != a || operation_table[a][e] != a) {
                is_identity = false;
                break;
            }
        }
        if (is_identity) {
            identity_element = e;
            identity_found = true;
            break;
        }
    }
    if (!identity_found) {
        cout << " [失败]" << endl;
        return false;
    }
    cout << " [通过, 单位元e = " << identity_element << "]" << endl;

    //逆元
    //检查每个元素 a 是否都存在逆元a'，满足a*a'=a'*a=e。
    cout << "检查逆元...";
    for (int a = 0; a < G_size; ++a) {
        bool inverse_found = false;
        for (int a_prime = 0; a_prime < G_size; ++a_prime) {
            //检查
            if (operation_table[a][a_prime] == identity_element &&
                operation_table[a_prime][a] == identity_element) {
                inverse_found = true;
                break;
            }
        }
        if (!inverse_found) {
            cout << " [失败: 元素 " << a << " 无逆元]" << endl;
            return false;
        }
    }
    cout << "[通过]" << endl;

    return true;
}

int main() {
    //预置集合大小n
    const int N = 4;

    //G={0, 1, 2, 3}，二元运算为模4加法(a+b)mod4
    //0*0=0,0*1=1,...,3*3=2
    const vector<vector<int>> CAYLEY_TABLE = {
        {0, 1, 2, 3}, 
        {1, 2, 3, 0}, 
        {2, 3, 0, 1}, 
        {3, 0, 1, 2}  
    };
    //以上为测试案例

    if (is_group(N, CAYLEY_TABLE)) {
        cout << "\n该集合关于此二元运算构成一个群。" << endl;
    }
    else {
        cout << "\n该集合关于此二元运算不构成群。" << endl;
    }

    return 0;
}