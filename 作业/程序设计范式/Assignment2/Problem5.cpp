#include<iostream>
#include<string>
#include<cctype>
#include<limits>
#include<vector>
using namespace std;

class GetPassword {
private:
	string a, b;

	bool CheckInput(const string& str) { //检查输入的是不是都是数字
		if (str.empty())
			return false;
		
		for (char c : str) {
			if (!isdigit(c))
				return false;
		}
		return true;
	}

	void Input() {
		while (1) {
			cout << "Enter two numbers:";
			cin >> a >> b;
			if (CheckInput(a) && CheckInput(b))
				break;
			else {
				cout << "Invalid input. Please try again. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}
	}

	string multiplyStrings(const string& num1, const string& num2) {
		if (num1 == "0" || num2 == "0")
			return "0";
		
		int len1 = num1.size();
		int len2 = num2.size();

		vector<int> result(len1 + len2, 0);

		for (int i = len1 - 1; i >= 0; i--) { 
			for (int j = len2 - 1; j >= 0; j--) { //两个都从最后一位开始相乘
				int current = (num1[i] - '0') * (num2[j] - '0'); //先乘
				int sum = current + result[i + j + 1]; //再加已有的进位

				result[i + j + 1] = sum % 10;      // 当前位
				result[i + j] += sum / 10;         // 往前进位



			}
		}

		//再转换成字符串

		string finalResult = "";
		for (int num : result) {
			// 跳过开头的0
			if (!(finalResult.empty() && num == 0)) {
				finalResult += to_string(num);
			}
		}

		
		if (finalResult.empty()) { 
			return "0";
		}

		return finalResult;



	}







public:
	void GetResult() {
		Input();
		cout << multiplyStrings(a, b);
	}


};












int main() {

	GetPassword password;
	password.GetResult();

}


