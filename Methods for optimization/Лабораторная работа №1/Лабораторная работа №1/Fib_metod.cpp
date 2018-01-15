#include "Head.h"
#include "funk.h" 

double fib(double n)
{
	if(n==0) return 0;
	if(n==1 || n==2) return 1;
	return fib(n-1)+fib(n-2);
}

void fibonachi_method()
{
	cout<<"МЕТОД ФИБОНАЧЧИ----------"<<endl;
	double an=a;
	double bn=b;
	double k=1;
	while(!((fib(k+1)<=(b-a)/e)&&(fib(k+2)>=(b-a)/e))){k++;}
	double n=k;
	double uk=an+(fib(n)/fib(n+2))*(bn-an);
	double vk=an+(fib(n+1)/fib(n+2))*(bn-an);
	double A=f(uk);
	double B=f(vk);
	k=1;
	cout<<"ak | uk | vk | bk | f(uk) | f(vk) | k"<<endl;
	while(1)
	{
		cout<<an<<" "<<uk<<" "<<vk<<" "<<bn<<" "<<f(uk)<<" "<<f(vk)<<" "<<k<<endl;
		if(A<B)
		{
			bn=vk; 
			k++;
			if(k==n) break;
			vk=uk;
			B=A;
			uk=an+(fib(n-k+1)/fib(n+2))*(b-a);
			A=f(uk);
		}
		else 
		{
			an=uk;
			k++;
			if(k==n) break;
			uk=vk;
			A=B;
			vk=an+(fib(n-k+2)/fib(n+2))*(b-a);
			B=f(vk);
		}
	}
	cout<<"Значение минимума находиться в точке с кординатами:("<<(an+bn)/2<<", "<<-f((an+bn)/2)<<")"<<endl;
}