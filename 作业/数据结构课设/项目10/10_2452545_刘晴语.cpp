#include<iostream>
#include<cstring>
#include<ctime>
#include<vector>
#include<algorithm>
using namespace std;


class sorting {
private:
	int* numbers;
	long long sortingTime;
	int count;
	long long swapCount;
	long long compareCount;


	//1.冒泡排序
	void bubbleSort(int numbers[]) {

		clock_t startTime = clock(); //记录开始时间

		for (int i = 0; i < count; i++) {
			for (int j = i; j < count; j++) {
				if (numbers[j] < numbers[i]) {
					compareCount++;
					swap(numbers[i], numbers[j]);
					swapCount++;
				}
			}
		}

		clock_t endTime = clock();//记录结束时间
		sortingTime = endTime - startTime; //计算时间差

	}


	//2.选择排序
	void choosingSort(int numbers[]) {

		clock_t startTime = clock(); //记录开始时间
		for (int i = 0; i < count; i++) {
			int minIndex = i;
			for (int j = i+1; j < count; j++) {
				if (numbers[minIndex] > numbers[j]) {
					compareCount++;
					swapCount++;
					minIndex = j; //记录最小值位置
				}

			}
			compareCount++; //记录minIndex != i的compareCount
			if (minIndex != i) {
				swap(numbers[i], numbers[minIndex]);
				swapCount++;
			}
		}

		clock_t endTime = clock();//记录结束时间
		sortingTime = endTime - startTime; //计算时间差


	}


	//3.直接插入排序
	void insertSort(int numbers[]) {
		clock_t startTime = clock();
		swapCount = 0;
		compareCount = 0;

		for (int i = 1; i < count; i++) {
			int key = numbers[i];
			int j = i - 1;

			// 统计比较次数，每个元素最多比较i次
			while (j >= 0 && numbers[j] > key) {
				compareCount++;
				numbers[j + 1] = numbers[j];  // 元素后移
				swapCount++;  // 记录移动操作
				j--;
			}

			// 如果是因为j<0退出循环，还需要统计最后一次比较
			if (j >= 0) {
				compareCount++;  // 统计导致退出循环的那次比较
			}

			numbers[j + 1] = key;
		}

		clock_t endTime = clock();
		sortingTime = endTime - startTime;
	}


	//4.希尔排序
	void shellSort(int numbers[]) {
		clock_t startTime = clock(); //记录开始时间

		for (int gap = count / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < count; i++) {
				int temp = numbers[i];

				int j = i - gap;
				while (j >= 0) {

					compareCount++;  // 记录numbers[j] > temp比较次数
					if (numbers[j] > temp) {
						numbers[j + gap] = numbers[j];
						j -= gap;
						swapCount++;
					}
					else {
						break;
					}
				}

				numbers[j + gap] = temp;

			}

		}

		clock_t endTime = clock();//记录结束时间
		sortingTime = endTime - startTime; //计算时间差

	}


	//5.快速排序
	void quickSort(int numbers[], int low = 0, int high = -1) {

		if (high == -1) {
			clock_t startTime = clock(); //记录开始时间
			high = count - 1;

			quickSort(numbers, low, high); // 开始递归

			clock_t endTime = clock(); //记录结束时间
			sortingTime = endTime - startTime; //计算时间差
			return;
		}



		if (low < high) {

			// 选择基准（最右边元素）
			int pivot = numbers[high];
			int i = low - 1;  // 小于基准的区域的边界
			for (int j = low; j < high; j++) {
				compareCount++;
				if (numbers[j] <= pivot) {
					i++;
					// 交换元素
					if (i != j) {
						swap(numbers[i], numbers[j]);
						swapCount++;
					}
				}
			}

			// 将基准放到正确位置
			int pivotIndex = i + 1; 
			if (pivotIndex != high) {
				swap(numbers[pivotIndex], numbers[high]);
				swapCount++;
			}

			// 递归排序左右两部分
			quickSort(numbers, low, pivotIndex - 1);
			quickSort(numbers, pivotIndex + 1, high);
		}
	}


	//6. 堆排序
	void heapSort(int numbers[]) {

		clock_t startTime = clock(); //记录开始时间

		int n = count;
			

		//Lambda方式函数试用
		auto heapify = [&](int start, int end) {
			int current = start;
			//左孩子索引
			while (current * 2 + 1 < end) { 
				int child = current * 2 + 1; // 先假设左孩子是较大的
				compareCount++; 
				if (child + 1 < end && numbers[child + 1] > numbers[child]) {
					child++; // 如果右孩子存在且更大，选择右孩子
				}
				compareCount++;  
				if (numbers[child] > numbers[current]) {// 如果孩子比父亲大
					swap(numbers[current], numbers[child]);  // 继续调整被影响的子树
					swapCount++;  // 可以修改外部的swapCount
					current = child;
				}
				else {
					break; // 当前节点已经比孩子大了，调整结束
				}
			}
			};


		//构建初始大顶堆
		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(i, n);  
		}

		//排序，反复取最大值
		for (int i = n - 1; i > 0; i--) {
			swap(numbers[0], numbers[i]);// 把堆顶最大值放到末尾
			swapCount++;
			heapify(0, i);// 对剩余元素重新建堆
		}




		clock_t endTime = clock();//记录结束时间
		sortingTime = endTime - startTime; //计算时间差

	}

	
	//7. 归并排序
	void mergeSort(int numbers[]) {

		clock_t startTime = clock();

		// 内部递归函数
		//捕获外部所有变量；把自身作为参数传递
		auto mergeSortHelper = [&](auto&& self, int left, int right) -> void { 
			if (left < right) {
				int mid = left + (right - left) / 2;

				// 递归排序左右两半
				self(self, left, mid);
				self(self, mid + 1, right);

				// 合并过程
				vector<int> temp(right - left + 1);
				int i = left, j = mid + 1, k = 0;

				while (i <= mid && j <= right) {
					compareCount++;
					if (numbers[i] <= numbers[j]) {
						temp[k++] = numbers[i++];
					}
					else {
						temp[k++] = numbers[j++];
						swapCount++;
					}
				}

				while (i <= mid) temp[k++] = numbers[i++];
				while (j <= right) temp[k++] = numbers[j++];

				// 拷贝回原数组
				for (int idx = 0; idx < k; idx++) {
					numbers[left + idx] = temp[idx];
				}
			}
			};

		// 开始排序
		mergeSortHelper(mergeSortHelper, 0, count - 1);


		clock_t endTime = clock();//记录结束时间
		sortingTime = endTime - startTime; //计算时间差

	}



	//8.基数排序
	void RadixSort(int numbers[]) {
		clock_t startTime = clock(); //记录开始时间
		swapCount = 0;
		compareCount = 0;

		// 找到数组中的最大值，确定最大位数
		int maxNum = numbers[0];
		for (int i = 1; i < count; i++) {
			compareCount++; // 记录比较次数
			if (numbers[i] > maxNum) {
				maxNum = numbers[i];
			}
		}

		// 进行基数排序（从最低位到最高位）
		int exp = 1; // 从个位开始
		int* output = new int[count]; // 输出数组
		int* countArr = new int[10];  // 计数数组（0-9）

		while (maxNum / exp > 0) {
			// 初始化计数数组
			for (int i = 0; i < 10; i++) {
				countArr[i] = 0;
			}

			// 统计每个数字出现的次数
			for (int i = 0; i < count; i++) {
				int digit = (numbers[i] / exp) % 10;
				countArr[digit]++;
			}

			// 将计数转换为位置
			for (int i = 1; i < 10; i++) {
				countArr[i] += countArr[i - 1];
			}

			// 根据当前位数排序（从后往前保持稳定性）
			for (int i = count - 1; i >= 0; i--) {
				int digit = (numbers[i] / exp) % 10;
				output[countArr[digit] - 1] = numbers[i];
				countArr[digit]--;
				swapCount++; // 记录移动次数
			}

			// 将排序结果拷贝回原数组
			for (int i = 0; i < count; i++) {
				numbers[i] = output[i];
			}

			exp *= 10; // 处理下一位
		}

		// 释放内存
		delete[] output;
		delete[] countArr;

		clock_t endTime = clock(); //记录结束时间
		sortingTime = endTime - startTime; //计算时间差
	}
	


//随机生成数字
	void InputNumbers() {
		while (1) {
			cout << "请输入要产生的随机数的个数（100/1000/10000/100000）：";
			cin >> count;
			if (count == 100 || count == 1e3 || count == 1e4 || count == 1e5)
				break;
			else {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.clear();
			}
			
		}


		if (numbers != nullptr) {
			delete[] numbers;  // 释放之前的内存
		}


		numbers = new int[count];
		srand(static_cast<unsigned int>(time(0)));  // 设置随机种子
		for (int i = 0; i < count; i++) {
			numbers[i] = rand() % 1000;
		}

		
		

	
	}

	
	void OutputResults(const char method[] ) {
		
		cout << method << "排序所用时间：" << sortingTime << "ms" << endl;
		cout << method << "排序交换次数：" << swapCount << endl;
		cout << method << "排序比较次数：" << compareCount << endl;
		cout << "------------------------" << endl;

	}




public:

	sorting() : numbers(nullptr), sortingTime(0), count(0), swapCount(0), compareCount(0) {}  // 构造函数初始化

	~sorting() {  // 析构函数释放内存
		if (numbers != nullptr) {
			delete[] numbers;
		}
	}


	void menu() {
		cout << "**                  排序算法比较                  **" << endl
			<< "====================================================" << endl
			<< "**                  1 --- 冒泡排序                **" << endl
			<< "**                  2 --- 选择排序                **" << endl
			<< "**                  3 --- 直接插入排序            **" << endl
			<< "**                  4 --- 希尔排序                **" << endl
			<< "**                  5 --- 快速排序                **" << endl
			<< "**                  6 --- 堆排序                  **" << endl
			<< "**                  7 --- 归并排序                **" << endl
			<< "**                  8 --- 基数排序                **" << endl
			<< "**                  9 --- 退出排序                **" << endl
			<< "====================================================" << endl << endl;

		InputNumbers();
		//生成随机数


		while (1) {

			cout << "\n请选择排序算法：  ";
			int choice;
			cin >> choice;


			int* numbersCopy = new int[count];

			for (int i = 0; i < count; i++) {
				numbersCopy[i] = numbers[i];
			}
			//为了方便用同一组随机数进行比较，拷贝一份副本

			const char* method="";
			swapCount = 0;
			compareCount = 0;
			sortingTime = 0;

			if (choice == 9)
				break;
			else if (choice == 1) {
				method = "冒泡";
				bubbleSort(numbersCopy);
			}
			else if (choice == 2) {
				method = "选择";
				choosingSort(numbersCopy);
			}
			else if (choice == 3){
				method="直接插入";
				insertSort(numbersCopy);
			}
			else if (choice == 4) {
				method = "希尔排序";
				shellSort(numbersCopy);
			}
			else if (choice == 5) {
				method = "快速";
				quickSort(numbersCopy);
			}
			else if (choice == 6) {
				method = "堆";
				heapSort(numbersCopy);
			}
			else if (choice == 7) {
				method = "归并";
				mergeSort(numbersCopy);
			}
			else if (choice == 8) {
				method = "基数";
				RadixSort(numbersCopy);
			}


			OutputResults(method);
			delete[] numbersCopy;
			
		}

	}
	



};




int main() {

	sorting mysort;
	mysort.menu();

	return 0;


}