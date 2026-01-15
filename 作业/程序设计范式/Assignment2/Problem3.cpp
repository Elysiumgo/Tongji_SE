#include<iostream>
#include<vector>
#include <limits>

using namespace std;

void OutputChocos(const vector<int>& chocoBars) {

	int size = chocoBars.size();
	
	for (int i = 0; i < size; i++) {
		cout << chocoBars[i];
		if (i < size - 1)
			cout << ' ';
	}


}
vector<int> BreakChoco(const int length) {

	int current = 2; //将第一个值设为2，开始枚举

	vector<int> chocoBars;

	int leftLength = length;

	for (; ; current++) {
		if (current > leftLength) {
			break;
		}
		else {
			chocoBars.push_back(current);
			leftLength -= current;
		}
	}

	int i = chocoBars.size() - 1; //从最后开始加

	while (leftLength > 0) {
		chocoBars[i]++;

		leftLength--;
		i--;
		if (leftLength > 0 && i < 0)
			i = chocoBars.size()-1; //如果加完一轮还剩，则重置编号，重新从最后开始加一轮
			

	}

	return chocoBars;

}








int main() {


	
	int length;
	while (1) {
		cout << "Please input the length of chocolate bar(3 ≤ length ≤ 10000): ";
		cin >> length;

		if (length >= 3 && length <= 10000 && cin.good())
			break;
		else {
			cout << "Input error." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
	

	OutputChocos(BreakChoco(length));
	


}





