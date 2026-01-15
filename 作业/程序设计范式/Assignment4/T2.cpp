#include<iostream>
using namespace std;


class Vector3D {

private:
	float x, y, z;

public:

    //构造函数们
    Vector3D() {
        while (1) {

            cout << "Enter x, y, z: ";
            cin >> x >> y >> z;

            if (cin.good())
                break;
            else {
                cout << "Input error. " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

        }
    }

    Vector3D(float arr[3]) {
        x = arr[0];
        y = arr[1];
        z = arr[2];
    }

    Vector3D(float x_val, float y_val, float z_val) {
        x = x_val;
        y = y_val;
        z = z_val;
    }



    Vector3D add(const Vector3D& v) {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }


    float dot(const Vector3D& v) {
        return x * v.x + y * v.y + z * v.z;
    }


    Vector3D cross(const Vector3D& v) {
        return Vector3D(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }


    void print() {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }


    // 向量加法
    Vector3D operator+(const Vector3D& v) {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }


    // 向量减法
    Vector3D operator-(const Vector3D& v) {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }


    // 标量乘法
    Vector3D operator*(float scalar) {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }


    // v1+=v2
    Vector3D& operator+=(const Vector3D& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;  // 返回当前对象的引用
    }

    float& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw out_of_range("Index out of range");
    }

    // const版本的下标运算符
    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        throw out_of_range("Index out of range");
    }


    friend Vector3D operator*(float scalar, const Vector3D& v);

};


Vector3D operator*(float scalar, const Vector3D& v) {
    return Vector3D(scalar * v.x, scalar * v.y, scalar * v.z);
}


int main() {
    //测试代码
    float arr1[3] = { 1, 2, 3 };

    const Vector3D v0 = Vector3D();
    Vector3D v1(arr1);
    Vector3D v2(4,5,6);

    //使用运算符重载
    Vector3D v3 = v1 + v2;  //向量加法
    Vector3D v4 = v1 - v2;  //向量减法
    Vector3D v5 = v1 * 2.5; //标量乘法
    Vector3D v6 = 3.0 * v1; //标量乘法（另一种顺序）

    v1 += v2;  //复合赋值

    //访问分量
    cout << "v1 x: " << v1[0] << endl;
    cout << "v1 y: " << v1[1] << endl;
    cout << "v1 z: " << v1[2] << endl;

    cout << "v0 x: " << v0[0] << endl;
    cout << "v0 y: " << v0[1] << endl;
    cout << "v0 z: " << v0[2] << endl;

    return 0;
}