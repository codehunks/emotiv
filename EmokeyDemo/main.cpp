#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<conio.h>

#include<string.h>

using namespace std;
char output[100];

int x=0,y=0,check=0;

void display(void){

	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 600, 0, 600, -1, 1);

	glColor3f(1.0,0.0,0.0);
    
    glBegin(GL_POLYGON);
	    glVertex2d(100,100);
    	glVertex2d(200,100);
    	glVertex2d(200,200);
    	glVertex2d(100,200);
    glEnd();
    glFlush();
	
	/*ifstream fp ("log.txt", ios::in);;
	
	if(fp.is_open()) {
		while(!fp.eof()) {
			fp>> output;
			if(strcmp(output,"D")==0)
				y+=120;
			if(strcmp(output,"L")==0)
				x-=120;
			if(strcmp(output,"R")==0)
				x+=120;
			if(strcmp(output,"U")==0)
				y-=120;
		}
	}
	else 
		cout<<"error";
	fp.close();*/

	

	
}

void func_done()
{
	if(_kbhit() == 1)
	{
	}
	else
	{
	check = _kbhit();
	if(check==1)
	{
		cout<<"Done\n";
		_khbit() = 0;
	}
	}
	
	
}
void updateScreen(void)
{	
	/*glBegin(GL_POLYGON);
	    glVertex2d(100+x,100+y);
    	glVertex2d(200+x,100+y);
    	glVertex2d(200+x,200+y);
    	glVertex2d(100+x,200+y);
    glEnd();
    glFlush();

	glutPostRedisplay();*/
	
	/*if(_kbhit())
	{
		cout<<"Done";
	}*/
	 
	//glutPostRedisplay();
	check = _kbhit();
	if(check==1)
	{
		cout<<"Done\n";
		_khbit() = 0;
	}
	//func_done();
		glutPostRedisplay();
}

void reshape(int w, int h)
{   
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     //gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glOrtho(0.0,800,800,0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
   /*eEvent = EE_EmoEngineEventCreate();
   eState = EE_EmoStateCreate();
   unsigned int userID = -1;
   float secs							= 1;
   
   EE_EngineConnect();	
   
    hData = EE_DataCreate();
	EE_DataSetBufferSizeInSec(secs);*/

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Tic Tac Toe");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	//glutMotionFunc(motion);
    glutIdleFunc(updateScreen);
    
    glutMainLoop(); 
	
   /*EE_EngineDisconnect();
   EE_EmoStateFree(eState);
   EE_EmoEngineEventFree(eEvent);*/	

   return 0;
}
