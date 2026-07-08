#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define PI 3.14159265358979323846

using namespace std;

double f(double x, double y) {
    return cos(x);
}

int main() {
    double x = 0;
    double y = 0;
    double h = 0.1;
    double end = 2 * PI;

    vector<int> errors;

    while (x <= end) {
    double y_true = sin(x);
    double err = (y - y_true) * (y - y_true);
    errors.push_back(err);

    cout << "x = " << x << endl
    << "y_num = " << y << endl
    << "y_true = " << y_true << endl<<endl;

    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 2, y + k1 / 2);
    double k3 = h * f(x + h / 2, y + k2 / 2);
    double k4 = h * f(x + h, y + k3);

    y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    x += h;
    }

    double mse = 0;
    for (double e : errors)
    mse += e;
    mse /= errors.size();

    cout << "MSE = " << mse << endl;
    return 0;
}