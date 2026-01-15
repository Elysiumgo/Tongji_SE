#include <iostream>
#include <string>
using namespace std;


struct MyStruct {
    string first;
    string second;
    int number;
};


typedef MyStruct MyStructType;

int main() {
    
    MyStructType instance;
    instance.first = "Hello";
    instance.second = "World";
    instance.number = 100;

    
    cout << "Initial values:" << endl;

    cout << "first: " << instance.first << endl;
    cout << "second: " << instance.second << endl;
    cout << "number: " << instance.number << endl;
    cout << endl;

    // 获取实例地址并赋值给指针
    MyStructType* ptr = &instance;

    // 使用指针修改三个值
    ptr->first = "Goodbye";
    ptr->second = "Universe";
    ptr->number = 200;

   
    cout << "After modification using pointer:" << endl;

    cout << "first: " << ptr->first << endl;
    cout << "second: " << ptr->second << endl;
    cout << "number: " << ptr->number << endl;

    return 0;
}