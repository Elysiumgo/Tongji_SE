#include<iostream>
#include<chrono>

using namespace std;
using namespace std::chrono;


//基类
class BaseProcessor {

public:
	virtual void process() {
		int result = 0;
		for (int i = 0; i < 1000; i++) {
			result += i;
		}
	}

	// 非虚函数（隐藏）
	void compute() {
		int result = 0;
		for (int i = 0; i < 1000; i++) {
			result += i;
		}
	}

};



class AdvancedProcessor :public BaseProcessor {

public:
	void process() override {
		int result = 0;
		for (int i = 0; i < 1000; i++) {
			result += i;
		}
	}

	void compute() {
		int result = 0;
		for (int i = 0; i < 1000; i++) {
			result += i;
		}
	}

};


int main() {

    //创建子类对象，向上转换为基类指针
    AdvancedProcessor advancedObj;
    BaseProcessor* basePtr = &advancedObj;  

    const int NUM_CALLS = 100000;  // 调用次数

    //测量虚函数调用时间
    auto start1 = high_resolution_clock::now();
    for (int i = 0; i < NUM_CALLS; i++) {
        basePtr->process();  // 虚函数调用
    }
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(end1 - start1);

    //测量非虚函数调用时间  
    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < NUM_CALLS; i++) {
        basePtr->compute();  // 非虚函数调用
    }
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(end2 - start2);

    //比较并打印结果
    cout << "虚函数 process() 调用 " << NUM_CALLS << " 次耗时: "
        << duration1.count() << " 微秒" << endl;
    cout << "非虚函数 compute() 调用 " << NUM_CALLS << " 次耗时: "
        << duration2.count() << " 微秒" << endl;

    long long difference = duration1.count() - duration2.count();
    cout << "时间差: " << difference << " 微秒" << endl;
    cout << "虚函数比非虚函数慢: " << (difference * 100.0 / duration2.count()) << "%" << endl;

    return 0;



}










