#include "head.h"
#include "funk.h"


double dihotomia_method(double a0, double b0, double x1t, double x2t)
{
    int k;    
    double lk, mk;
    double delta=0.5*e;
    double x_;
    double ak=a0, bk=b0;    
    k=1;
    do
    {
        lk=(ak+bk-delta)/2;
        mk=(ak+bk+delta)/2;
        k++;
        if(f(x1t - lk*fdx1(x1t,x2t), x2t - lk*fdx2(x1t,x2t))<=f(x1t - mk*fdx1(x1t,x2t), x2t - mk*fdx2(x1t,x2t))){bk=mk;}
        else{ak=lk;}
    } while ((bk-ak)>=e);
    x_=(ak+bk)/2;
    return x_;
}


void fast_desent()
{
    double x1n;
	double x1p;
    double x2n;
	double x2p;
    double alpha;

    x1p=x1;
    x2p=x2;

	cout<<"("<<x1p<<", "<<x2p<<")"<<" "<<"f("<<x1p<<", "<<x2p<<") = "<<f(x1p, x2p) <<endl;

    while (1)
    {
        alpha=dihotomia_method(-100,100,x1p,x2p);
        x1n=x1p-alpha*fdx1(x1p, x2p);
        x2n=x2p-alpha*fdx2(x1p, x2p);
        cout<<"("<<x1n<<", "<<x2n<<")"<<" "<<"f("<<x1n<<", "<<x2n<<") = "<<f(x1n, x2n) <<endl;
        if (sqrt(fdx1(x1n, x2n)*fdx1(x1n, x2n)+fdx2(x1n, x2n)*fdx2(x1n, x2n))<e){break;}
		x1p=x1n;x2p=x2n;
    }

    cout <<"Точка минимума достигнута!"<<endl;
    cout<<"("<<x1n<<", "<<x2n<<")"<<" "<<"f("<<x1n<<", "<<x2n<<") = "<<f(x1n, x2n) <<endl;                 
}
