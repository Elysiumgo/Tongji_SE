#include<cmath>
#include <limits>
#include<iostream>

using namespace std;

const int kVowelCount = 5;
const int kConsonantCount = 21;

int main() {
	int n;
	while(1){
		cout << "Please input the number n(1-10): ";
		cin >> n;

		if (cin.good() && n >= 1 && n <= 10)
			break;
		else {
			cout << "Input error. Please enter an integer between 1 and 10." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}

	long long result = 1;
	int vowel_count = (n + 1) / 2;
	int consonant_count = n / 2;

	for (int i = 0; i < vowel_count; i++)
		result *= kVowelCount;
	for (int i = 0; i < consonant_count; i++)
		result *= kConsonantCount;


	cout << result << endl;

	return 0;

}