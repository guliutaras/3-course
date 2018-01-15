#include "Head.h"
#include "funk.h"

void half_div_method()
{
	double ak=a;
	double bk=b;
	double del=0.005;
	double x1=(ak+bk+del)/2;
	double x2=(ak+bk-del)/2;
	cout<<"МЕТОД ДИХОТОМИИ----------"<<endl;
	cout<<"ak | bk | x1 | x2 | f(x1) | f(x2) | bk-ak"<<endl;
	while(1)
	{
		cout<<ak<<" "<<bk<<" "<<x1<<" "<<x2<<" "<<f(x1)<<" "<<f(x2)<<" "<<bk-ak<<endl;
		if(f(x1)>=f(x2)){
			bk=x2;
			if(bk-ak<e) break;
			x1=(ak+bk+del)/2;
			x2=(ak+bk-del)/2;
			continue;}
		if(f(x1)<f(x2)){	
			ak=x1;
			if(bk-ak<e) break;
			x1=(ak+bk+del)/2;
			x2=(ak+bk-del)/2;
			continue;}
	}
	cout<<"Значение минимума находиться в точке с кординатами:("<<(ak+bk)/2<<", "<<-f((ak+bk)/2)<<")"<<endl;
}