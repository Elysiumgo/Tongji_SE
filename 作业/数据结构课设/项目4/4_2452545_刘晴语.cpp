#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SIZE = 200;

class NumStack {
    double data[MAX_SIZE];
    int topIdx;
public:
    NumStack() : topIdx(-1) {}
    void push(double val) {
        if (topIdx < MAX_SIZE - 1) data[++topIdx] = val;
        else cout << "数字栈溢出" << endl;
    }
    double pop() { 
        if (topIdx >= 0) 
            return data[topIdx--];
        return 0; 
    }
    double top() { return (topIdx >= 0) ? data[topIdx] : 0; }
    bool empty() { return topIdx == -1; }
    int size() { return topIdx + 1; }
};

class OpStack {
    char data[MAX_SIZE];
    int topIdx;
public:
    OpStack() : topIdx(-1) {}
    void push(char val) {
        if (topIdx < MAX_SIZE - 1) data[++topIdx] = val;
    }
    char pop() {
        if (topIdx >= 0) return data[topIdx--];
        return 0;
    }
    char top() { return (topIdx >= 0) ? data[topIdx] : 0; }
    bool empty() { return topIdx == -1; }
};

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return (b == 0) ? 0 : a / b;
    case '%': return ((int)b == 0) ? 0 : (int)a % (int)b;
    case '^': return pow(a, b);
    default: return 0;
    }
}

//计算逻辑
double solveExpression(char* exp) {
    NumStack nums;
    OpStack ops;

    for (int i = 0; exp[i] != '\0' && exp[i] != '='; i++) {
        if (exp[i] == ' ') continue;

        //处理数字，边界保护
        if (isdigit(exp[i])) {
            double val = 0;
            double frac = 0.1;
            bool isDecimal = false;
            while (exp[i] != '\0' && (isdigit(exp[i]) || exp[i] == '.')) {
                if (exp[i] == '.') isDecimal = true;
                else {
                    if (!isDecimal) val = val * 10 + (exp[i] - '0');
                    else {
                        val += (exp[i] - '0') * frac;
                        frac /= 10;
                    }
                }
                i++;
            }
            nums.push(val);
            i--;
        }
        else if (exp[i] == '(') {
            ops.push('(');
        }
        else if (exp[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                if (nums.size() < 2) 
                    break; //避免非法表达式导致空栈弹出
                double v2 = nums.pop();
                double v1 = nums.pop();
                nums.push(applyOp(v1, v2, ops.pop()));
            }
            ops.pop(); // 弹出 '('
        }
        else {
            //处理运算符及单目符号
            if ((exp[i] == '-' || exp[i] == '+') && (i == 0 || exp[i - 1] == '(')) {
                nums.push(0);
            }
            while (!ops.empty() && ops.top() != '(' && getPriority(ops.top()) >= getPriority(exp[i])) {
                if (nums.size() < 2) break;
                double v2 = nums.pop();
                double v1 = nums.pop();
                nums.push(applyOp(v1, v2, ops.pop()));
            }
            ops.push(exp[i]);
        }
    }

    while (!ops.empty()) {
        if (nums.size() < 2) break;
        double v2 = nums.pop();
        double v1 = nums.pop();
        nums.push(applyOp(v1, v2, ops.pop()));
    }
    return nums.top();
}

int main() {
    char exp[MAX_SIZE];
    char choice;
    do {
        cout << "输入表达式：" << endl;
        cin >> exp;

        bool illegal = false;
        int bc = 0;
        for (int i = 0; exp[i] != '\0'; i++) {
            if (exp[i] == '(') bc++;
            if (exp[i] == ')') bc--;
            //非法字符检测
            if (!isdigit(exp[i]) && exp[i] != '.' && exp[i] != '+' && exp[i] != '-' &&
                exp[i] != '*' && exp[i] != '/' && exp[i] != '%' && exp[i] != '^' &&
                exp[i] != '(' && exp[i] != ')' && exp[i] != '=') {
                illegal = true;
            }
        }

        if (bc != 0 || illegal) {
            cout << "表达式格式不正确或包含非法字符" << endl;
        }
        else {
            cout << solveExpression(exp) << endl;
        }

        cout << "是否继续（y，n）？";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    return 0;
}