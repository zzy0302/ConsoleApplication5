// ConsoleApplication5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
using namespace std;

class Memory {
public:
	bool isFree = true;
	int number = 0;
	int size = 0;
};
int speed = 10;
bool flag = false;
Memory memory[641];
int stepnow = 0;
int temp = 0;
string c;
int Thread[12] = { 1,2,3,2,4,3,1,5,6,7,6,0 };
int Block[12] = { 130,60,100,60,200,100,130,140,60,50,60,0 };
string Operate[12] = { "作业1申请130K","作业2申请60K","作业3申请100k","作业2释放60K","作业4申请200K","作业3释放100K","作业1释放130K","作业5申请140K","作业6申请60K","作业7申请50K","作业6释放60K" };
string operate_now;
int requestNumber;
int requestSize;
void outask()
{
	string a = "请输入请求序列号,再次输入序列号将清空序列";
	for (int i = 0; i < a.length(); i++)
	{
		cout << a[i];
		Sleep(speed);
	}
	cout << endl;
}

void output()
{
	system("cls");
	Sleep(100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+                     当前内存分配情况如下                     +" << endl;
	temp = 0;
	for (int i = 0; i < 640; i++)//显示状态
	{
		if (temp == 0)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		if (memory[i].number != temp)
		{
			temp = memory[i].number;
			if (temp == 0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (temp == 1)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			if (temp == 2)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
			if (temp == 3)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			if (temp == 4)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (temp == 5)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
			if (temp == 6)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_BLUE);
			if (temp == 7)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
		}
		Sleep(speed);
		if (!memory[i].isFree)
		{
			cout << memory[i].number;
		}
		if (memory[i].isFree)
		{
			cout << "0";

		}
		if ((i + 1) % 64 == 0)
			cout << endl;
	}
	cout << endl;
}

void step()
{
	requestNumber = Thread[stepnow];
	requestSize = Block[stepnow];
	operate_now = Operate[stepnow];
	stepnow++;
}

void Auto_mode()
{
	system("cls");
	step();
	while (requestNumber != 0)
	{
		Sleep(2000);
		system("cls");
		cout << operate_now;
		Sleep(2000);
		flag = false;
		for (int i = 0; i < 640; i++)
		{
			if (memory[i].number == requestNumber)
			{
				flag = true;
				for (int i = 0; i < 640; i++)
					if (memory[i].number == requestNumber)
					{
						memory[i].number = 0;
						memory[i].isFree = true;
					}
			}
			if (flag)
				break;
		}
		if (flag)
		{
			output();
			step();
			continue;
		}
		int freeBlock = 0;
		int tempMinFreeBlock = 640;
		int endAddress = 640;
		for (int i = 0; i < 641; i++) {//遍历内存块
			if (memory[i].isFree)//如果没被使用则freeBlock+1
			{
				freeBlock++;
			}
			if (freeBlock >= requestSize && !memory[i].isFree&&freeBlock <= tempMinFreeBlock)//如果遇到了另一个已被占用的内存块并且在两个内存块之前																																						
			{																																			//并且两个块之间的空余内存块大于请求内存大小,同时该空余内存块又
				tempMinFreeBlock = freeBlock;																						//比之前的空余内存块要小,则进行记录
				freeBlock = 0;
				endAddress = i - 1;
			}
			if (freeBlock < requestSize && !memory[i].isFree)																//反之清零
			{
				freeBlock = 0;
			}
		}
		for (int j = endAddress - tempMinFreeBlock + requestSize; j > endAddress - tempMinFreeBlock; j--)
		{
			memory[j].isFree = false;																										//开始占用
			memory[j].number = requestNumber;
			memory[j].size = requestSize;
		}

		output();
		step();
	}

	cout << "程序结束" << endl;
	Sleep(5000);
	exit(-0);
}

bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
	{

		return false;
	}
	if (sin >> c)
	{

		return false;
	}
	return true;
}

void Manual_mode()
{
	system("cls");
	outask();
	int requestNumber;
	cin >> requestNumber;
	while (requestNumber != 0)
	{
		flag = false;
		for (int i = 0; i < 640; i++)
		{
			if (memory[i].number == requestNumber)
			{
				flag = true;
				for (int i = 0; i < 640; i++)
					if (memory[i].number == requestNumber)
					{
						memory[i].number = 0;
						memory[i].isFree = true;
					}
			}
			if (flag)
				break;
		}
		if (flag)
		{
			output();
			outask();
			cin >> requestNumber;
			continue;
		}
		cout << "请输入请求序列所需内存大小" << endl;
		int requestSize;
		cin >> requestSize;
		int freeBlock = 0;
		int tempMinFreeBlock = 640;
		int endAddress = 640;
		for (int i = 0; i < 641; i++) {//遍历内存块
			if (memory[i].isFree)//如果没被使用则freeBlock+1
			{
				freeBlock++;
			}
			if (freeBlock >= requestSize && !memory[i].isFree&&freeBlock <= tempMinFreeBlock)//如果遇到了另一个已被占用的内存块并且在两个内存块之前																																						
			{																																			//并且两个块之间的空余内存块大于请求内存大小,同时该空余内存块又
				tempMinFreeBlock = freeBlock;																						//比之前的空余内存块要小,则进行记录
				freeBlock = 0;
				endAddress = i - 1;
			}
			if (freeBlock < requestSize && !memory[i].isFree)																//反之清零
			{
				freeBlock = 0;
			}
		}
		for (int j = endAddress - tempMinFreeBlock + requestSize; j > endAddress - tempMinFreeBlock; j--)
		{
			memory[j].isFree = false;																										//开始占用
			memory[j].number = requestNumber;
			memory[j].size = requestSize;
		}
		output();
		outask();
		cin >> requestNumber;

	}
	cout << "程序结束" << endl;
	Sleep(5000);
	exit(-0);
}

int main()
{
	memory[640].isFree = false;
	memory[640].number = 0;
	cout << "请输入运行速度[0-1000],默认为100" << endl;
	string tt;
	getline(cin, tt);
	if (isNum(tt))
	{
		if (stoi(tt) >= 0 && stoi(tt) <= 1000)
		{
			speed = 1000 - stoi(tt);
			cout << "速度 " << tt << " 已设定" << endl;
		}
	}
	else
		cout << "速度已设定为 100 " << endl;
	Sleep(2000);
	system("cls");
	while (1)
	{
		cout << "1.手动模式\n2.自动模式" << endl;
		cin >> c;
		if (c == "1")
			Manual_mode();
		else if (c == "2")
			Auto_mode();
		else
			cout << "输入错误，请重新输入" << endl;
		Sleep(3000);
		system("cls");
	}
}