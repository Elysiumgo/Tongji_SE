#include<iostream>
#include<string>
using namespace std;

void modify1(string* str)
{
	if (str != nullptr) {
		*str = "*" + *str + "*";  // 在字符串前后加星号
	}
}


void modify2(string& str)
{
	str = "[" + str + "]";

}





int main()
{
	
	
    string myString = "Hello";

    // 打印原始字符串
    cout << "Original string: " << myString << endl;

    // 传递指针给第一个函数
    modify1(&myString);
    cout << "After pointer function: " << myString << endl;

    // 传递引用给第二个函数
    modify2(myString);
    cout << "After reference function: " << myString << endl;

    return 0;



}