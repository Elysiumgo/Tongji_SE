#include<iostream>
#include <vector>
#include <unordered_map>
#include<limits>
#include<string>
#include<sstream>
using namespace std;

class SubArrayCheck {
private:
	vector<int> nums;
	size_t length;


//输入原数组、子数组长度
	void inputNums() {
		do {
			cout << "请输入整数数组（以空格分隔，回车结束）：";
			string line;
			getline(cin, line);          // 读取整行输入

			stringstream ss(line);        // 将字符串转换为字符串流
			int num;
			while (ss >> num) {           // 从流中逐个读取整数
				nums.push_back(num);      // 添加到数组
			}

			if (nums.empty()) {
				cout << "无整数，输入错误，请重新输入" << endl;
			}
				
		} while (nums.empty());
		


		while (1) {
			cout << "请输入子数组长度（原数组长度为" << nums.size() << "）：";
			if (cin >> length && length <= (nums.size()) && length > 0)
				break;
			else if (length > nums.size()) //子数组长度必须小于原数组
				cout << "子数组长度错误，请重新输入" << endl;
			else {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}


	}

	bool checkSubArray() {
		
		if (length <= 1)
			return false;

		unordered_map<int, int> count;

		//先初始化第一个窗口，每次只修改第一个和最后一个元素的计数
		// 这样就不用循环套循环，不用每次都从头遍历一遍

		for (size_t i = 0; i < length && i < nums.size(); i++) {
			count[nums[i]]++;
			if (count[nums[i]] >= 2) 
				return true;
		}

		for (size_t i = 1; i <= (nums.size()-length); i++) {
			count[nums[i - 1]]--;
			if (count[nums[i - 1]] == 0) {
				count.erase(nums[i - 1]);
			}
			//去掉前一个元素


			count[nums[i + length-1]]++;
			if (count[nums[i + length - 1]] == 2)
				return true;
		}
			//加上最后一个元素

		return false;

	}


public:

	bool check() {
		inputNums();

		return checkSubArray();
	}

};





int main() {

	SubArrayCheck myCheck;
	bool exist = myCheck.check();

	cout << (exist ? "true" : "false");
	return 0;

}