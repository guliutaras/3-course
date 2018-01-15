#include "head.h"
#include "funk.h"


void cordin_desent()
{
	int k=1;
	int n=1;
	double a1=0.5;
	double a2=0.5;
	double x1p=x1;
	double x2p=x2;
	double x1n=x1p;
	double x2n=x2p;
	double A=0;
	double B=f(x1,x2);
	bool cheak=0;
	do
	{
		if(cheak && sqrt((x1n-x1p)*(x1n-x1p)+(x2n-x2p)*(x2n-x2p))<e) break;
		A=B;
		if(n==1)
		{
			B=f(x1n+a1,x2n);
			if(B<A)
			{
				x1p=x1n;
				x1n=x1n+a1;
				while(f(x1n+2*a1,x2n)<A)
				{
					a1=a1*2;
					A=B;
					B=f(x1n+a1,x2n);
					x1p=x1n;
					x1n=x1n+a1;
				}
				a2=a1;
				n++;
				cout<<x1n<<" "<<x2n<<endl;
				continue;
			}
			B=f(x1n-a1,x2n);
			if(B<A)
			{
				x1p=x1n;
				x1n=x1n-a1;
				while(f(x1n-2*a1,x2n)<A)
				{
					a1=a1*2;
					A=B;
					B=f(x1n-a1,x2n);
					x1p=x1n;
					x1n=x1n-a1;
				}
				a2=a1;
				n++;
				cout<<x1n<<" "<<x2n<<endl;
				continue;
			}
			B=f(x1n,x2n);
			a1=a1/2;
			a2=a1;
			n++;
			continue;
		}
		if(n==2)
		{
			B=f(x1n,x2n+a2);
			if(B<A)
			{
				x2p=x2n;
				x2n=x2n+a2;
				while(f(x1n,x2n+2*a2)<A)
				{
					a2=a2*2;
					A=B;
					B=f(x1p,x2n+a2);
					x2p=x2n;
					x2n=x2n+a2;
				}
				a1=a2;
				n--;
				cout<<x1n<<" "<<x2n<<endl;
				cheak=1;
				continue;
			}
			B=f(x1p,x2p-a2);
			if(B<A)
			{
				x2p=x2n;
				x2n=x2n-a2;
				while(f(x1n,x2n-2*a2)<A)
				{
					a2=a2*2;
					A=B;
					B=f(x1n,x2n-a2);
					x2p=x2n;
					x2n=x2n-a2;
				}
				a1=a2;
				n--;
				cout<<x1n<<" "<<x2n<<endl;
				cheak=1;
				continue;
			}
			B=f(x1n,x2n);
			a2=a2/2;
			a1=a2;
			n--;
			continue;
		}
	}while(1);
	cout<<"Минимум достигнут в точке f("<<x1p<<" , "<<x2p<<") = "<<f(x1p,x2p)<<endl;
}