#include "Head.h"

int main()
{ 
	system("CHCP 1251>NUL");
	cout<<"Лабораторная работа №1 Методы одномерной оптимизации"<<endl;
	cout<<"Задача: Найти максимум функции y=(x^2+1)/x на отрезке [-2,-0,5] с точностью e=10^-2"<<endl;
	half_div_method();
	gold_div_method();
	fibonachi_method();
	system("pause");
	return 0;
}