#include<iostream>
#include<string>
#include <limits> 
#include <cctype> 
using namespace std;

class NumberMirror {
private:
    int p, m;
    string k;

    // 将字符转换为数值
    int CharToValue(char c) const {
        if (isdigit(c))
            return c - '0';
        return c - 'A' + 10;
    }

    // 将数值转换为字符
    char ValueToChar(int val) const {
        if (val < 10)
            return '0' + val;
        return 'A' + (val - 10);
    }

    //输入并进行错误处理
    void InputIndex() {
        bool correctCheck = true;
        while(1){
            correctCheck = true;
            cout << "Enter p(original base),m(final base),k(number in base-p): ";
            if (!(cin >> p >> m >> k)) {
                cout << "Invalid input format!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                correctCheck = false;
            }

            // 同时检查p和m范围
            if (p < 2 || p > 20 || m < 2 || m > 20) {
                cout << "Error: p and m must be between 2 and 20" << endl;
                correctCheck = false;
            }

            // 检查k是否合法（不能超过p，也不能超过J）
            for (char c : k) {
                int value;
                if (isdigit(c)) {
                    value = c - '0';
                }
                else if (isupper(c) && c >= 'A' && c <= 'J') {
                    value = c - 'A' + 10;
                }
                else {
                    cout << "Error: Invalid character '" << c << "' in k" << endl;
                    correctCheck = false;
                    continue; //直接跳过不检查后续了
                }

                // 检查数字是否小于p
                if (value >= p) { 
                //我不是很懂这里怎么写比较好，这里VS有智能提示说使用未初始化内存
                // 但我觉得给变量随便赋一个值更不合适了
                    cout << "Error: Digit '" << c << "' (value=" << value
                        << ") is not valid in base-" << p << endl;
                    correctCheck = false;
                }
            }
            if (correctCheck) //各项检查都通过则退出，否则重新输入
                break;
            else
                cout << "\nPlease try again." << endl;
        }

    }




    //将原值转换为十进制
    long long PToDecimal(const string& str, int base) const {
        long long result = 0;
        for (char c : str) { //逐一对str的每个字符进行操作
            result = result * base + CharToValue(c);
        }
        return result;
    }

    //将十进制转换为m_base
    string DecimalToM(long long decimal, int base) {
        if (decimal == 0) 
            return "0"; //总之先处理边界情况

        string result;
        long long num = decimal;
        while (num > 0) {
            result+= ValueToChar(num % base); //用字符串从后面加，不需要再反转了
            num /= base; //模拟长除法


        }

        return result;


    }


    void OutputWithoutZero(string& result) {

        if (result == "0") { //先处理本身就是0的情况
            cout << result;
            return;
        }
            

        bool skip = true; //输出时是否跳过零
        for (char c : result) {
            if (c != '0')
                skip = false;
            if (!skip)
                cout << c;
        }




    }


public:
    
    void mirror() {
       
        InputIndex();

        long long decimalIndex = PToDecimal(k, p);
        string result = DecimalToM(decimalIndex, m);

        OutputWithoutZero(result);





    }
    



};











int main() {

    NumberMirror mirror;
    mirror.mirror();


    return 0;

}






