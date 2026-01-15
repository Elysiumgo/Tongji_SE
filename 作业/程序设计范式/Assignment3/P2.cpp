#include<iostream>
#include<cmath>
#include<limits>
#include<vector>
#include<string>
#include<sstream>
#include<unordered_map>
using namespace std;

class CheckAbs {

private:
	vector<int> nums;
	size_t length;
	long long difference;

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
			cout << "请输入绝对值：";
			if (cin >> difference && difference >= 0) //绝对值大于0
				break;
			else {
				cout << "输入错误，请重新输入（绝对值大于0）" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}

		while (1) {
			cout << "请输入查找范围：";
			if (cin >> length && length <= nums.size() && length > 0)
				break;
			else {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}

	}


	bool checkDifference() {

		unordered_map<long long, int> buckets;
		long long bucket_size = difference + 1; //创建桶的大小

		for (size_t i = 0; i < nums.size(); i++) {
			// 当i>length时，移除最早的元素
			if (i > length) {
				long long removeNum = nums[i - length - 1];
				long long oldBucket = (removeNum - INT_MIN) / bucket_size; //负数要用偏移量特殊处理
				buckets.erase(oldBucket); 
			}

			//先取出一个元素
			long long currentNum = nums[i];

			//然后计算它应该在的桶编号，使用偏移量处理负数
			long long bucketNum = ((long long)currentNum - INT_MIN) / bucket_size;
			

			if (buckets.count(bucketNum) || //如果一个桶里有两个元素，则必然存在
				(buckets.count(bucketNum - 1) && abs(currentNum - buckets[bucketNum - 1]) <= difference) ||
				(buckets.count(bucketNum + 1) && abs(currentNum - buckets[bucketNum + 1]) <= difference) ){
				//也有可能跨桶存在，但只可能在相邻桶
				return true;
			}

			//如果没有找到就加进去
			buckets[bucketNum] = currentNum;
		}

	return false;

	}



public:

	bool check() {
		inputNums();
		return checkDifference();

	}

};



int main() {

	CheckAbs MyCheck;
	bool exist = MyCheck.check();
	cout << (exist ? "true" : "false");

	return 0;

}