#include <glut.h>
#include<gl\GL.h>
#include <gl\GLU.h>
#include <windows.h>
#include <math.h>

struct Color
{
	int R;
	int G;
	int B;
	Color(int* a):R(a[0]), G(a[1]), B(a[2]){}
	Color(Color& C){R=C.R; G=C.G; B=C.B;}
	void PaintColor(){glColor3ub(R,G,B);}
};

class Letter
{
protected:
	int rotat_x;
	int rotat_y;
	int rotat_z;
	int x;
	int y;
	int z;
	Color front;
	Color back;
	Color border;
	int dy;
	int dx;
	int dz;
	
public:
	bool lightOff;
	Letter(int xx, int yy, int zz ,int *f, int * s, int* t): x(xx), y(yy), z(zz), dx(0), dy(0), dz(0),rotat_x(0),rotat_y(30), rotat_z(0), front(f), back(s), border(t), lightOff(0){}
	virtual void draw(){return;}
	void rotate_x(int r){rotat_x=rotat_x+r; if(rotat_x==360) rotat_x=0;}
	void rotate_y(int r){rotat_y=rotat_y+r; if(rotat_y==360) rotat_y=0;}
	void rotate_z(int r){rotat_z=rotat_z+r; if(rotat_z==360) rotat_z=0;}
	void move(int xx, int yy, int zz){dx=dx+xx; dy=dy+yy; dz=dz+zz;}
	void normalMove(){dx=0; dy=0; dz=0; rotat_x=0; rotat_y=0; rotat_z=0;}
};

class LetterT: public Letter
{
	int h;
	int w;
	int d;
	int grid_h;
	int grid_w;
public:
	LetterT(int xx, int yy,int zz, int *f, int * s, int* t, int hh, int ww, int dd): Letter(xx,yy,zz,f,s,t), h(hh), w(ww),d(dd)
	{
		grid_h=h/6;
		grid_w=h/7;
	}
	void draw_front_back(int depth, bool back)
	{
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		//нижняя трапеция
		glVertex3f(-0.5*grid_w,-2*grid_h,depth);
		glVertex3f(-1.5*grid_w,-3*grid_h,depth);
		glVertex3f(0,-3*grid_h,depth);

		glVertex3f(-0.5*grid_w,-2*grid_h,depth);
		glVertex3f(0,-3*grid_h,depth);
		glVertex3f(1.5*grid_w,-3*grid_h,depth);

		glVertex3f(-0.5*grid_w,-2*grid_h,depth);
		glVertex3f(1.5*grid_w,-3*grid_h,depth);
		glVertex3f(0.5*grid_w,-2*grid_h,depth);

		// основной прямоугольник
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(0.5*grid_w,-2*grid_h,depth);
		glVertex3f(-0.5*grid_w,-grid_h,depth);
		glVertex3f(0.5*grid_w,-grid_h,depth);
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(-0.5*grid_w,-2*grid_h,depth);
		glVertex3f(0.5*grid_w,-2*grid_h,depth);
		glVertex3f(-0.5*grid_w,-grid_h,depth);
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(0.5*grid_w,-grid_h,depth);
		glVertex3f(-0.5*grid_w,0,depth);
		glVertex3f(-0.5*grid_w,-grid_h,depth);
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(0.5*grid_w,-grid_h,depth);
		glVertex3f(0.5*grid_w,0,depth);
		glVertex3f(-0.5*grid_w,0,depth);
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(-0.5*grid_w,0,depth);
		glVertex3f(0.5*grid_w,grid_h,depth);
		glVertex3f(-0.5*grid_w,grid_h,depth);
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(-0.5*grid_w,0,depth);
		glVertex3f(0.5*grid_w,0,depth);
		glVertex3f(0.5*grid_w,grid_h,depth);
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(0.5*grid_w,grid_h,depth);
		glVertex3f(-0.5*grid_w,2*grid_h,depth);
		glVertex3f(0.5*grid_w,2*grid_h,depth);
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(0.5*grid_w,grid_h,depth);
		glVertex3f(-0.5*grid_w,grid_h,depth);
		glVertex3f(-0.5*grid_w,2*grid_h,depth);

		// врехний прямоугольник c скосами
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-0.5*grid_w,2*grid_h,depth);
		glVertex3f(0.5*grid_w,3*grid_h,depth);
		glVertex3f(0.5*grid_w,2*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(0.5*grid_w,2*grid_h,depth);
		glVertex3f(1.5*grid_w,3*grid_h,depth);
		glVertex3f(1.5*grid_w,2*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(1.5*grid_w,2*grid_h,depth);
		glVertex3f(2.5*grid_w,3*grid_h,depth);
		glVertex3f(2.5*grid_w,2*grid_h,depth);

		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(2.5*grid_w,2*grid_h,depth);
		glVertex3f(2.5*grid_w,1*grid_h,depth);
		glVertex3f(3*grid_w,2*grid_h,depth);

		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(3*grid_w,2*grid_h,depth);
		glVertex3f(3.5*grid_w,3*grid_h,depth);
		glVertex3f(2.5*grid_w,3*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(2.5*grid_w,3*grid_h,depth);
		glVertex3f(3*grid_w,2*grid_h,depth);
		glVertex3f(2.5*grid_w,2*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(2.5*grid_w,3*grid_h,depth);
		glVertex3f(1.5*grid_w,2*grid_h,depth);
		glVertex3f(1.5*grid_w,3*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(1.5*grid_w,3*grid_h,depth);
		glVertex3f(0.5*grid_w,2*grid_h,depth);
		glVertex3f(0.5*grid_w,3*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(0.5*grid_w,3*grid_h,depth);
		glVertex3f(-0.5*grid_w,2*grid_h,depth);
		glVertex3f(-0.5*grid_w,3*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-0.5*grid_w,3*grid_h,depth);
		glVertex3f(-1.5*grid_w,2*grid_h,depth);
		glVertex3f(-1.5*grid_w,3*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-1.5*grid_w,3*grid_h,depth);
		glVertex3f(-2.5*grid_w,2*grid_h,depth);
		glVertex3f(-2.5*grid_w,3*grid_h,depth);

		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glVertex3f(-2.5*grid_w,3*grid_h,depth);
		glVertex3f(-3.5*grid_w,3*grid_h,depth);
		glVertex3f(-3*grid_w,2*grid_h,depth);
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-3*grid_w,2*grid_h,depth);
		glVertex3f(-2.5*grid_w,3*grid_h,depth);
		glVertex3f(-2.5*grid_w,2*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-2.5*grid_w,2*grid_h,depth);
		glVertex3f(-2.5*grid_w,1*grid_h,depth);
		glVertex3f(-3*grid_w,2*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-2.5*grid_w,2*grid_h,depth);
		glVertex3f(-1.5*grid_w,3*grid_h,depth);
		glVertex3f(-1.5*grid_w,2*grid_h,depth);

		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glVertex3f(-1.5*grid_w,2*grid_h,depth);
		glVertex3f(-0.5*grid_w,3*grid_h,depth);
		glVertex3f(-0.5*grid_w,2*grid_h,depth);
		
	}
	void draw_border()
	{
		//левая сторона
		glNormal3f(-1,0,0);
		glVertex3f(-0.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,grid_h,0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(-0.5*grid_w,grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,grid_h,-0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(-0.5*grid_w,grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,0,0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(-0.5*grid_w,0,0.5*d);
		glVertex3f(-0.5*grid_w,grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,0,-0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(-0.5*grid_w,0,0.5*d);
		glVertex3f(-0.5*grid_w,0,-0.5*d);
		glVertex3f(-0.5*grid_w,-grid_h,-0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(-0.5*grid_w,-grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,0,0.5*d);
		glVertex3f(-0.5*grid_w,-grid_h,0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(-0.5*grid_w,-grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,-2*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,-2*grid_h,-0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(-0.5*grid_w,-grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,-grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,-2*grid_h,-0.5*d);

		//левая сторона трапеции основания
		glNormal3f(-1,1,0);
		glVertex3f(-0.5*grid_w,-2*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,-3*grid_h,0.5*d);

		glVertex3f(-0.5*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,-3*grid_h,0.5*d);

		//низ трапеции основания
		glNormal3f(0,-1,0);
		glVertex3f(-1.5*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-1.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,-3*grid_h,0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(-0.5*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,-3*grid_h,-0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-0.5*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,-3*grid_h,0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(0.5*grid_w,-3*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,-3*grid_h,-0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(0.5*grid_w,-3*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,-3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(1.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,-3*grid_h,0.5*d);
		glVertex3f(1.5*grid_w,-3*grid_h,0.5*d);

		//правая сторона трапеции основания
		glNormal3f(-1,-1,0);
		glVertex3f(0.5*grid_w,-2*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,-3*grid_h,0.5*d);

		glVertex3f(0.5*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,-3*grid_h,0.5*d);

		//правая сторона основания
		glNormal3f(-1,0,0);
		glVertex3f(0.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,grid_h,0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(0.5*grid_w,grid_h,0.5*d);
		glVertex3f(0.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,grid_h,-0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(0.5*grid_w,grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,grid_h,0.5*d);
		glVertex3f(0.5*grid_w,0,0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(0.5*grid_w,0,0.5*d);
		glVertex3f(0.5*grid_w,grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,0,-0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(0.5*grid_w,0,0.5*d);
		glVertex3f(0.5*grid_w,0,-0.5*d);
		glVertex3f(0.5*grid_w,-grid_h,-0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(0.5*grid_w,-grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,0,0.5*d);
		glVertex3f(0.5*grid_w,-grid_h,0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(0.5*grid_w,-grid_h,0.5*d);
		glVertex3f(0.5*grid_w,-2*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,-2*grid_h,-0.5*d);
		glNormal3f(-1,0,0);
		glVertex3f(0.5*grid_w,-grid_h,0.5*d);
		glVertex3f(0.5*grid_w,-grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,-2*grid_h,-0.5*d);

		//низ правой части верхнего прямоугольника
		glNormal3f(0,-1,0);
		glVertex3f(0.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,2*grid_h,0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(1.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(1.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,2*grid_h,-0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(1.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(1.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(2.5*grid_w,2*grid_h,0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(2.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(2.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,2*grid_h,-0.5*d);

		//правая засечка вниз
		glNormal3f(-1,0,0);
		glVertex3f(2.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(2.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(2.5*grid_w,1*grid_h,0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(2.5*grid_w,1*grid_h,0.5*d);
		glVertex3f(2.5*grid_w,1*grid_h,-0.5*d);
		glVertex3f(2.5*grid_w,2*grid_h,-0.5*d);

		//правая косая плоскость верхнего прямоугольника
		glNormal3f(2,-1,0);
		glVertex3f(2.5*grid_w,1*grid_h,0.5*d);
		glVertex3f(2.5*grid_w,1*grid_h,-0.5*d);
		glVertex3f(3.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(-2,1,0);
		glVertex3f(3.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(3.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(2.5*grid_w,1*grid_h,-0.5*d);

		//верхняя часть верхнего прямоугольника
		glNormal3f(0,1,0);
		glVertex3f(3.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(3.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(2.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(2.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(2.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(3.5*grid_w,3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(2.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(2.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(1.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(1.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(2.5*grid_w,3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(1.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(1.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(0.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(1.5*grid_w,3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(0.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(0.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-0.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(0.5*grid_w,3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(-0.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-1.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-1.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(-1.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-1.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-2.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-2.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-2.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,3*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(-2.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-2.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-3.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-3.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-3.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-2.5*grid_w,3*grid_h,-0.5*d);

		//левая косая плоскость
		glNormal3f(2,1,0);
		glVertex3f(-2.5*grid_w,1*grid_h,0.5*d);
		glVertex3f(-2.5*grid_w,1*grid_h,-0.5*d);
		glVertex3f(-3.5*grid_w,3*grid_h,0.5*d);
		glNormal3f(-2,-1,0);
		glVertex3f(-3.5*grid_w,3*grid_h,0.5*d);
		glVertex3f(-3.5*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-2.5*grid_w,1*grid_h,-0.5*d);

		// левая засечка
		glNormal3f(-1,0,0);
		glVertex3f(-2.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(-2.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-2.5*grid_w,1*grid_h,0.5*d);
		glNormal3f(1,0,0);
		glVertex3f(-2.5*grid_w,1*grid_h,0.5*d);
		glVertex3f(-2.5*grid_w,1*grid_h,-0.5*d);
		glVertex3f(-2.5*grid_w,2*grid_h,-0.5*d);
		
		//низ левой части верхнего прямоугольника
		glNormal3f(0,1,0);
		glVertex3f(-0.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(-0.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,2*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-1.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(-1.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-0.5*grid_w,2*grid_h,-0.5*d);
		glNormal3f(0,1,0);
		glVertex3f(-1.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(-1.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-2.5*grid_w,2*grid_h,0.5*d);
		glNormal3f(0,-1,0);
		glVertex3f(-2.5*grid_w,2*grid_h,0.5*d);
		glVertex3f(-2.5*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-1.5*grid_w,2*grid_h,-0.5*d);
	}
	void draw()
	{
		glPushMatrix();
		glTranslatef(x+dx,y+dy,z+dz);
		glRotatef(rotat_z,0,0,1);
		glRotatef(rotat_y,0,1,0);
		glRotatef(rotat_x,1,0,0);

		glBegin(GL_TRIANGLES);
		back.PaintColor();
		draw_front_back(-0.5*d,0);
		
		if(!lightOff) border.PaintColor();
		draw_border();

		if(!lightOff) front.PaintColor();
		draw_front_back(0.5*d,1);
		
		glEnd();
		glPopMatrix();
	}
};

class LetterG: public Letter
{
	int h;
	int w;
	int d;
	int grid_h;
	int grid_w;
public:
	LetterG(int xx, int yy,int zz, int *f, int * s, int* t, int hh, int ww, int dd): Letter(xx,yy,zz,f,s,t), h(hh), w(ww),d(dd)
	{
		grid_h=h/6;
		grid_w=h/6;
	}
	void draw_front_back(int depth, bool back)
	{
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glBegin(GL_TRIANGLE_STRIP);// основной прямоугольник
		glVertex3f(-2*grid_w,2*grid_h,depth);
		glVertex3f(-1*grid_w,2*grid_h,depth);
		glVertex3f(-2*grid_w,grid_h,depth);
		glVertex3f(-1*grid_w,grid_h,depth);
		glVertex3f(-2*grid_w,0,depth);
		glVertex3f(-1*grid_w,0,depth);
		glVertex3f(-2*grid_w,-grid_h,depth);
		glVertex3f(-1*grid_w,-grid_h,depth);
		glVertex3f(-2*grid_w,-2*grid_h,depth);
		glVertex3f(-1*grid_w,-2*grid_h,depth);
		glEnd();
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glBegin(GL_TRIANGLE_STRIP);// врехний прямоугольник
		glVertex3f(-2*grid_w,3*grid_h,depth);
		glVertex3f(-2*grid_w,2*grid_h,depth);
		glVertex3f(-1*grid_w,3*grid_h,depth);
		glVertex3f(-1*grid_w,2*grid_h,depth);
		glVertex3f(1*grid_w,3*grid_h,depth);
		glVertex3f(1*grid_w,2*grid_h,depth);
		glVertex3f(2*grid_w,3*grid_h,depth);
		glVertex3f(2*grid_w,2*grid_h,depth);
		glEnd();
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glBegin(GL_TRIANGLE_FAN);//правый треугольник
		glVertex3f(2.5*grid_w,2*grid_h,depth);
		glVertex3f(3*grid_w,3*grid_h,depth);
		glVertex3f(2*grid_w,3*grid_h,depth);
		glVertex3f(2*grid_w,2*grid_h,depth);
		glVertex3f(2*grid_w,1*grid_h,depth);
		glEnd();
		glNormal3f(0,0,depth);
		if(back)glNormal3f(0,0,-depth);
		glBegin(GL_TRIANGLE_FAN);//левый треугольник
		glVertex3f(-2*grid_w,3*grid_h,depth);
		glVertex3f(-3*grid_w,3*grid_h,depth);
		glVertex3f(-2*grid_w,2*grid_h,depth);
		glEnd();
		glNormal3f(0,0,-depth);
		if(back)glNormal3f(0,0,depth);
		glBegin(GL_TRIANGLE_FAN);//нижняя трапеция
		glVertex3f(-1.5*grid_w,-3*grid_h,depth);
		glVertex3f(-3*grid_w,-3*grid_h,depth);
		glVertex3f(-2*grid_w,-2*grid_h,depth);
		glVertex3f(-1*grid_w,-2*grid_h,depth);
		glVertex3f(0*grid_w,-3*grid_h,depth);
		glEnd();
	}
	void draw_border()
	{
		glNormal3f(-1,0,0);
		glBegin(GL_TRIANGLE_STRIP);//левая сторона
		glVertex3f(-2*grid_w,2*grid_h,0.5*d);
		glVertex3f(-2*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-2*grid_w,grid_h,0.5*d);
		glVertex3f(-2*grid_w,grid_h,-0.5*d);
		glVertex3f(-2*grid_w,0,0.5*d);
		glVertex3f(-2*grid_w,0,-0.5*d);
		glVertex3f(-2*grid_w,-grid_h,0.5*d);
		glVertex3f(-2*grid_w,-grid_h,-0.5*d);
		glVertex3f(-2*grid_w,-2*grid_h,0.5*d);
		glVertex3f(-2*grid_w,-2*grid_h,-0.5*d);
		glEnd();
		glNormal3f(-1,1,0);
		glBegin(GL_TRIANGLE_STRIP);//левая косая сторона трапеции основания
		glVertex3f(-2*grid_w,-2*grid_h,0.5*d);
		glVertex3f(-2*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(-3*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-3*grid_w,-3*grid_h,-0.5*d);
		glEnd();
		glNormal3f(0,-1,0);
		glBegin(GL_TRIANGLE_STRIP);//низ трапеции основания
		glVertex3f(-3*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-3*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(-2*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-2*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(-1*grid_w,-3*grid_h,0.5*d);
		glVertex3f(-1*grid_w,-3*grid_h,-0.5*d);
		glVertex3f(0*grid_w,-3*grid_h,0.5*d);
		glVertex3f(0*grid_w,-3*grid_h,-0.5*d);
		glEnd();
		glNormal3f(-1,-1,0);
		glBegin(GL_TRIANGLE_STRIP);//правая косая сторона трапеции основания
		glVertex3f(-1*grid_w,-2*grid_h,0.5*d);
		glVertex3f(-1*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(0*grid_w,-3*grid_h,0.5*d);
		glVertex3f(0*grid_w,-3*grid_h,-0.5*d);
		glEnd();
		glNormal3f(-1,0,0);
		glBegin(GL_TRIANGLE_STRIP);//правая сторона основания
		glVertex3f(-1*grid_w,-2*grid_h,-0.5*d);
		glVertex3f(-1*grid_w,-2*grid_h,0.5*d);
		glVertex3f(-1*grid_w,-grid_h,-0.5*d);
		glVertex3f(-1*grid_w,-grid_h,0.5*d);
		glVertex3f(-1*grid_w,0,-0.5*d);
		glVertex3f(-1*grid_w,0,0.5*d);
		glVertex3f(-1*grid_w,grid_h,-0.5*d);
		glVertex3f(-1*grid_w,grid_h,0.5*d);
		glVertex3f(-1*grid_w,2*grid_h,-0.5*d);
		glVertex3f(-1*grid_w,2*grid_h,0.5*d);
		glEnd();
		glNormal3f(0,-1,0);
		glBegin(GL_TRIANGLE_STRIP);//низ верхнего прямоугольника
		glVertex3f(-1*grid_w,2*grid_h,0.5*d);
		glVertex3f(-1*grid_w,2*grid_h,-0.5*d);
		glVertex3f(0*grid_w,2*grid_h,0.5*d);
		glVertex3f(0*grid_w,2*grid_h,-0.5*d);
		glVertex3f(1*grid_w,2*grid_h,0.5*d);
		glVertex3f(1*grid_w,2*grid_h,-0.5*d);
		glVertex3f(2*grid_w,2*grid_h,0.5*d);
		glVertex3f(2*grid_w,2*grid_h,-0.5*d);
		glEnd();
		glNormal3f(-1,0,0);
		glBegin(GL_TRIANGLE_STRIP);//правая засечка вниз
		glVertex3f(2*grid_w,2*grid_h,0.5*d);
		glVertex3f(2*grid_w,2*grid_h,-0.5*d);
		glVertex3f(2*grid_w,1*grid_h,0.5*d);
		glVertex3f(2*grid_w,1*grid_h,-0.5*d);
		glEnd();
		glNormal3f(2,-1,0);
		glBegin(GL_TRIANGLE_STRIP);//правая косая плоскость верхнего прямоугольника
		glVertex3f(2*grid_w,1*grid_h,0.5*d);
		glVertex3f(2*grid_w,1*grid_h,-0.5*d);
		glVertex3f(3*grid_w,3*grid_h,0.5*d);
		glVertex3f(3*grid_w,3*grid_h,-0.5*d);
		glEnd();
		glNormal3f(0,1,0);
		glBegin(GL_TRIANGLE_STRIP);//верхняя часть верхнего прямоугольника
		glVertex3f(3*grid_w,3*grid_h,0.5*d);
		glVertex3f(3*grid_w,3*grid_h,-0.5*d);
		glVertex3f(2*grid_w,3*grid_h,0.5*d);
		glVertex3f(2*grid_w,3*grid_h,-0.5*d);
		glVertex3f(1*grid_w,3*grid_h,0.5*d);
		glVertex3f(1*grid_w,3*grid_h,-0.5*d);
		glVertex3f(0*grid_w,3*grid_h,0.5*d);
		glVertex3f(0*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-1*grid_w,3*grid_h,0.5*d);
		glVertex3f(-1*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-2*grid_w,3*grid_h,0.5*d);
		glVertex3f(-2*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-3*grid_w,3*grid_h,0.5*d);
		glVertex3f(-3*grid_w,3*grid_h,-0.5*d);
		glEnd();
		glNormal3f(-1,-1,0);
		glBegin(GL_TRIANGLE_STRIP);//левая косая плоскость
		glVertex3f(-3*grid_w,3*grid_h,0.5*d);
		glVertex3f(-3*grid_w,3*grid_h,-0.5*d);
		glVertex3f(-2*grid_w,2*grid_h,0.5*d);
		glVertex3f(-2*grid_w,2*grid_h,-0.5*d);
		glEnd();
	}
	void draw()
	{
		glPushMatrix();
		glTranslatef(x+dx,y+dy,z+dz);
		glRotatef(rotat_z,0,0,1);
		glRotatef(rotat_y,0,1,0);
		glRotatef(rotat_x,1,0,0);

		front.PaintColor();
		draw_front_back(0.5*d,0);

		if(!lightOff) border.PaintColor();
		draw_border();

		if(!lightOff) back.PaintColor();
		draw_front_back(-0.5*d,1);
		glPopMatrix();
	}
};