#include <iostream>
#include <climits>
using namespace std;

const int N = 100; //图的最大顶点数
int p[N], key[N], tb[N][N];//父节点数组,权值数组,邻接矩阵

void prim(int v, int n) {
    int min_val;
    for (int i = 1; i <= n; i++) {
        p[i] = v;
        key[i] = tb[v][i];
    }
    key[v] = 0;

    for (int i = 2; i <= n; i++) {
        min_val = INT_MAX;
        //在未加入的顶点中找距离生成树最近的顶点
        for (int j = 1; j <= n; j++) {
            if (key[j] > 0 && key[j] < min_val) {
                v = j; //记录这个顶点
                min_val = key[j]; //记录最小距离
            }
        }
        cout << "最小耗费是：" << p[v] << " 和 " << v << endl;
        key[v] = 0; //顶点v已加入生成树

        for (int j = 1; j <= n; j++) {
            if (tb[v][j] < key[j]) {
                p[j] = v;
                key[j] = tb[v][j];
            }
        }
    }
}

int main() {
    int n, m;
    int u, v, w;

    cout << "请输入所求图的顶点数目和边的数目（输入两个0结束）：" << endl;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) 
            break;

        // 初始化邻接矩阵
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                tb[i][j] = INT_MAX;
            }
        }

        cout << "请输入两条边的节点序号以及它们的权值：" << endl;
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            tb[u][v] = tb[v][u] = w;
        }

        prim(1, n);
        cout << endl;
        cout << "请输入所求图的顶点数目和边的数目（输入两个0结束）：" << endl;


    }

    return 0;
}