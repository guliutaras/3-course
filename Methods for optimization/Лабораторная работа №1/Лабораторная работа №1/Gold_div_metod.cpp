#include "Head.h"
#include "funk.h"

void gold_div_method()
{
	cout<<"ÌÅÒÎÄ ÇÎËÎÒÎÃÎ ÑÅ×ÅÍÈß----------"<<endl;
	double an=a;
	double bn=b;
	double x1=a+((3-pow(5,0.5))*(bn-an))/2;
	double x2=b-((3-pow(5,0.5))*(bn-an))/2;
	double A=f(x1);
	double B=f(x2);
	bool movement=0;
	cout<<"ak | x1 | x2 | bk | f(x1) | f(x2) | bn-an"<<endl;
	while(1)
	{
		cout<<an<<" "<<x1<<" "<<x2<<" "<<bn<<" "<<f(x1)<<" "<<f(x2)<<" "<<bn-an<<endl;
		if(A<B)
		{
			bn=x2;
			if(bn-an<=e) break;
			x2=x1;
			B=A;
			x1=an+((3-pow(5,0.5))*(bn-an))/2;
			A=f(x1);
		}
		else
		{
			an=x1;
			if(bn-an<=e) break;
			x1=x2;
			A=B;
			x2=bn-((3-pow(5,0.5))*(bn-an))/2;
			B=f(x2);		
		}

	}
	cout<<"Çíà÷åíèå ìèíèìóìà íàõîäèòüñÿ â òî÷êå ñ êîðäèíàòàìè:("<<(an+bn)/2<<", "<<-f((an+bn)/2)<<")"<<endl;
}