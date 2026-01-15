#include<iostream>
#include<vector>
#include <memory>
using namespace std;


class Shape {
public:
	virtual ~Shape() = default;  // 虚析构函数

	virtual Shape* clone() const {
		return new Shape(*this);  // 返回新的拷贝
	}
	
};

class Circle :public Shape {
private:
	double radius;

public:

	Circle(const double r):radius(r){}

	Circle* clone() const override {
		return new Circle(*this);
	}

};


class Rectangle :public Shape {
private:
	double width, height;
public:

	Rectangle(double w, double h) : width(w), height(h) {}

	Rectangle* clone() const override {
		return new Rectangle(*this);
	}

};




class ShapeWithSmartPtr {
public:
	virtual ~ShapeWithSmartPtr() = default;

	//智能指针版本
	virtual unique_ptr<ShapeWithSmartPtr> clone() const {
		return make_unique<ShapeWithSmartPtr>(*this);
	}

};


class CircleWithSmartPtr : public ShapeWithSmartPtr {

private:
	double radius;
public:
	CircleWithSmartPtr(double r) : radius(r) {}

	unique_ptr<ShapeWithSmartPtr> clone() const override {
		return make_unique<CircleWithSmartPtr>(*this);
	}

};


class RectangleWithSmartPtr : public ShapeWithSmartPtr {
private:
	double width, height;
public:
	RectangleWithSmartPtr(double w, double h) : width(w), height(h) {}

	unique_ptr<ShapeWithSmartPtr> clone() const override {
		return make_unique<RectangleWithSmartPtr>(*this);
	}

};








int main() {

	cout << "=== 原始指针版本测试 ===" << endl;
	vector<Shape*> shapes;
	shapes.push_back(new Circle(5.0));
	shapes.push_back(new Rectangle(3.0, 4.0));

	vector<Shape*> clonedShapes;
	for (Shape* shape : shapes) {
		Shape* cloned = shape->clone();
		clonedShapes.push_back(cloned);


		//验证类型
		cout << "原始类型: " << typeid(*shape).name()
			<< ", 克隆类型: " << typeid(*cloned).name() << endl;

	}

	for (Shape* shape : shapes) 
		delete shape;
	for (Shape* shape : clonedShapes) 
		delete shape;





	cout << "\n=== 智能指针版本测试 ===" << endl;
	vector<unique_ptr<ShapeWithSmartPtr>> smarterShapes;
	smarterShapes.emplace_back(make_unique<CircleWithSmartPtr>(5.0));
	smarterShapes.emplace_back(make_unique<RectangleWithSmartPtr>(3.0, 4.0));


	vector<unique_ptr<ShapeWithSmartPtr>> clonedSmarterShapes;

	for (auto& shape : smarterShapes) {
		auto cloned = shape->clone();
		clonedSmarterShapes.emplace_back(std::move(cloned));

		// 验证类型
		cout << "原始类型: " << typeid(*shape).name()
			<< ", 克隆类型: " << typeid(*clonedSmarterShapes.back()).name() << endl;
	}
}



