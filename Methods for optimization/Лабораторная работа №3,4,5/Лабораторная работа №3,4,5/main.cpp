#include "head.h"

int main()
{
	system("CHCP 1251>NUL");
	cout<<"Лабораторная работа №3,4,5 Методы многомерной оптимизации"<<endl;

	//cordin_desent();
	cout<<"Метод найскорейшего спуска"<<endl;
	cout<<"--------------------"<<endl;
	fast_desent();
	cout<<endl;
	cout<<"Метод Ньютона"<<endl;
	cout<<"--------------------"<<endl;
	newton_method();
	system("pause");
	return 0;
}