#include<iostream>
#include<string>
using namespace std;


class Author {

private:
	string name;

public:
	Author(const string& authorName) : name(authorName) {
		cout << "Author constructor: " << name << endl;
	}

	// 拷贝构造函数
	Author(const Author& other) : name(other.name) {
		cout << "Author copy constructor: " << name << endl;
	}

	// 赋值运算符
	Author& operator=(const Author& other) {
		if (this != &other) {
			name = other.name;
		}
		cout << "Author assignment: " << name << endl;
		return *this;

	}

	string getName() const { 
		return name; 
	}

};


class Publisher {

private:
	string name;

public:

	//构造函数
	Publisher(const string& publisherName) : name(publisherName) {
		cout << "Publisher constructor: " << name << endl;
	}


	// 拷贝构造函数
	Publisher(const Publisher& other) : name(other.name) {
		cout << "Publisher copy constructor: " << name << endl;
	}


	Publisher& operator=(const Publisher& other) {


		if (this != &other) {
			name = other.name;

		}

		cout << "Publisher assignment: " << name << endl;
		return *this;
	}


	string getName() const { 
		return name; 
	}



};



class Book :public Author {

private:
	Publisher publisher;

public:

	//默认构造函数
	Book() : Author("Unknown"), publisher("Unknown") {
		cout << "Book default constructor" << endl;
	}

	//带两个字符串参数的构造函数
	Book(const string& authorName, const string& publisherName) :Author(authorName), publisher(publisherName) {
		cout << "Book parameterized constructor" << endl;
	}

	//拷贝构造函数
	Book(const Book& other) 
        : Author(other),  // 调用基类的拷贝构造函数
          publisher(other.publisher) {  // 调用Publisher的拷贝构造函数
        cout << "Book copy constructor" << endl;
    }



	// 赋值运算符
	Book& operator=(const Book& other) {
		if (this != &other) {
			Author::operator=(other);  //调用基类的赋值运算符
			publisher = other.publisher; //调用成员的赋值运算符
		}
		cout << "Book assignment" << endl;
		return *this;
	}

	void display() const {
		cout << "Author: " << getName() << ", Publisher: " << publisher.getName() << endl;
	}

};



int main() {
	cout << "=== Creating book1 ===" << endl;
	Book book1("蔡昇晏", "昨天的孩子");
	book1.display();

	cout << "\n=== Creating book2 (copy of book1) ===" << endl;
	Book book2 = book1;  //调用拷贝构造函数
	book2.display();

	cout << "\n=== Creating book3 (default) ===" << endl;
	Book book3;  //调用默认构造函数
	book3.display();

	cout << "\n=== Assigning book1 to book3 ===" << endl;
	book3 = book1;  //调用赋值运算符
	book3.display();

	cout << "\n=== Creating book4 with different values ===" << endl;
	Book book4("石锦航", "因为留不住");
	book4.display();

	return 0;
}










