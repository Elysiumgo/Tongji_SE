#include<vector>
#include<iostream>
#include<string>
#define NUM 25
using namespace std;


void display(const vector<float>& numbers)
{
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i] << '\t';
		if ((i + 1) % 5 == 0 && i != 0)
			cout << endl;
	}
}
//´ò±í


void square(vector<float>& numbers)
{
	for (unsigned int i = 0; i < numbers.size(); i++)
		numbers[i] = numbers[i] * numbers[i];
	

}




int main()
{
	vector<float> numbers(NUM);
	cout << "Please enter 25 numbers:";
	for (int i = 0; i < NUM; i++)
	{
		cin >> numbers[i];
	}

	cout << endl << "Before multiplications:" << endl;
	display(numbers);
	square(numbers);

	cout << endl << "After multiplications:" << endl;
	display(numbers);

	return 0;




}