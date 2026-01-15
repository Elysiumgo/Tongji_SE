#include<iostream>
#include <vector>
#include <unordered_map>
#include<limits>
#include<string>
#include<sstream>
using namespace std;

class findSubArray {
private:
	vector<int> nums;
	size_t length;
	int appearTime;

	//输入原数组、子数组长度、出现次数
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
			if (cin >> length && length <= static_cast<int>(nums.size()) && length >=2)
				break;
			else if (length > nums.size()) //子数组长度必须小于原数组
				cout << "子数组长度错误，请重新输入" << endl;
			else {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}

		while (1) {
			cout << "请输入出现次数：";
			if (cin >> appearTime && appearTime <= length&&appearTime>=2) 
				break;
			else {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}

	}


	bool findCount() {
		
		unordered_map<int, int> count;
		//先初始化窗口
		//只需要检查固定长度length的滑动窗口即可 
		// 只要length里有那就一定有一个子数组也包含所需答案
		for (int i = 0; i < length; i++) {
			count[nums[i]]++;
			if (count[nums[i]]>= appearTime)
				return true;
		}

		for (size_t i = length; i < nums.size(); i++) {
			count[nums[i - length]]--;
			count[nums[i]]++;

			if (count[nums[i]]>= appearTime)
				return true;

		}
		return false;

	}

public:
	bool Find() {
		inputNums();
		return findCount();
	}
};


int main() {

	findSubArray MyFind;
	bool exist = MyFind.Find();
	cout << (exist ? "true" : "false");

	return 0;

}