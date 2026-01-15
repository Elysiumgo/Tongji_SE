#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

void output(int s[][MAX_SIZE], int n, int d);
void zifan(int s2[][MAX_SIZE], int n, int d);
void duichen(int s2[][MAX_SIZE], int n, int d);
void chuandi(int s2[][MAX_SIZE], int n, int d);
void select();

int s[MAX_SIZE][MAX_SIZE];
int n, d, i, j, z;

int main(){
    select();
    return 0;
}

void select(){
    cout << "请输入矩阵的行数:";
    cin >> n;
    cout << "请输入矩阵的列数:";
    cin >> d;
    cout << "请输入关系矩阵:" << endl;

    for (i = 0; i < n; i++){
        cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
        for (j = 0; j < d; j++) {
             int temp;
             cin >> temp;
             if (cin.good() && (temp == 1 || temp == 0))
                 s[i][j] = temp;
             else {
                 cin.clear();
                 cin.ignore(1024, '\n');
                 cout << "输入错误，请从错误处重新输入";
             }

        }
        cin.ignore(1024, '\n');
        
    }

    do {
        cout << "输入对应序号选择算法" << endl;
        cout << "1:自反闭包" << endl;
        cout << "2:传递闭包" << endl;
        cout << "3:对称闭包" << endl;
        cout << "4:退出" << endl;
        cin >> z;

        switch (z)
        {
        case 1: zifan(s, n, d); break;
        case 2: chuandi(s, n, d); break;
        case 3: duichen(s, n, d); break;
        case 4: return;
        default: cout << "无效选择，请重新输入" << endl;
        }
    } while (z != 4);
}

void output(int s[][MAX_SIZE], int n, int d)
{
    cout << "所求关系矩阵为:" << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < d; j++)
            cout << s[i][j] << " ";
        cout << endl;
    }
}

void zifan(int s2[][MAX_SIZE], int n, int d){
    // 自反闭包：主对角线元素设为1
    int temp[MAX_SIZE][MAX_SIZE];

    // 复制原矩阵
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
            temp[i][j] = s2[i][j];

    // 设置主对角线为1
    for (i = 0; i < n && i < d; i++)
        temp[i][i] = 1;

    output(temp, n, d);
}

void duichen(int s2[][MAX_SIZE], int n, int d){
    // 对称闭包：R ∪ R^(-1)
    int temp[MAX_SIZE][MAX_SIZE];
    int s1[MAX_SIZE][MAX_SIZE];

    // 计算转置矩阵
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
            s1[j][i] = s2[i][j];

    // 计算并集（逻辑或）
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
            temp[i][j] = s2[i][j] || s1[i][j];

    output(temp, n, d);
}

void chuandi(int s2[][MAX_SIZE], int n, int d){
    // 传递闭包：使用Warshall算法
    int temp[MAX_SIZE][MAX_SIZE];

    // 复制原矩阵
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
            temp[i][j] = s2[i][j];

    // Warshall算法
    for (int k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < d; j++)
                temp[i][j] = temp[i][j] || (temp[i][k] && temp[k][j]);

    output(temp, n, d);
}