#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<process.h>

#include<string.h>

using namespace std;
char output[100];

int x=0,y=0,z=1,ctr=0,check=0;

void blinkCursor() {
if(z==1)
	glColor3f(1.0,0.0,0.0);
else
	glColor3f(0.0,0.0,0.0);

glBegin(GL_POLYGON);
	    glVertex2d(0+x,0+y);
    	glVertex2d(200+x,0+y);
    	glVertex2d(200+x,200+y);
    	glVertex2d(0+x,200+y);
    glEnd();
	glFlush();

}

void display(void){

	/*glClearColor(0.0,0.0,0.0,0.0);
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
    glFlush();*/
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 600, 0, 600, -1, 1);

	blinkCursor();
	
}


void updateScreen(void)
{	
	char c;
	ctr++;
	if(ctr%150==0){
		ctr=0;
		z*=-1;
	}
		if(_kbhit())
		{
			c = getch();
			cout<<c<<endl;
			if( c == 'd' || c == 'D')
			 {
				 x+= 200;
			 }
			 if( c == 'a' || c == 'A')
			 {
				 x-= 200;
			 }
			 if( c == 'w' || c == 'W')
			 {
				 y+= 200;
			 }
			 if( c == 's' || c == 'S')
			 {
				 y-= 200;
			 }
			 if( c == 'X' || c == 'x')
			 {
				 exit(0);
			 }
	}

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
