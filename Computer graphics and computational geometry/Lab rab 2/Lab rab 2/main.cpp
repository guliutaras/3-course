#include "Letters.h"

int fillMenu, shrinkMenu, mainMenu, colorMenu;
#define PI 3.141592653

bool pshe=0;
bool wah=0;
int menuFlag = 0;	
int light_sample = 0;

int a[]={19,91,64};
int b[]={0,162,90};
int c[]={81,177,124};

int a1[]={205, 85, 85};
int b1[]={139, 58, 58};
int c1[]={255, 106, 106};


int rotat_y=0;
int rotat_x=0;

Letter* T= new LetterT(0,0,0,a,b,c,140,120,20);
Letter* G= new LetterG(10,-10,0,a1,b1,c1,120,120,20);

void init()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
}

void ChangeSize2(int width, int height)    
{

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45,(GLfloat)width/(GLfloat)height,(float)1,(float)100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	 
}
void RenderScene (void)
{
	//
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0,0,-300);
	GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	if (light_sample == 1)
	{
		// направленный источник света
		GLfloat light0_diffuse[] = {0.4, 0.7, 0.2};
		GLfloat light0_direction[] = {0.0, 0.0,(GLfloat)1, 0.0};
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
	}
	if (light_sample == 2)
	{
		// точечный источник света
		// убывание интенсивности с расстоянием
		// отключено (по умолчанию)
		GLfloat light1_diffuse[] = {0.4, 0.7, 0.2};
		GLfloat light1_position[] = {50.0, 50.0, 100.0, 1.0};
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	}
	if (light_sample == 3)
	{
		// точечный источник света
		// убывание интенсивности с расстоянием
		// задано функцией f(s) = 1.0 / (0.01 * s + 0.015)
		GLfloat light2_diffuse[] = {0.4, 0.7, 0.2};
		GLfloat light2_position[] = {-100.0, -100.0, 100.0, 1.0};
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.015);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
	}
	if (light_sample == 4)
	{
		// прожектор
		// убывание интенсивности с расстоянием
		// отключено (по умолчанию)
		// половина угла при вершине 30 градусов
		// направление на центр плоскости
		GLfloat light3_diffuse[] = {0.4, 0.7, 0.2};
		GLfloat light3_position[] = {0.0, 0.0, 200.0, 1.0};
		GLfloat light3_spot_direction[] = {0.0, 0.0, -1.0};
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
		glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
	}
	if (light_sample == 5)
	{
		// прожектор
		// убывание интенсивности с расстоянием
		// отключено (по умолчанию)
		// половина угла при вершине 30 градусов
		// направление на центр плоскости
		// включен расчет убывания интенсивности для прожектора
		GLfloat light4_diffuse[] = {0.4, 0.7, 0.2};
		GLfloat light4_position[] = {100.0, 100.0, 100.0, 1.0};
		GLfloat light4_spot_direction[] = {-1.0, -1.0, -1.0};
		glEnable(GL_LIGHT4);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
		glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light4_spot_direction);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);
	}
	glRotatef(rotat_y,0,1,0);
	glRotatef(rotat_x,1,0,0);
	T->draw();
	G->draw();
	glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
	glPopMatrix();
	glutSwapBuffers();
}

void Keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':{T->move(-10,0,0); break;}// влево Т
	case 'd':{T->move(10,0,0);  break;}// вправо Т
	case 'w':{T->move(0,10,0); break;}// вверх Т
	case 's':{T->move(0,-10,0); break;}// вниз Т
	case 'r':{T->move(0,0,-10); break;}// вглубь Т
	case 'f':{T->move(0,0,10); break;}// на себя Т
	case 'j':{G->move(-10,0,0); break;}// влево Г
	case 'l':{G->move(10,0,0);  break;}// вправо Г
	case 'i':{G->move(0,10,0); break;}// вверх Г
	case 'k':{G->move(0,-10,0); break;}// вниз Г
	case 'y':{G->move(0,0,-10); break;}// вглубь Г
	case 'h':{G->move(0,0,10); break;}// на себя Г
	case 'e':{T->normalMove();rotat_y=0; rotat_x=0; break;}// нормализировать Т
	case 'u':{G->normalMove();rotat_y=0; rotat_x=0; break;}// нормализировать Г
	case 'b':{rotat_y=rotat_y+5; if(rotat_y==360) rotat_y=0; break;}
	case 'n':{rotat_x=rotat_x+5; if(rotat_x==360) rotat_x=0; break;}
	case '0':{if(pshe){light_sample=0;}break;}
	case '1':{if(pshe){light_sample=1;}break;}
	case '2':{if(pshe){light_sample=2;}break;}
	case '3':{if(pshe){light_sample=3;}break;}
	case '4':{if(pshe){light_sample=4;}break;}
	case '5':{if(pshe){light_sample=5;}break;}
	}
	RenderScene();
}

void KeySpec(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:{T->rotate_x(-5); break;}
	case GLUT_KEY_F2:{T->rotate_x(5); break;}
	case GLUT_KEY_F3:{T->rotate_y(-5); break;}
	case GLUT_KEY_F4:{T->rotate_y(5); break;}
	case GLUT_KEY_F5:{T->rotate_z(-5);break;}
	case GLUT_KEY_F6:{T->rotate_z(5);break;}
	case GLUT_KEY_F7:{G->rotate_x(-5);break;}
	case GLUT_KEY_F8:{G->rotate_x(5);break;}
	case GLUT_KEY_F9:{G->rotate_y(-5); break;}
	case GLUT_KEY_F10:{G->rotate_y(5); break;}
	case GLUT_KEY_F11:{G->rotate_z(-5); break;}
	case GLUT_KEY_F12:{G->rotate_z(5); break;}
	}
	RenderScene();
}
void processMenuStatus(int status, int x, int y) {
	if (status == GLUT_MENU_IN_USE)
		{menuFlag = 1;
	}
	else{
		menuFlag = 0;}
}
void processMainMenu(int option) {
	switch(option){
	case 1:
		pshe=false;
		wah=false;
		glClearColor(190.0/255.0, 218.0/255.0, 197.0/255.0, 0.0);
		glDisable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		T->lightOff=0;
		G->lightOff=0;
		glutPostRedisplay();
		break;
	case 2:
		pshe=true;
		wah=true;
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glEnable(GL_LIGHTING);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glEnable(GL_NORMALIZE);
		T->lightOff=1;
		G->lightOff=1;
		glutPostRedisplay();
		break;
	}
}
void createPopupMenus() {
	mainMenu = glutCreateMenu(processMainMenu);
	glutAddMenuEntry("Без освещения", 1);
	glutAddMenuEntry("С освещением", 2);
	// прикрепить меню к правой кнопке
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//статус активности меню
	glutMenuStatusFunc(processMenuStatus);
}

int main(int argc, char* argv[])
{
	pshe=false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Лабораторна работа №2 Гулий Тарас");
	if(wah){init();}
	glutKeyboardFunc(Keys);
	glutSpecialFunc(KeySpec);
	glutReshapeFunc(ChangeSize2);
	glutDisplayFunc(RenderScene);
	createPopupMenus();
	glutMainLoop(); 
}