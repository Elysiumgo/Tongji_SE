#include<iostream>
#include<string>
#include<vector>
#include<limits>
#include<chrono>
using namespace std;


class BankAccount {

private:
	
	struct Account {
		string name = "anonymous";
		double balance = 0.0;
		string type = "saving";
	};
	
	vector<Account> allAccounts;


	//比较是否相同
	bool equalityTest(const string& goal) {
		
		bool found = 0;
		
		for (size_t i = 0; i < allAccounts.size(); i++) {

			if (allAccounts[i].name == goal) {
				found = 1;
				break;

			}
				
		}

		return found;

	}

	//存款函数
	void deposit(const string& name,const double amount) {

		bool found = 0;
		size_t i = 0;
		for (; i < allAccounts.size(); i++) {

			if (allAccounts[i].name == name) {
				found = 1;
				break;

			}
		}

		

		if (found == 1) {
			allAccounts[i].balance += amount;
			cout << "Deposit successful." << endl;
		}
			
		else
			cout << "Account doesn't exist. " << endl;
		

	}


	//取款函数
	void withdraw(const string& name, const double amount) {

		bool found = 0;
		
		size_t i = 0;
		for (; i < allAccounts.size(); i++) {

			if (allAccounts[i].name == name) {
				found = 1;
				break;
			}
		}

		if(found==1){
			if (amount > allAccounts[i].balance) {
				cout << "Insufficient balance." << endl;
			}
			else {
				allAccounts[i].balance -= amount;
				cout << "Withdrawal successful." << endl;
			}
		}
	
		else {
			cout << "Account doesn't exist. " << endl;
		}

	}


	//罗列函数
	void display() {

		for (size_t i = 0; i < allAccounts.size(); i++) {
			cout << "Account " << i + 1 << "." << endl
				<< "name: " << allAccounts[i].name << endl
				<< "balance: " << allAccounts[i].balance << endl
				<< "type: " << allAccounts[i].type << endl << endl;
		}

	}




	//比较是否不同
	bool inequalityTest(const string& goal) {

		bool found = 1;

		for (size_t i = 0; i < allAccounts.size(); i++) {

			if (allAccounts[i].name == goal) {
				found = 0;
				break;

			}

		}

		return found;

	}

	//获取要操作的账户名
	string getName() {
		cout << "Please enter the name of the account: ";
		string name;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区
		getline(cin, name);  //可以获取带空格的

		return name;

	}

	//获取要操作的款项
	double getAmount() {

		cout << "Please enter amount: ";

		double d;
		while (!(cin >> d)) {
			if (cin.fail()) {
				cout << "Input error. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}
			else
				break;
		}


		return d;

	}



public:

	void input() {

		Account tmp;
		
		cout << "Please enter account name: ";

		//输入用户名，默认为Anonymous
		while (1) {
			cout << "Anonymous? (Y/N) :";
			string s;
			cin >> s;
			if (s == "Y")
				break;
			else if (s == "N"){
				cout << "name: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区
				getline(cin, tmp.name);
				break;
			}

		}
		
	
		while (1) {

			cout << "Please enter balance: ";
			cin >> tmp.balance;
			if (cin.fail()) {
				cout << "Input error. ";
				cin.clear();
				cin.ignore(1024, '\n');

			}
			else
				break;

		}


		while (1) {

			cout << "Please enter type (saving/current) : ";
			cin >> tmp.type;
			if (tmp.type !="saving"&& tmp.type!="current") {
				cout << "Input error. ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}
			else
				break;

		}

		allAccounts.push_back(tmp);


	}

	//菜单
	void menu() {


		cout << "==================" << endl
			<< "1.deposit " << endl
			<< "2. withdraw" << endl
			<< "3. equalityTest" << endl
			<< "4. inequalityTest" << endl
			<< "5. display" << endl
			<< "6. input" << endl
			<< "0. exit" << endl
			<< "==================" << endl;

		while (1) {
			cout << "\nPlease enter your choice: ";
			int choice;
			cin >> choice;
			
			if (choice == 1)
				deposit(getName(), getAmount());
			else if (choice == 2)
				withdraw(getName(), getAmount());
			else if (choice == 3) {
				if (equalityTest(getName()))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;

			}
			else if (choice == 4) {
				if (inequalityTest(getName()))
					cout << "TRUE" << endl;
				else
					cout << "FALSE" << endl;

			}
			else if (choice == 5)
				display();
			else if (choice == 6)
				input();
			else if (choice == 0)
				break;
			else {
				cout << "Input error." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}


		}





	}



};


int main() {

	BankAccount MyBank;
	MyBank.input();
	MyBank.menu();

	
	return 0;


}




