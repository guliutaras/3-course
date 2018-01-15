#include "Letter.h"
#include <IrrKlang\irrKlang.h>

#include <process.h>
using namespace irrklang;

ISoundEngine* engine = createIrrKlangDevice();

bool idel;
int rotateS;

int a[]={19,91,64};
int b[]={0,162,90};
int c[]={81,177,124};
Letter* T= new LetterT(0,0,a,b,c,160,40);
Letter* G= new LetterG(50,-50,a,b,c,160,40);

void IdelSpiningClock()
{
	rotateS=rotateS-5; if(rotateS==360) rotateS=0;
	glutPostRedisplay();
}

void IdelSpiningUncloc()
{
	rotateS=rotateS+5; if(rotateS==360) rotateS=0; 
	glutPostRedisplay();
}

void IdelSpiningDimetrial()
{
	G->rotate(5);
	T->rotate(-5);
	glutPostRedisplay();
}

void IdelMusicDance()
{
	T->dancemove();
	G->dancemove();
	glutPostRedisplay();

}

void RenderScene(void)
{

	glClearColor(190.0/255.0, 218.0/255.0, 197.0/255.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT); 
	glPushMatrix();
	glRotatef(rotateS,0,0,1);
	T->draw();
	G->draw();
	glPopMatrix();
	glutSwapBuffers();
}
void ChangeSize1(int w, int h)   
{
	glViewport(0, 0, w, h); // задаем область вывода по размерам окна

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2, w/2, -h/2, h/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();         
}
void Keys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 't':{T->rndcolor();  break;}//случайный цвет для Т
	case 'g':{G->rndcolor(); break;}//случайный цвет для Г
	case 'n':{T->chcolor(a,b,c);G->chcolor(a,b,c); break;}//вернуть цвета
	case 'a':{T->move(-10,0); break;}// влево Т
	case 'd':{T->move(10,0);  break;}// вправо Т
	case 'w':{T->move(0,10); break;}// вверх Т
	case 's':{T->move(0,-10); break;}// вниз Т
	case 'j':{G->move(-10,0); break;}// влево Г
	case 'l':{G->move(10,0);  break;}// вправо Г
	case 'i':{G->move(0,10); break;}// вверх Г
	case 'k':{G->move(0,-10); break;}// вниз Г
	case 'f':{T->normalMove(); rotateS=0; break;}// вернуть все настойки Т
	case 'h':{G->normalMove(); rotateS=0; break;}// вернуть все настойки Г
	case '-':{rotateS=rotateS-5; if(rotateS==360) rotateS=0;  break;}// повороот вокруг цента 2 букв по часовой
	case '0':{rotateS=rotateS+5; if(rotateS==360) rotateS=0; break;}// повороот вокруг цента 2 букв против часовой
	}
	RenderScene();
}
void KeySpec(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:{T->move(-10,0); G->move(-10,0); break;}// влево Т и Г
	case GLUT_KEY_RIGHT:{T->move(10,0); G->move(10,0); break;}// вправо Т и Г
	case GLUT_KEY_UP:{T->move(0,10); G->move(0,10); break;}// вверх Т и Г
	case GLUT_KEY_DOWN:{T->move(0,-10); G->move(0,-10); break;}// вниз Т и Г
	case GLUT_KEY_F2:{T->rotate(-5); break;}//  Т
	case GLUT_KEY_F1:{T->rotate(5); break;}
	case GLUT_KEY_F12:{G->rotate(-5); break;}
	case GLUT_KEY_F11:{G->rotate(5); break;}
	case GLUT_KEY_F5:
		{
			if(idel){glutIdleFunc(NULL); idel=0;engine->setAllSoundsPaused(true); glutIdleFunc(RenderScene);}
			else{glutIdleFunc(IdelSpiningClock);idel=1;}
			break;
		}
	case GLUT_KEY_F6:
		{
			if(idel){glutIdleFunc(NULL); engine->setAllSoundsPaused(true); idel=0;glutIdleFunc(RenderScene);}
			else{glutIdleFunc(IdelSpiningUncloc);idel=1;}
			break;
		}
	case GLUT_KEY_F8:
		{
			if(idel){glutIdleFunc(NULL);engine->setAllSoundsPaused(true); idel=0;glutIdleFunc(RenderScene);}
			else{glutIdleFunc(IdelSpiningDimetrial);idel=1;}
			break;
		}
	case GLUT_KEY_F9:
		{
			if(idel)
			{
				glutIdleFunc(NULL);

				engine->setAllSoundsPaused(true);
				idel=0;
				glutIdleFunc(RenderScene);
			}
			else
			{
				engine->play2D("madness.mp3",true);
				glutIdleFunc(IdelMusicDance);
				idel=1;
			}
			break;
		}
	}
	RenderScene();
}

int main(int argc, char* argv[])
{
	rotateS=0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Лабораторна работа №1 Гулий Тарас");
	glutSpecialFunc(KeySpec);
	glutKeyboardFunc(Keys);
	glutReshapeFunc(ChangeSize1);
	glutDisplayFunc(RenderScene);
	glutMainLoop(); // Цикл сообщений графического окна
}
