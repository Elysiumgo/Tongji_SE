#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;



class Student {
private:
    int num;
    char name[50];
    char gender[10];
    int age;
    char item[50];

public:
    // 构造函数
    Student() : num(0), age(0) {
        name[0] = '\0';
        gender[0] = '\0';
        item[0] = '\0';
    }

    Student(int n, const char* na, const char* g, int a, const char* i) : num(n), age(a) {
        strcpy(name, na);
        strcpy(gender, g);
        strcpy(item, i);
    }

    // 输入数据
    void input() {
       

       
        while(1){
            cin >> num >> name >> gender >> age >> item;
            if (age >= 0 && age < 150)
                break;
            else
                cout << "输入非法，请重新输入" << endl;
        }
        

    }

    // 输出数据
    void display() const {
        cout << num << '\t' << name << '\t' << gender << '\t' << age << '\t' << item << endl;
    }

    // getter 方法
    int getNum() const { return num; }
    const char* getName() const { return name; }
    const char* getGender() const { return gender; }
    int getAge() const { return age; }
    const char* getItem() const { return item; }


};

struct StudentNode {
    Student data;
    StudentNode* next;
};

class ExamSystem {
private:
    StudentNode* head;
    int currentSize;

    void headline() {
        cout << endl << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
    }

public:
    ExamSystem() : head(nullptr), currentSize(0) {}

    ~ExamSystem() {
        // 释放内存
        StudentNode* current = head;
        while (current != nullptr) {
            StudentNode* temp = current;
            current = current->next;
            delete temp;
        }
    }



    int inputNum(const char words[])
    {
        int num = 0;
        while (1)
        {
            cout << "请输入要" << words << "的考生的考号：";
            cin >> num;
            StudentNode* current = head;
            while (current != nullptr && current->data.getNum() != num)
                current = current->next;

            if (current == nullptr)
                cout << "未找到该考号，请重新输入" << endl;
            else
                break;

        }
        return num;

    }

    //检查输入的考号是否合法


    void check() {

        int targetNum = inputNum("查找");

        StudentNode* current = head;
        while (current != nullptr) {
            if (current->data.getNum() == targetNum) {
                headline();
                current->data.display();
                return;
            }
            current = current->next;
        }
        cout << "未找到考号为 " << targetNum << " 的考生" << endl;

    }

    void list() {
        headline();
        StudentNode* current = head;
        while (current != nullptr) {
            current->data.display();
            current = current->next;
        }
    }

    void modify() {
        int targetNum = inputNum("修改");


        StudentNode* current = head;
        while (current != nullptr) {
            if (current->data.getNum() == targetNum) {
                cout << "请输入考生信息（考号 姓名 性别 年龄 报考类别）：" << endl;
                current->data.input();
                list();
                return;
            }
            current = current->next;
        }
        cout << "未查询到考号为 " << targetNum << " 的考生信息" << endl;
    }

    void Delete() {
        int targetNum = inputNum("删除");

        StudentNode* current = head;
        StudentNode* preCurrent = nullptr;

        while (current != nullptr) {
            if (current->data.getNum() == targetNum) {
                break;
            }
            else {
                preCurrent = current;
                current = current->next;
            }
        }

        if (current == nullptr) {
            cout << "未查询到考号为 " << targetNum << " 的考生信息" << endl;
            return;
        }

        if (preCurrent == nullptr) {
            head = current->next;
        }
        else {
            preCurrent->next = current->next;
        }

        delete current;
        currentSize--;

    }

    void insert() {
        cout << "请输入要插入的位置：";
        int pos;
        cin >> pos;

        if (pos < 1 || pos > currentSize + 1) {
            cout << "插入位置无效" << endl;
            return;
        }

        StudentNode* newNode = new StudentNode;

        cout << "请输入考生信息（考号 姓名 性别 年龄 报考类别）：" << endl;
        newNode->data.input();


        if (pos == 1) {
            newNode->next = head;
            head = newNode;
        }
        else {
            StudentNode* current = head;
            for (int i = 1; i < pos - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        currentSize++;

    }

    void menu() {
        cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
        while (1) {
            cout << endl << "请选择您要进行的操作：";
            int choice;
            cin >> choice;

            if (choice == 1)
                insert();
            else if (choice == 2)
                Delete();
            else if (choice == 3)
                check();
            else if (choice == 4)
                modify();
            else if (choice == 5)
                list();
            else if (choice == 0)
                break;
            else
                cout << "输入非法，请重新输入" << endl;

        }
    }

    void initialize() {
        cout << "首先请建立考生信息系统！" << endl
            << "请输入考生人数:";
        int T;
        cin >> T;
        currentSize = T;

        cout << endl << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！" << endl;

        StudentNode* tail = nullptr;
        for (int i = 0; i < T; i++) {
            StudentNode* newNode = new StudentNode;

            while (true) {
                newNode->data.input();

                // 检查考号是否重复
                bool isDuplicate = false;
                StudentNode* current = head;
                while (current != nullptr) {
                    if (current->data.getNum() == newNode->data.getNum()) {
                        isDuplicate = true;
                        break;
                    }
                    current = current->next;
                }

                if (isDuplicate) {
                    cout << "考号重复，请重新输入该考生信息：" << endl;
                }
                else {
                    break;
                }
            }

            newNode->next = nullptr;

            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }
};

int main() {
    ExamSystem system;
    system.initialize();
    system.menu();
    return 0;
}