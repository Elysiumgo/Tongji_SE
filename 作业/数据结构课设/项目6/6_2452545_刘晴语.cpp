#include<iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;



class FamilyMember {
public:

	string name;     // 姓名
	string gender;   // 性别
	vector<FamilyMember*> children;  // 子女

	// 构造函数
	FamilyMember(string n, string g) : name(n), gender(g) {}
	void displayInfo() {
		cout << "姓名: " << name << endl;
		cout << "性别: " << gender << endl;
	}

};




class FamilyTree {
private:
	FamilyMember* root;  // 根节点（家族始祖）


	// 清空树
	void clearTree(FamilyMember* node) {
		if (node == nullptr) 
			return;
		for (auto child : node->children) {
			clearTree(child);
		}
		delete node;
	}


	// 创建家族始祖
	void createAncestor(string name, string gender) {
		
		root = new FamilyMember(name, gender);
		cout << "此家谱的祖先是： " << name << endl;
	}


	// 查找成员
	FamilyMember* findMember(FamilyMember* current, const string& name) {
		if (current == nullptr) 
			return nullptr;
		if (current->name == name) 
			return current;

		for (auto child : current->children) {
			FamilyMember* result = findMember(child, name);
			if (result != nullptr) 
				return result;
		}
		return nullptr;
	}


	//添加孩子
	bool addChild(string parentName, string childName, string gender) {
		
		FamilyMember* parent = findMember(root, parentName);

		if (parent == nullptr) {
			cout << "未找到父/母: " << parentName << endl;
			return false;
		}

		FamilyMember* child = new FamilyMember(childName, gender);
		parent->children.push_back(child);
		return true;
	}


	// 显示家庭成员
	void displayFamily(const string& name) {
		FamilyMember* member = findMember(root, name);

		if (member == nullptr) {
			cout << "未找到成员: " << name << endl;
			return;
		}

		cout << name << " 的家庭成员：" << endl;
		for (size_t i = 0; i < member->children.size(); i++) {
			cout << "第" << (i + 1) << "个孩子: " << member->children[i]->name
				<< " (" << member->children[i]->gender << ")" << endl;
		}
	}


	// 解散家庭
	void dissolveFamily(string name) {

		FamilyMember* member = findMember(root, name);
		if (member == nullptr) {
			cout << "未找到成员: " << name << endl;
			return;
		}

		if (member->children.empty()) {
			cout << name << " 没有子女，无需解散家庭" << endl;
			return;
		}

		cout << name << " 的家庭被解散，删除的子女有：" << endl;
		for (auto child : member->children) {
			cout << child->name << " ";
		}
		cout << endl;

		// 清空子女列表
		for (auto child : member->children) {
			clearTree(child);
		}
		member->children.clear(); //清空指针列表
	}



	// 更改成员信息
	void changeInfo(string oldName, string newName, string newGender) {
		FamilyMember* member = findMember(root, oldName);
		if (member == nullptr) {
			cout << "未找到成员: " << oldName << endl;
			return;
		}

		member->name = newName;
		member->gender = newGender;
		cout << "成功修改成员信息: " << oldName << " -> " << newName << endl;
	}


	




public:



	FamilyTree() :root(nullptr) {}

	//析构函数
	~FamilyTree() {
		clearTree(root);
	}



	void menu() {

		cout << "**	 	   家谱管理系统		    **" << endl
			<< "===================================" << endl
			<< "**      请选择要执行的操作：     **" << endl
			<< "**         A.完善家谱            **" << endl
			<< "**         B.添加家庭成员        **" << endl
			<< "**         C.解散局部家庭        **" << endl
			<< "**         D.更改家庭成员姓名    **" << endl
			<< "**         E.退出                **" << endl
			<< "===================================" << endl;


		cout << endl << "首先建立一个家谱" << endl;
		cout << "请输入祖先的姓名和性别：";


		string ancestorName, ancestorGender;
		while (1) {
			cin >> ancestorName >> ancestorGender;
			if (ancestorGender == "男" || ancestorGender == "女")
				break;

			else {
				cout << "输入错误，请重新输入：";
				cin.clear();
				cin.ignore(1024, '\n');
			}
		}

		createAncestor(ancestorName, ancestorGender);
		cin.ignore();
		char choice;
		while (1) {

			cout << "请输入要选择的操作：";
			cin >> choice;


			if (choice == 'A') {
				string parentName;
				cout << "请输入要建立家庭的人的姓名：";
				while (cin >> parentName) {
					if (parentName.empty()) {
						cout << "姓名不能为空，请重新输入：";
						cout << "请输入要建立家庭的人的姓名：";
						continue;
					}
					else if (!findMember(root, parentName)) {
						cout << "未找到父/母:" << parentName << endl;
						cout << "请输入要建立家庭的人的姓名：";
						continue;
					}

					break;
				}

				int membersNum;
				cout << "请输入" << parentName << "的儿女人数：";
				while (cin >> membersNum) {
					if (cin.fail()) {
						cout << "输入错误，请重新输入：";
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					break;
				}


				cout << "请依次输入" << parentName << "的儿女的姓名和性别：";

				for (int i = 0; i < membersNum; ) {
					string childName, gender;
					cin >> childName >> gender;
					if ((gender == "男" || gender == "女") && addChild(parentName, childName, gender))
						i++;
					else {
						cout << "输入错误，请重新输入：";
						cin.clear();
						cin.ignore(1024, '\n');
					}

				}
				

				displayFamily(parentName);


			}


			else if (choice == 'B') {
				string parentName;
				cout << "请输入要添加孩子的人的姓名：";
				while (cin >> parentName) {
					if (parentName.empty()) {
						cout << "姓名不能为空，请重新输入：";
						continue;
					}
					else if (!findMember(root, parentName)) {
						cout << "未找到目标成员:" << parentName << endl;
						cout << "请输入要添加孩子的人的姓名：";
						continue;
					}
					break;
				}


				cout << "请输入" << parentName << "要添加孩子的人的姓名和性别：";
				string childName, gender;
				while (1) {
					cin >> childName >> gender;
					if ((gender == "男" || gender == "女") && addChild(parentName, childName, gender))
						break;

					else {
						cout << "输入错误，请重新输入：";
						cin.clear();
						cin.ignore(1024, '\n');
					}
				}


				displayFamily(parentName);

			}

			
			else if (choice == 'C') {

				string parentName;
				cout << "请输入要解散家庭的人的姓名：";
				while (cin >> parentName) {
					if (parentName.empty()) {
						cout << "姓名不能为空，请重新输入：";
						continue;
					}
					break;
				}

				dissolveFamily(parentName);



			}


			else if (choice == 'D'){

				string oldName;
				cout << "请输入要更改姓名的人的目前姓名：";
				while (cin >> oldName) {
					if (oldName.empty()) {
						cout << "姓名不能为空，请重新输入：";
						cout << "请输入要更改姓名的人的目前姓名：";
						continue;
					}
					else if (!findMember(root, oldName)) {
						cout << "未找到目标成员:" << oldName << endl;
						cout << "请输入要更改姓名的人的目前姓名：";
						continue;
					}
					break;
				}
				

				string Newname, gender;
				cout << "请输入更改后的姓名和性别：";
				while (1) {
					cin >> Newname >> gender;
					if (gender == "男" || gender == "女" )
						break;

					else {
						cout << "输入错误，请重新输入：";
						cin.clear();
						cin.ignore(1024, '\n');
					}
				}

				
				changeInfo(oldName, Newname, gender);

			}


			else if(choice=='E')
				break;



		}







	}



};



int main() {

	FamilyTree MyFamily;
	MyFamily.menu();


	return 0;

}


