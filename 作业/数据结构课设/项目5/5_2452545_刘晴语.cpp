#include<iostream>
#include<limits>
using namespace std;




int main() {
	int N;

	while (1) {
		cout << "请输入顾客人数以及编号（以空格隔开）：";
		cin >> N;
		if (cin.fail()) {
			cout << "输入错误，请重新输入";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else 
			break;

	}
	
	int* customers = new int[N];

	while (1) {
		bool inputValid = true;

		for (int i = 0; i < N; i++) {
			int tmp;
			cin >> tmp;
			if (cin.fail()) {
				cout << "输入错误，请重新输入";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inputValid = false;
				break;
			}
			else
				customers[i] = tmp;
		}

		if (!inputValid) continue;

		// 检查是否有重复
		bool hasDuplicate = false;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				if (customers[i] == customers[j]) {
					hasDuplicate = true;
					break;
				}
			}
			if (hasDuplicate)
				break;
		}

		// 如果有重复，提示并重新输入
		if (hasDuplicate) {
			cout << "存在重复编号，请重新输入所有编号: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}
		else
			break;
	}


	int oddCount = 0, evenCount = 0;
	int* odd = new int[N];
	int* even = new int[N];

	for (int i = 0; i < N; i++) {

		if (customers[i] % 2 == 1) 
			odd[oddCount++] = customers[i];
		else
			even[evenCount++] = customers[i];

	}
	//count是数量，不是编号


	int i = 0, j = 0, first = 1;
	bool second = 0;
	
	while (i<oddCount||j<evenCount) {
		
		if (i < oddCount) {
			if (!first) 
				cout << " ";
			cout << odd[i++];
			first = 0;
		}
		if (i < oddCount) {
			if (!first)
				cout << " ";
			cout << odd[i++];
		}
		if (j < evenCount) {
			if (!first)
				cout << " ";
			cout << even[j++];
		}



	}


	delete[] customers;
	delete[] odd;
	delete[] even;

	return 0;

}
