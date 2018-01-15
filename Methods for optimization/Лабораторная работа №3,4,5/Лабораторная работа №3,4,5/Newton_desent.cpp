#include "head.h"
#include "funk.h"

void newton_method()
{
	double xp[]={x1,x2};
	double xn[]={0,0};
	double frevdob[2][2]=
	{
		{2,-5},
		{-5,14}
	};
	cout<<"("<<xp[0]<<", "<<xp[1]<<")"<<" "<<"f("<<xp[0]<<", "<<xp[1]<<") = "<<f2(xp[0], xp[1]) <<endl;

	while(1)
	{
		double p[]={0,0};
		p[0]=-1/3.0*(frevdob[0][0]*f2x1(xp[0],xp[1])+frevdob[0][1]*f2x2(xp[0],xp[1]));
		p[1]=-1/3.0*(frevdob[1][0]*f2x1(xp[0],xp[1])+frevdob[1][1]*f2x2(xp[0],xp[1]));

		xp[0]=xp[0]+p[0];
		xp[1]=xp[1]+p[1];
		cout<<"("<<xp[0]<<", "<<xp[1]<<")"<<" "<<"f("<<xp[0]<<", "<<xp[1]<<") = "<<f2(xp[0], xp[1]) <<endl;

		if(sqrt(f2x1(xp[0],xp[1])*f2x1(xp[0],xp[1])+f2x2(xp[0],xp[1])*f2x2(xp[0],xp[1]))<e){break;}
	}
	cout <<"Точка минимума достигнута!"<<endl;
	cout<<"("<<xp[0]<<", "<<xp[1]<<")"<<" "<<"f("<<xp[0]<<", "<<xp[1]<<") = "<<f2(xp[0], xp[1]) <<endl;
}