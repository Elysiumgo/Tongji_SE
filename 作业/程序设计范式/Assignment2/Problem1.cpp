#include<iostream>
#include<string>
using namespace std;

bool GetPalindrome(string &origin) {

	if (origin.empty())
		return false;


	int left = 0;
	int right = static_cast<int>(origin.length()) - 1;

	while (left < right) {
		if (origin[left] < origin[right])
			origin[right] = origin[left];
		else if (origin[left] > origin[right])
			origin[left] = origin[right];

		left++;
		right--;


   }

	return true;


}








int main() {



	while(1){
		string origin;
		cout << "Please input a string: ";
		getline(cin, origin);

		if (GetPalindrome(origin)) {
			cout << "The palindrome version: " << origin;
			break;
		}
		else {
			cout << "Input error! " << endl;
		}




	}

	return 0;
}