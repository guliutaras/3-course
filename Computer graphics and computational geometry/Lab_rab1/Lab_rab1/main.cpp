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
	glViewport(0, 0, w, h); // ������ ������� ������ �� �������� ����

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
	case 't':{T->rndcolor();  break;}//��������� ���� ��� �
	case 'g':{G->rndcolor(); break;}//��������� ���� ��� �
	case 'n':{T->chcolor(a,b,c);G->chcolor(a,b,c); break;}//������� �����
	case 'a':{T->move(-10,0); break;}// ����� �
	case 'd':{T->move(10,0);  break;}// ������ �
	case 'w':{T->move(0,10); break;}// ����� �
	case 's':{T->move(0,-10); break;}// ���� �
	case 'j':{G->move(-10,0); break;}// ����� �
	case 'l':{G->move(10,0);  break;}// ������ �
	case 'i':{G->move(0,10); break;}// ����� �
	case 'k':{G->move(0,-10); break;}// ���� �
	case 'f':{T->normalMove(); rotateS=0; break;}// ������� ��� �������� �
	case 'h':{G->normalMove(); rotateS=0; break;}// ������� ��� �������� �
	case '-':{rotateS=rotateS-5; if(rotateS==360) rotateS=0;  break;}// �������� ������ ����� 2 ���� �� �������
	case '0':{rotateS=rotateS+5; if(rotateS==360) rotateS=0; break;}// �������� ������ ����� 2 ���� ������ �������
	}
	RenderScene();
}
void KeySpec(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:{T->move(-10,0); G->move(-10,0); break;}// ����� � � �
	case GLUT_KEY_RIGHT:{T->move(10,0); G->move(10,0); break;}// ������ � � �
	case GLUT_KEY_UP:{T->move(0,10); G->move(0,10); break;}// ����� � � �
	case GLUT_KEY_DOWN:{T->move(0,-10); G->move(0,-10); break;}// ���� � � �
	case GLUT_KEY_F2:{T->rotate(-5); break;}//  �
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
	glutCreateWindow("����������� ������ �1 ����� �����");
	glutSpecialFunc(KeySpec);
	glutKeyboardFunc(Keys);
	glutReshapeFunc(ChangeSize1);
	glutDisplayFunc(RenderScene);
	glutMainLoop(); // ���� ��������� ������������ ����
}
