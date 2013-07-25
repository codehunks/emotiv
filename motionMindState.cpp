#include<windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <stdlib.h>
#include<iostream>
#include<conio.h>
#include<sstream>
#include<map>

#include "edk.h"
#include "edkErrorCode.h"
#include "EmoStateDLL.h"

#pragma comment(lib, "edk.lib")
#pragma comment(lib, "glut32.lib")

#define PI 3.1418

EmoStateHandle eState;
DataHandle hData;
EmoEngineEventHandle eEvent;

bool oneTime = true;
bool outOfBound = false;
float currX = 0,currY = 0;
double maxRadius = 10000;
float xmax = 0, ymax = 0;
float preX = 0, preY = 0;
int incOrDec = 10;
float oldXVal =0, oldYVal = 0;
unsigned long pass = 0,globalElapsed = 0;
int count = 0;
float x;

bool readytocollect					= false;

float affEngegement=0.0, affFrus=0.0, affMed=0.0, affExcitement=0.0, affSmile=0.0;

GLsizei MOUSEx=0, MOUSEy=0;
GLfloat SIDE=50;
float COLOR[][3] = {
	{1,0,0},
	{0,1,0},
	{0,0,1},
	{1,1,1},
	{1,1,0.2}

};
GLfloat color1[3];

EE_DataChannel_t targetChannelList[] = {
		ED_COUNTER,
		ED_AF3, ED_F7, ED_F3, ED_FC5, ED_T7, 
		ED_P7, ED_O1, ED_O2, ED_P8, ED_T8, 
		ED_FC6, ED_F4, ED_F8, ED_AF4, ED_GYROX, ED_GYROY, ED_TIMESTAMP, 
		ED_FUNC_ID, ED_FUNC_VALUE, ED_MARKER, ED_SYNC_SIGNAL
	};
	

void affective(void)
{	unsigned int userID					= 0;
	const unsigned short composerPort	= 1726;
	
	unsigned int datarate				= 0;
	
	int option							= 0;
	int state							= 0;
	
	
	state = EE_EngineGetNextEvent(eEvent);
	EE_Event_t eventType;

	if (state == EDK_OK) {

		eventType = EE_EmoEngineEventGetType(eEvent);
		EE_EmoEngineEventGetUserId(eEvent, &userID);
		EE_EmoEngineEventGetEmoState(eEvent, eState);

		// Log the EmoState if it has been updated
		if (eventType == EE_UserAdded) {
			std::cout << "User added";
			EE_DataAcquisitionEnable(userID,true);
			readytocollect = true;
		}
			
		//std::cout<<"recollect & event is "<<readytocollect<<eventType;
		if (readytocollect && (eventType == EE_EmoStateUpdated)) {
									
			EE_DataUpdateHandle(0, hData);

			unsigned int nSamplesTaken=0;
			EE_DataGetNumberOfSample(hData,&nSamplesTaken);
		
			//std::cout << "Updated " << nSamplesTaken << std::endl;
						

			if (nSamplesTaken != 0  ) {

				double* data = new double[nSamplesTaken];
				for (int sampleIdx=0 ; sampleIdx<(int)nSamplesTaken ; ++ sampleIdx) {
					for (int i = 0 ; i<sizeof(targetChannelList)/sizeof(EE_DataChannel_t) ; i++) {

						EE_DataGet(hData, targetChannelList[i], data, nSamplesTaken);
						//ofs << data[sampleIdx] << ",";
					}	
					//ofs << std::endl;
				}
				delete[] data;							
			}
						
			affEngegement = ES_AffectivGetEngagementBoredomScore(eState);
			affFrus = ES_AffectivGetFrustrationScore(eState);
			affMed = ES_AffectivGetMeditationScore(eState);
			affExcitement = ES_AffectivGetExcitementShortTermScore(eState);
			//printf("Exc:%f, Fru:%f, Med:%f, Eng:%f\n",affExcitement,affFrus,affMed,affEngegement);
			affSmile = ES_ExpressivGetSmileExtent(eState);
			//ofs2 <<affEngegement<<","<<	affFrus<<","<<affMed<<","<<affExcitement<<","<<std::endl;

			}
		}
			//Sleep(100);
}


void drawSquare1()
{	if (affSmile > 0.5)
	{
		std::cout <<" You're smiling "; 
		glColor3fv(COLOR[4]);
        //glColor3fv(color1);
		glBegin(GL_POLYGON);
        glVertex3f(MOUSEx, MOUSEy,0);
        glVertex3f(MOUSEx+SIDE, MOUSEy,0);
        glVertex3f(MOUSEx+SIDE, MOUSEy+SIDE,0);
        glVertex3f(MOUSEx, MOUSEy+SIDE,0);
	}
    else {
	/*if(affExcitement > 0.7 )
		glColor3fv(COLOR[2]); //GLfloat COLOR[3] = {0,0,1}; //blue for excitement
	else if(affFrus >0.7)
		glColor3fv(COLOR[0]); //GLfloat COLOR[3] = {1,0,0}; //red for frustration
	else if(affEngegement > 0.5)
		glColor3fv(COLOR[1]); //GLfloat COLOR[3] = {0,1,0}; //green for engagement/meditation
	else
		glColor3fv(COLOR[3]); //GLfloat COLOR[3] = {1,0,1}; //white
		*/
	color1[0]=affFrus;
	color1[1]=affEngegement;
	color1[2]=affExcitement;
	glColor3fv(color1);
    
	
	glBegin(GL_POINTS);
	glVertex2i(MOUSEx, MOUSEy);}

	//printf("this is %d %d", MOUSEx, MOUSEy);
    glEnd();
    glFlush();
}   

void display(void)
{   
    //glClearColor (0.0,0.0,0.0,1.0);
    //glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 
    drawSquare1();
    glFlush();
}

void updateScreen(void)
{	affective();
	int gyroX = 0,gyroY = 0;
    EE_HeadsetGetGyroDelta(0,&gyroX,&gyroY);
	MOUSEx += gyroX;
	MOUSEy += gyroY;
	
	//printf ("gyrox is %d gyroy is %d ",gyroX, gyroY);
	glutPostRedisplay();
}

/*void updateDisplay(void)
{	  
   int gyroX = 0,gyroY = 0;
   EE_HeadsetGetGyroDelta(0,&gyroX,&gyroY);
   xmax += gyroX;
   ymax += gyroY;

   if( outOfBound )
   {
	   if( preX != gyroX && preY != gyroY )
	   {
		   xmax = currX;
		   ymax = currY;
	   }
   }

   double val = sqrt((float)(xmax*xmax + ymax*ymax));
  
    std::cout <<"xmax : " << xmax <<" ; ymax : " << ymax << std::endl;

   
   if( val >= maxRadius )
   {
	   changeXY(1);	
	   outOfBound = true;
	   preX = gyroX;
	   preY = gyroY;
   }
   else
   {		
	   outOfBound = false;
		if(oldXVal == gyroX && oldYVal == gyroY)
		{
			++count;
			if( count > 10 )
			{									
				changeXY(0);
			}
		}
		else
		{
			count = 0;
			currX = xmax;
			currY = ymax;
			oldXVal = gyroX;
			oldYVal = gyroY;			
		}
   }
   Sleep(15);
   glutPostRedisplay(); 
}*/
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
void setX(int x)
{
    MOUSEx=x;
}

void setY(int y)
{
    MOUSEy=y;
}

void motion (int x, int y)
{
    //  Print the mouse drag position
    //printf ("Mouse Drag Position: %d, %d.\n", x, y);
	setX(x);
    setY(y);
	glutPostRedisplay();
}
/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
   eEvent = EE_EmoEngineEventCreate();
   eState = EE_EmoStateCreate();
   unsigned int userID = -1;
   float secs							= 1;
   
   EE_EngineConnect();	
   
    hData = EE_DataCreate();
	EE_DataSetBufferSizeInSec(secs);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Moving squares");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutIdleFunc(updateScreen);
    glutMainLoop(); 
      
   EE_EngineDisconnect();
   EE_EmoStateFree(eState);
   EE_EmoEngineEventFree(eEvent);	

   return 0;
}