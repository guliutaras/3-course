#include <glut.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<windows.h>
#include <ctime>
#include<math.h>

void circle(int R ,int dx, int dy)
{
	int x=0;
	int y=R;
	int d=3-2*R;
	glBegin(GL_QUADS);
	while(x<=y)
	{
		glVertex2f(x+dx,y+dy);
		glVertex2f(y+dx,x+dy);
		glVertex2f(x+dx,-y+dy);
		glVertex2f(y+dx,-x+dy);
		glVertex2f(-x+dx,-y+dy);
		glVertex2f(-y+dx,-x+dy);
		glVertex2f(-x+dx,y+dy);
		glVertex2f(-y+dx,x+dy);
		if(d<0) d+=4*x+6;
		else{d+=4*x-4*y+10; y--;}
		x++;
	}
	glEnd();
}

struct Color
{
	int R;
	int G;
	int B;
	Color(int* a):R(a[0]), G(a[1]), B(a[2]){}
	Color(Color& C){R=C.R; G=C.G; B=C.B;}
	void PaintColor(){glColor3ub(R,G,B);}
	void ChColor(int r, int g, int b){R=r;G=g;B=b;}
};


class Letter
{
protected:
	bool dance;
	int rotat;
	int x;
	int y;
	Color first;
	Color second;
	Color third;
	int dy;
	int dx;
public:
	Letter(int xx, int yy, int *f, int * s, int* t): x(xx), y(yy), dx(0), dy(0),rotat(0), first(f), second(s), third(t), dance(0){}
	virtual void draw(){return;}
	void rndcolor(){srand(time(0)); first.ChColor(rand()%255,rand()%255,rand()%255); second.ChColor(rand()%255,rand()%255,rand()%255); third.ChColor(rand()%255,rand()%255,rand()%255); srand(time(0)); }
	void chcolor(int* a, int* b, int *c){ first.ChColor(a[0],a[1],a[2]); second.ChColor(b[0],b[1],b[2]); third.ChColor(c[0],c[1],c[2]);}
	void rotate(int r){rotat=rotat+r; if(rotat==360) rotat=0;}
	void dancemove()
	{
		if(rotat<45&&dance==1) {rotat=rotat+3;  dx=dx+5; dy=dy-5;} 
		else
		{
			dance=0; 
			if(rotat>-45&&dance==0) {rotat=rotat-3; dx=dx-5; dy=dy+5;}
			else dance=1;
		}
	
	}
	void move(int xx, int yy){dx=dx+xx; dy=dy+yy;}
	void normalMove(){dx=0; dy=0; rotat=0;}
};


class LetterT: public Letter
{
	int h;
	int w;
public:
	LetterT(int xx, int yy, int *f, int * s, int* t, int hh, int ww): Letter(xx,yy,f,s,t), h(hh), w(ww){} 
	void draw()
	{
		glPushMatrix();
		glTranslatef(x+dx,y+dy,0);
		glRotatef(rotat,0,0,1);
		GLfloat tbasel=-w/2, tbaser=w/2, tbaseb=-h/2, tbaset=h/2;
		for(int i=10; i>-1; i=i-5)
		{
			if(i==0) first.PaintColor();
			if(i==5) second.PaintColor();
			if(i==10) third.PaintColor();
			glBegin(GL_QUADS);//основа т
			glVertex2f(tbasel-i,tbaseb);
			glVertex2f(tbasel-i,tbaset);
			glVertex2f(tbaser+i,tbaset);
			glVertex2f(tbaser+i,tbaseb);
			glEnd();   
			glBegin(GL_QUADS);// шапка т
			glVertex2f(tbasel*4,tbaset-i);
			glVertex2f(tbasel*4,tbaset+w+i);
			glVertex2f(tbaser*4,tbaset+w+i);
			glVertex2f(tbaser*4,tbaset-i);
			glEnd();
			circle(tbaser+i,0,tbaseb);
			circle(tbaser+i,tbasel*4,tbaset+w/2);
			circle(tbaser+i,tbaser*4,tbaset+w/2);
		}
		glPopMatrix();
	}
};
class LetterG: public Letter
{
	int h;
	int w;
public:
	LetterG(int xx, int yy, int *f, int * s, int* t, int hh, int ww): Letter(xx,yy,f,s,t), h(hh), w(ww){} 
	void draw()
	{
		
		glPushMatrix();
		glTranslatef(x+dx,y+dy,0); 
		glRotatef(rotat,0,0,1);
		GLfloat tbasel=-w/2, tbaser=w/2, tbaseb=-h/2, tbaset=h/2;
		for(int i=10; i>-1; i=i-5)
		{
			if(i==0) first.PaintColor();
			if(i==5) second.PaintColor();
			if(i==10) third.PaintColor();
			glBegin(GL_QUADS);//основа г
			glVertex2f(tbasel-i,tbaseb);
			glVertex2f(tbasel-i,tbaset);
			glVertex2f(tbaser+i,tbaset);
			glVertex2f(tbaser+i,tbaseb);
			glEnd();   
			glBegin(GL_QUADS);// шапка г
			glVertex2f(0,tbaset-w/2-i);
			glVertex2f(0,tbaset+w/2+i);
			glVertex2f(tbaser*6,tbaset+w/2+i);
			glVertex2f(tbaser*6,tbaset-w/2-i);
			glEnd();
			circle(tbaser+i,0,tbaseb);
			circle(tbaser+i,0,tbaset);
			circle(tbaser+i,tbaser*6,tbaset);
		}
		glPopMatrix();
	}
};





