#include <stdio.h>
#include <iostream>
#include <windows.h>
using namespace std;



bool check_input(int input)
{
	return (input == 0 || input == 1);

}
//检查输入内容是否是0或1


void input(char name,int& index)
{
	while (1) {
		cout <<endl<< "请输入" << name << "的值（0或1），以回车结束：";
		cin >> index;
		if (check_input(index))
			break;
		else{
			cout << name << "的值输入有误，请重新输入" << endl;
			Sleep(2000);

		}
	}
	
}
//错误处理，循环输入


void output(int p,int q)
{
	cout << "\n\n  合取:\n       P/\\Q =" << (p && q) << endl;
	cout << "  析取:\n       P\\/Q =" << (p || q) << endl;
	cout << "  条件:\n       P->Q =" << ((!p) || q) << endl;
	cout << "  双条件:\n       P<->Q =" << (((!p) || q) && ((!q) || p)) << endl;

}

//进行逻辑运算并输出



bool exit()
{
	char s;
	while(1)
	{
		cout << "\n是否继续运算?（y/n）";
		cin >> s;
		if (s == 'y' || s == 'n')
		{
			if (s == 'y')
			{
				system("cls");  //清屏
				return 1;
			}
			else
			{
				cout << "欢迎下次再次使用!\n";  //退出
				return 0;

			}
			break;
		}
		else
		{
			cout << "输入错误,请重新输入!\n"; //错误校验

		}
	}
	

}

//退出循环函数，不完整，处理y/n循环以及错误处理






int main()
{
	while(1){
		cout << "***************************************" << endl;
		cout << "**                                   **\n";
		cout << "**        欢迎进入逻辑运算程序       **\n";
		cout << "**                                   **\n";
		cout << "***************************************" << endl;


		int p = 0, q = 0;
		input('P', p);
		input('Q', q);



		output(p, q);


		if (!exit())
			break;

		//补充退出条件

	}



}









