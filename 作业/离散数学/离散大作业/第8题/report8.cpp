#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

class TSP_MST_Approximation {
private:
    int num_cities;
    vector<vector<int>> dist_matrix;
    vector<vector<int>> mst_adj;
    vector<int> path;

    void buildMST() {
        vector<int> key(num_cities, numeric_limits<int>::max());
        vector<bool> inMST(num_cities, false);
        vector<int> parent(num_cities, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        key[0] = 0;
        pq.push({ 0, 0 });

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (int v = 0; v < num_cities; v++) {
                if (u != v && !inMST[v] && dist_matrix[u][v] < key[v]) {
                    key[v] = dist_matrix[u][v];
                    parent[v] = u;
                    pq.push({ key[v], v });
                }
            }
        }

        //构建MST邻接表
        mst_adj.clear();
        mst_adj.resize(num_cities);
        for (int i = 1; i < num_cities; i++) {
            if (parent[i] != -1) {
                mst_adj[i].push_back(parent[i]);
                mst_adj[parent[i]].push_back(i);
                cout << "MST边: " << parent[i] << " - " << i << " (距离: " << dist_matrix[parent[i]][i] << ")" << endl;
            }
        }
    }

    void DFS_Optimized(int u, vector<bool>& visited) {
        visited[u] = true;
        path.push_back(u);

        //对邻居按距离排序，优先访问可能得到更好TSP路径的邻居
        vector<pair<int, int>> neighbors;
        for (int v : mst_adj[u]) {
            if (!visited[v]) {
                neighbors.push_back({ dist_matrix[u][v], v });
            }
        }

        //按距离升序排序
        sort(neighbors.begin(), neighbors.end());

        for (auto& neighbor : neighbors) {
            if (!visited[neighbor.second]) {
                DFS_Optimized(neighbor.second, visited);
            }
        }
    }

public:
    TSP_MST_Approximation(const vector<vector<int>>& distances)
        : dist_matrix(distances), num_cities(distances.size()) {
        mst_adj.resize(num_cities);
    }

    void solve() {
        if (num_cities <= 1) {
            cout << "城市数量太少" << endl;
            return;
        }

        cout << "=== 旅行商问题MST近似算法 ===" << endl;

        //构建MST
        cout << "\n步骤1: 构建最小生成树" << endl;
        buildMST();

        //DFS遍历
        cout << "\n步骤2: DFS遍历MST" << endl;
        vector<bool> visited(num_cities, false);
        path.clear();
        DFS_Optimized(0, visited);

        //计算总距离
        int total_distance = 0;
        cout << "\n步骤3: 计算TSP路径" << endl;
        cout << "生成的TSP路径: ";
        for (int i = 0; i < num_cities; i++) {
            cout << path[i];
            if (i < num_cities - 1) cout << " -> ";

            int u = path[i];
            int v = path[(i + 1) % num_cities];
            total_distance += dist_matrix[u][v];
        }
        cout << " -> " << path[0] << endl;

        cout << "路径长度: " << total_distance << endl;

        //显示详细距离计算
        cout << "\n距离计算详情:" << endl;
        for (int i = 0; i < num_cities; i++) {
            int u = path[i];
            int v = path[(i + 1) % num_cities];
            cout << path[i] << "->" << v << ": " << dist_matrix[u][v] << endl;
        }

        
        cout << "\n对比分析:" << endl;
        cout << "MST近似解: " << total_distance << endl;
        cout << "理论最优解: 80 (0->1->3->2->0)" << endl;
        cout << "近似比: " << fixed << (double)total_distance / 80.0 << endl;
        cout << "性能损失: " << total_distance - 80 << endl;
    }
};

int main() {
    vector<vector<int>> distances = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP_MST_Approximation tsp_solver(distances);
    tsp_solver.solve();

    return 0;
}