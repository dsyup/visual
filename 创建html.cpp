#include<iostream>
#include<fstream>
#include"windows.h"
using namespace std;

//利用c++流文件操作建立html文件
int main()
{
	char filename[30], get[100];
	ofstream ot;
	cout << "Please input the name of getcontent file:\n";
	cin >> filename;
	ot.open(filename, ios::out);
	if (!ot)
	{
		cerr << "file can not be opened" << endl;
		abort();
	}
	cout << "Input the content returned by get :"
		<< "(Enter Crtl+Z to end input)\n";

	while (cin >> get)
	{
		ot <<get << '\n';
	}
	ot.close();

	ShellExecute(NULL, L"open", L"D:\\contest.html", NULL, NULL, SW_SHOWMAXIMIZED);

	system("pause");
}