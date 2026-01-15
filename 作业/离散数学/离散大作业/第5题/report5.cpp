#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TreeNode {
    int freq;           // 频率值
    TreeNode* left;     // 左子树
    TreeNode* right;    // 右子树
    TreeNode(int f) : freq(f), left(nullptr), right(nullptr) {}
};

// 比较函数，用于优先队列（最小堆）
struct Compare {
    bool operator()(TreeNode* a, TreeNode* b) {
        return a->freq > b->freq;  // 小顶堆
    }
};

// 构建哈夫曼树（使用优先队列）
TreeNode* buildHuffmanTree(vector<int>& frequencies) {
    // 创建最小堆优先队列
    priority_queue<TreeNode*, vector<TreeNode*>, Compare> minHeap;

    // 创建叶子结点并加入堆
    for (int f : frequencies) {
        minHeap.push(new TreeNode(f));
    }

    // 循环合并直到只剩一个结点
    while (minHeap.size() > 1) {
        // 取出两个频率最小的结点
        TreeNode* left = minHeap.top();
        minHeap.pop();
        TreeNode* right = minHeap.top();
        minHeap.pop();

        // 创建新结点
        TreeNode* parent = new TreeNode(left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // 将新结点加入堆
        minHeap.push(parent);
    }

    return minHeap.top();  // 返回根结点
}

// 生成前缀码（哈夫曼编码）
void generatePrefixCodes(TreeNode* root, string code, vector<pair<int, string>>& codes) {
    if (!root) return;

    // 如果是叶子结点，保存编码
    if (!root->left && !root->right) {
        codes.push_back({ root->freq, code });
        return;
    }

    // 左子树编码加 '0'
    generatePrefixCodes(root->left, code + "0", codes);
    // 右子树编码加 '1'
    generatePrefixCodes(root->right, code + "1", codes);
}

// 释放二叉树内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int n;
    cout << "请输入通信符号个数: ";
    cin >> n;

    vector<int> frequencies(n);
    cout << "请输入各符号的使用频率: ";
    for (int i = 0; i < n; i++) {
        cin >> frequencies[i];
    }

    // 构建哈夫曼树
    TreeNode* root = buildHuffmanTree(frequencies);

    // 生成前缀码
    vector<pair<int, string>> huffmanCodes;
    generatePrefixCodes(root, "", huffmanCodes);

    // 输出结果
    cout << "\n各通信符号的前缀码:" << endl;
    for (auto& code : huffmanCodes) {
        cout << "频率 " << code.first << ": " << code.second << endl;
    }

    // 计算平均编码长度
    double totalFreq = 0;
    double weightedLength = 0;
    for (auto& code : huffmanCodes) {
        totalFreq += code.first;
        weightedLength += code.first * code.second.length();
    }
    cout << "\n平均编码长度: " << weightedLength / totalFreq << endl;

    // 释放内存
    deleteTree(root);

    return 0;
}