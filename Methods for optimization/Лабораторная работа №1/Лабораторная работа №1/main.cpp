#include "Head.h"

int main()
{ 
	system("CHCP 1251>NUL");
	cout<<"������������ ������ �1 ������ ���������� �����������"<<endl;
	cout<<"������: ����� �������� ������� y=(x^2+1)/x �� ������� [-2,-0,5] � ��������� e=10^-2"<<endl;
	half_div_method();
	gold_div_method();
	fibonachi_method();
	system("pause");
	return 0;
}