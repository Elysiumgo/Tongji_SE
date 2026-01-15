#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

//表示不可达或未初始化距离
const int INF = 1e9;


class ChinesePostman {
private:
    int V;                             //顶点数
    vector<vector<int>> graph;         //邻接矩阵，存储直接边的权重
    vector<vector<int>> dist;          //距离矩阵，存储任意两点间的最短距离



    //找到所有奇度数顶点
    vector<int> findOddDegreeVertices() {
        vector<int> odd_vertices;
        for (int i = 0; i < V; ++i) {
            int degree = 0;
            for (int j = 0; j < V; ++j) {
                //如果i到j有边，则增加i的度数
                if (graph[i][j] != INF) {
                    degree++;
                }
            }
            //无向图，且邻接矩阵是对称的，所以直接计数即可
            if (degree % 2 != 0) {
                odd_vertices.push_back(i);
            }
        }
        return odd_vertices;
    }



    //Warshall计算所有点最短路径
    void floydWarshall() {
        //初始化dist矩阵，从graph复制初始边权重
        dist = graph;

        //设置自身到自身的距离为0
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0;
        }

        //K是中转点
        for (int k = 0; k < V; ++k) {
            //I是起点
            for (int i = 0; i < V; ++i) {
                //J是终点
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        // 尝试通过K来优化I到J的距离
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }

    // 最小权完美匹配(MWPM)
    int minimumWeightPerfectMatching(const vector<int>& odd_vertices) {
        int n = odd_vertices.size();
        if (n == 0) return 0;

        //理论上连通无向图的奇度数顶点个数n必须是偶数
        if (n % 2 != 0) 
            return INF;

        vector<bool> matched(n, false); //记录奇度数点是否已被匹配
        int min_cost = INF;

        //回溯函数，current_cost是当前已匹配的权重总和
        function<void(int, int)> backtrack =
            [&](int current_cost, int matched_count) {

            //终止条件为所有奇度数点都已配对
            if (matched_count == n) {
                min_cost = min(min_cost, current_cost);
                return;
            }

            //找到第一个未匹配的奇度数点u_idx
            int u_idx = -1;
            for (int i = 0; i < n; ++i) {
                if (!matched[i]) {
                    u_idx = i;
                    break;
                }
            }
            if (u_idx == -1) 
                return; //保护机制，其实不应发生

            //标记u_idx为已匹配，准备为其寻找配对
            matched[u_idx] = true;

            //遍历所有可能的配对v_idx(从u_idx之后开始，避免重复配对)
            for (int v_idx = u_idx + 1; v_idx < n; ++v_idx) {
                if (!matched[v_idx]) {
                    matched[v_idx] = true;

                    int u_node = odd_vertices[u_idx]; //顶点编号
                    int v_node = odd_vertices[v_idx]; //顶点编号

                    if (dist[u_node][v_node] != INF) {
                        //递归进行下一轮配对
                        backtrack(current_cost + dist[u_node][v_node], matched_count + 2);
                    }

                    matched[v_idx] = false; //撤销v_idx的匹配
                }
            }

            matched[u_idx] = false; //撤销u_idx的匹配

        };

        backtrack(0, 0);
        return min_cost;
    }


public:
    ChinesePostman(int num_vertices) : V(num_vertices) {
        //初始化邻接矩阵，所有距离设为无穷大
        graph.assign(V, vector<int>(V, INF));
    }

    //添加无向边(u, v, weight)
    void addEdge(int u, int v, int weight) {
        //u和v必须在有效范围内
        if (u < 0 || u >= V || v < 0 || v >= V) return;

        //无向图，确保对称性，且取最小权重（处理平行边）
        graph[u][v] = min(graph[u][v], weight);
        graph[v][u] = min(graph[v][u], weight);
    }

    //主求解函数
    long long solveCPP() {
        long long total_edge_weight = 0;

        //计算所有边的总权重 (只算一次)
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                if (graph[i][j] != INF) {
                    total_edge_weight += graph[i][j];
                }
            }
        }

        cout << "--- 中国邮递员问题求解 ---" << endl;
        cout << "原图所有边总权重: " << total_edge_weight << endl;

        //找到所有奇度数顶点
        vector<int> odd_vertices = findOddDegreeVertices();

        if (odd_vertices.empty()) {
            cout << "图为欧拉图，无需重复边。" << endl;
            cout << "最短路径总长度: " << total_edge_weight << endl;
            return total_edge_weight;
        }

        cout << "发现奇度数顶点 (共 " << odd_vertices.size() << " 个): ";
        for (int v : odd_vertices) {
            cout << v << " ";
        }
        cout << endl;

        //计算所有点对最短路径 (Floyd-Warshall)
        floydWarshall();

        //最小权完美匹配 (MWPM)
        int min_matching_weight = minimumWeightPerfectMatching(odd_vertices);

        if (min_matching_weight == INF) {
            cout << "错误：图不连通或奇度数顶点数量异常。" << endl;
            return -1;
        }

        cout << "最小权完美匹配的附加权重 (必须重复的距离): " << min_matching_weight << endl;

        //计算最终最优路径长度
        long long shortest_route_length = total_edge_weight + min_matching_weight;

        cout << "--------------------------------------" << endl;
        cout << "最优中国邮递员路径总长度: " << shortest_route_length << endl;
        cout << "--------------------------------------" << endl;

        return shortest_route_length;
    }
};




int main() {
    
    //顶点数V= 9(编号 0 到 8)
    //奇度数点: 1,3,6,8(共 4 个)

    //初始化图
    ChinesePostman cpp(9);

    //添加边(u,v,weight)
    cpp.addEdge(0, 1, 4);
    cpp.addEdge(0, 7, 8);
    cpp.addEdge(1, 2, 8);
    cpp.addEdge(1, 7, 11);
    cpp.addEdge(2, 3, 7);
    cpp.addEdge(2, 8, 2);
    cpp.addEdge(2, 5, 4);
    cpp.addEdge(3, 4, 9);
    cpp.addEdge(3, 5, 14);
    cpp.addEdge(4, 5, 10);
    cpp.addEdge(5, 6, 2);
    cpp.addEdge(6, 7, 1);
    cpp.addEdge(6, 8, 6);
    cpp.addEdge(7, 8, 7);
    cpp.addEdge(3, 6, 3); //增加一条边

    cpp.solveCPP();

    return 0;
}