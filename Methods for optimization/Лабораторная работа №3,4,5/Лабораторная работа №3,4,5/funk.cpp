#include "funk.h"

double f(double x1, double x2)
{
	return 6*x1*x1+2*x1*x2+x2*x2+6*x1+6*x2;
}
double fdx1(double x1, double x2)
{
	return 12*x1+2*x2+6;
}
double fdx2(double x1, double x2)
{
	return 2*x1+2*x2+6;
}
double f2(double x1, double x2)
{
	return 7*x1*x1+5*x1*x2+x2*x2+6*x1+3*x2;
}
double f2x1(double x1, double x2)
{
	return 14*x1+5*x2+6;
}
double f2x2(double x1, double x2)
{
	return 5*x1+2*x2+3;
}