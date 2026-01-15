#include <iostream>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

struct Pos {
    int x, y;
};

//栈
struct Stack {
    Pos data[ROWS * COLS];
    int top;

    Stack() { top = -1; }
    void push(Pos p) { data[++top] = p; }
    void pop() { if (top >= 0) top--; }
    Pos peek() { return data[top]; }
    bool isEmpty() { return top == -1; }
};

//迷宫地图，1是墙，0是路
int maze[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

//专门用来记录哪些路走过
bool visited[ROWS][COLS] = { false };

//打印函数
void printMazeWithStack(Stack& s) {
    // 临时创建一个用于显示的地图，先把原迷宫复制进去
    char display[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 1) 
                display[i][j] = '#'; //墙
            else 
                display[i][j] = ' ';                //路
        }
    }

    //只将栈里的坐标点（最终路径）标记为 '*'
    for (int k = 0; k <= s.top; k++) {
        display[s.data[k].x][s.data[k].y] = '*';
    }

    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << display[i][j] << "  ";
        }
        cout << endl;
    }
}

//回溯搜索
bool solve(int startX, int startY, int endX, int endY, Stack& s) {
    Pos start = { startX, startY };
    s.push(start);
    visited[startX][startY] = true;

    int dx[] = { -1, 1, 0, 0 }; //上下左右
    int dy[] = { 0, 0, -1, 1 };

    while (!s.isEmpty()) {
        Pos curr = s.peek();

        //检查是否到达出口
        if (curr.x == endX && curr.y == endY) 
            return true;

        bool found = false;
        for (int i = 0; i < 4; i++) {
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];

            //不越界、不是墙、没走过
            if (nextX >= 0 && nextX < ROWS && nextY >= 0 && nextY < COLS &&
                maze[nextX][nextY] == 0 && !visited[nextX][nextY]) {

                visited[nextX][nextY] = true; //标记已访问
                s.push({ nextX, nextY });       //入栈
                found = true;
                break; //深度优先进入
            }
        }

        if (!found) {
            s.pop(); //四周不通，出栈
        }
    }
    return false;
}

int main() {
    Stack s;
    int stX = 1, stY = 1; //入口
    int edX = 8, edY = 2; //出口


    if (solve(stX, stY, edX, edY, s)) {
        cout << "成功找到路线" << endl;

        cout << "坐标路线: ";
        for (int i = 0; i <= s.top; i++) {
            cout << "(" << s.data[i].x << "," << s.data[i].y << ")";
            if (i < s.top) 
                cout << " -> ";
        }
        cout << endl;

        //打印地图
        printMazeWithStack(s);
    }
    else {
        cout << "寻找失败" << endl;
    }

    return 0;
}