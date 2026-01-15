#include <iostream>
#include <vector>
using namespace std;

//使用Warshall算法求解传递闭包
vector<vector<int>> warshallClosure(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> closure = matrix;  //初始化闭包矩阵

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // 如果存在路径i->k和k->j，则设置 i->j
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }

    return closure;
}


void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "请输入关系矩阵的阶数: ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    cout << "请输入" << n << "×" << n << "关系矩阵(0或1):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    cout << "\n原始关系矩阵:" << endl;
    printMatrix(matrix);

    vector<vector<int>> closure = warshallClosure(matrix);

    cout << "\n传递闭包矩阵:" << endl;
    printMatrix(closure);

    return 0;
}