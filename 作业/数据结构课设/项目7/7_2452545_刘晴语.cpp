#include<iostream>
#include<limits>
#include <algorithm>
using namespace std;


typedef long long CostType;

class WoodCut {

private:
	int pieceNum;
	long long* pieces;
	int heapSize;//堆中当前元素数量

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }



	//确保最小堆性质
	void minHeapify(int i) {

		int l = left(i);
		int r = right(i);
		int smallest = i;

		//找到i，左子节点和右子节点中最小的那个
		if (l < heapSize && pieces[l] < pieces[i]) {
			smallest = l;
		}
		if (r < heapSize && pieces[r] < pieces[smallest]) {
			smallest = r;
		}

		//如果最小的不是i,则交换并递归调用
		if (smallest != i) {
			swap(pieces[i], pieces[smallest]);
			minHeapify(smallest);
		}



	}



	//向上调整，用于插入操作后
	void decreaseKey(int i) {
		//i是新插入元素的位置
		while (i > 0 && pieces[parent(i)] > pieces[i]) {
			//如果父节点大于当前节点，则交换
			swap(pieces[i], pieces[parent(i)]);
			//动到父节点位置，继续向上检查
			i = parent(i);
		}
	}


	//把合并后的数调整到堆里
	void insert(CostType key) {
		//确保数组有足够的空间
		if (heapSize >= pieceNum) {
			return;
		}

		//插入到数组末尾
		pieces[heapSize] = key;
		heapSize++;

		//向上调整
		decreaseKey(heapSize - 1);
	}


	//提取堆顶最小值
	CostType extractMin() {

		if (heapSize <= 0) {
			return 0;
		}

		//处理堆中只剩一个元素的情况
		if (heapSize == 1) {
			heapSize--;
			return pieces[0];
		}

		//堆顶即为最小值
		CostType min = pieces[0];

		//将最后一个元素移到堆顶
		pieces[0] = pieces[heapSize - 1];
		heapSize--;

		//向下调整
		minHeapify(0);

		return min;
	}





public:


	WoodCut() : pieceNum(0), pieces(nullptr), heapSize(0) {}

	//析构函数
	~WoodCut() {
		delete[] pieces;
	}


	void input(){


		//输入总块数
		while (1) {
			cout << "请输入需要的木头块数：";
			cin >> pieceNum;
			if (cin.good() && pieceNum <= 1e4)
				break;
			else {
				cout << "输入错误，请重试" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}

		}

		pieces = new long long[pieceNum];

		//输入每块长度
		
		cout << "请输入" << pieceNum << "个整数作为每块木头的长度：";

		for (int i = 0;i<pieceNum ; i++) {
			int tmp;
			cin >> tmp;
			if (cin.good())
				pieces[i] = tmp;
			else {
				cout << "输入错误，请从第" << i + 1 << "个整数开始重新输入" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				i--;
			}

		}	

		heapSize = pieceNum;

		


	}


	CostType solve() {

		if (pieces == nullptr || pieceNum == 0) {
			return 0;
		}

		//将输入数组建立成一个最小堆
		//从最后一个非叶子节点开始向上调用 minHeapify 
		for (int i = heapSize / 2 - 1; i >= 0; --i) {
			minHeapify(i);
		}

		CostType totalCost = 0;

		//只要堆中元素的数量大于1，就继续
		while (heapSize > 1) {
			//取出最短的两个
			CostType L1 = extractMin(); 
			CostType L2 = extractMin(); 

			CostType currentCost = L1 + L2;
			totalCost += currentCost;

			//将新的木头长度放回堆中
			insert(currentCost); 
		}
		return totalCost;
	}

};




int main() {

	WoodCut MyWood;
	MyWood.input();
	CostType result = MyWood.solve();

	cout << result << endl;

	return 0;

}