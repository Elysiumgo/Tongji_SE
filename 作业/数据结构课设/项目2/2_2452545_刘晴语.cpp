#include<iostream>
using namespace std;



struct ElementsNode {

	int data=-1;
	ElementsNode* next=NULL;

};




void input(ElementsNode*& head) {
	while (true) {
		head = NULL;
		ElementsNode* tail = NULL;
		bool hasDuplicate = false;
		int duplicateValue = -1;

		// 临时存储输入的数据
		int tempData[1000];
		int count = 0;

		// 先读取所有输入
		while (true) {
			int data;
			cin >> data;
			if (data == -1) break;
			tempData[count++] = data;
		}

		// 检查是否有重复
		for (int i = 0; i < count && !hasDuplicate; i++) {
			for (int j = i + 1; j < count && !hasDuplicate; j++) {
				if (tempData[i] == tempData[j]) {
					hasDuplicate = true;
					duplicateValue = tempData[i];
					break;
				}
			}
		}

		// 如果有重复，提示并重新输入
		if (hasDuplicate) {
			cout << "集合中存在重复元素 " << duplicateValue << "，请重新输入整个集合（以-1结束）: ";
			// 清空输入缓冲区
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		// 如果没有重复，构建链表
		for (int i = 0; i < count; i++) {
			ElementsNode* newNode = new ElementsNode;
			newNode->data = tempData[i];

			if (head == NULL) {
				head = newNode;
				tail = newNode;
			}
			else {
				tail->next = newNode;
				tail = newNode;
			}
		}
		break;
	}
}

void remove(ElementsNode*& preCurrent) {
	ElementsNode* current = preCurrent->next;
	preCurrent->next = current->next;
	delete current;
}
//删除元素



bool findX(int goal, ElementsNode* head) {
	ElementsNode* current = head;
	while (current != NULL) {
		if (current->data == goal)
			return 1;
		else 
			current = current->next;
		
	}
	
	return 0;


}

//寻找元素



void compare(ElementsNode*& headA, ElementsNode* headB) {

	if (headA == NULL || headB == NULL) {
		headA = NULL;
		return;
	}
		
	//是空集则直接返回


	

	while (headA != NULL && !findX(headA->data, headB)) { //A没有结束，且头节点不是交集元素
		ElementsNode* preA = headA;	
		headA = headA->next;
		delete preA;

	}

	//直到找到第一个交集元素


	if (headA == NULL)
		return;

	//如果删完了则直接返回


	ElementsNode* preCurrentA = headA;
	ElementsNode* currentA = headA->next;
	


	while (currentA != NULL) {
		int goal = currentA->data;
		

		if (!findX(goal, headB)) {
			//没有找到
			remove(preCurrentA);
			currentA = preCurrentA->next;
		}
		else {
			preCurrentA = currentA;
			currentA = currentA->next;
		}
		



	}


	


}


void output(ElementsNode* A) {

	if (A == NULL) {
		cout << "NULL";
		return;
	}


	while (A != NULL) {
		cout << A->data;
		if (A->next != NULL)
			cout << ' ';
		A = A->next;
	}




}



void deleteList(ElementsNode*& head) {
	while (head != NULL) {
		ElementsNode* temp = head;
		head = head->next;
		delete temp;
	}
}





int main() {
	ElementsNode* headA;
	ElementsNode* headB;

	
	cout << "请输入集合A的元素（以-1结束）：";
	input(headA);
	cout << "请输入集合B的元素（以-1结束）：";
	input(headB);

	
	compare(headA, headB);
	output(headA);


	deleteList(headA);
	deleteList(headB);

	return 0;


}



