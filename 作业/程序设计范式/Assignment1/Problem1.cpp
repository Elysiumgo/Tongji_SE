#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string fileName;
    cout << "Enter filename: ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file) {
        cout << "File not found!" << endl;
        return -1;
    }

    string word;
    int count = 0;
    while (file >> word) {
        if (word == "that") {
            count++;
        }
    }

    cout << "Occurrences of 'that': " << count << endl;
    return 0;
}