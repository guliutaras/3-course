#include "head.h"

int main()
{
	system("CHCP 1251>NUL");
	cout<<"������������ ������ �3,4,5 ������ ����������� �����������"<<endl;

	//cordin_desent();
	cout<<"����� ������������� ������"<<endl;
	cout<<"--------------------"<<endl;
	fast_desent();
	cout<<endl;
	cout<<"����� �������"<<endl;
	cout<<"--------------------"<<endl;
	newton_method();
	system("pause");
	return 0;
}