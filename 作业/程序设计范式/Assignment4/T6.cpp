#include<iostream>
#include<string>
#include<cmath>
#include <functional>
using namespace std;



struct Point {

	int x, y;

	double distance()const {
		return sqrt(x * x + y * y);
	}

    // 重载输出流操作符，用于打印Point
    friend ostream& operator<<(ostream& os, const Point& p) {
        os <<"( "<< p.x << "," << p.y<<" )" ;
        return os;
    }

};


struct StringCompare {

	bool operator()(const string& a, const string& b) {
		return a.length() < b.length();
	}

};


struct PointCompare {

	bool operator()(const Point a, const Point b) {
		return a.distance() < b.distance();
	}

};


struct PointPtrCompare {
	bool operator()(const Point* a, const Point* b) {
		return PointCompare()(*a, *b); //立即创建一个PointCompare变量并且调用默认函数
	}
};



template<typename T,typename Comp=less<T>>
const T& findMin(const T& a, const T& b, const T& c, Comp comp = Comp()) { //创建函数类型，默认为正常<比较

	const T* min = &a;

	if (!comp(*min, b)) {
		min = &b;
	}

	if (!comp(*min, c)) {
		min = &c;
	}

	return *min;

}


int main() {
    cout << "--- 1. int (默认比较) ---\n";
    cout << "Input: 1 2 3 -> Output: " << findMin(1, 2, 3) << endl;

    cout << "\n--- 2. double (默认比较) ---\n";
    cout << "Input: 1.3 2.4 0.6 -> Output: " << findMin(1.3, 2.4, 0.6) << endl;

    cout << "\n--- 4. string (按长度比较) ---\n";
    string s1 = "hello", s2 = "hi", s3 = "he"; // 长度: 5, 2, 2
    cout << "Input: " << s1 << " " << s2 << " " << s3 << endl;
    cout << "Output: " << findMin(s1, s2, s3, StringCompare()) << endl; 

    cout << "\n--- 5. Point 结构体 (按距离比较) ---\n";
    Point pA = { 1, 2 };
    Point pB = { 3, 4 };
    Point pC = { 0, 1 };
    cout << "Input: " << pA << " " << pB << " " << pC << endl;
    cout << "Output: " << findMin(pA, pB, pC, PointCompare()) << endl; 

    cout << "\n--- 6. Point* 指针 (解引用后按距离比较) ---\n";
    Point p4 = { 1, 2 }; Point p5 = { 0, 1 }; Point p6 = { 3, 4 };
    Point* pp4 = &p4;
    Point* pp5 = &p5;
    Point* pp6 = &p6;
    cout << "Input: " << p4 << " " << p5 << " " << p6 << endl;
    cout << "Output (via ptr): " << *findMin(pp4, pp5, pp6, PointPtrCompare()) << endl; 

    return 0;
}


