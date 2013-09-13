#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <stdlib.h>
#include<iostream>
#include<conio.h>
#include<process.h>
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
int visited[10]={0,0,0,0,0,0,0,0,0,0},turn=1, flagvar=-1,ctr=0,flagwin=1;
int drawn[10]={0,0,0,0,0,0,0,0,0,0};

int startX,startY,endX,endY,row,col;


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
			//printf("Smile:%f",affSmile);
			//ofs2 <<affEngegement<<","<<	affFrus<<","<<affMed<<","<<affExcitement<<","<<std::endl;

			}
		}
			//Sleep(100);
}
void drawCrossMark(int startX,int startY,int endX,int endY) {
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_LINES);
    	glVertex2d(startX,startY);
    	glVertex2d(endX,endY);
    glEnd();

    glBegin(GL_LINES);
    	glVertex2d(startX+200,startY);
    	glVertex2d(endX-200,endY);
    glEnd();
}

void drawBigO(int startX, int startY){
	glColor3f(0.0,1.0,0.0);

	glBegin(GL_POLYGON);
		for(double i=0;i<2*PI;i+=PI/6)
			glVertex3f(startX -100 + cos(i)*50,startY -100 + sin(i)*50,0.0);
    glEnd();
}

void checkBoxNumber(){
	int col_num=0,row_num=0;
	//int MOUSEx = 350;
	//int MOUSEy = 450;
	if (MOUSEx > 0 && MOUSEx < 200)
	{
		col_num = 1;
	}
	else if (MOUSEx > 200 && MOUSEx < 400)
	{
		col_num = 2;
	}
	else if (MOUSEx > 400 && MOUSEx < 600)
	{
		col_num = 3;
	}
		if(MOUSEy > 0 && MOUSEy < 200)
		{
			row_num = 1;
		}
		else if(MOUSEy > 200 && MOUSEy < 400)
		{
			row_num = 4;
		}
		else if(MOUSEy > 400 && MOUSEy < 600)
		{
			row_num = 7;
		}
	
	int box_num =  col_num+row_num-1;
	
	row = ceil(box_num/3.0);
	col = box_num-((row-1)*3);

	startX = (row-1)*200;
	startY = (col-1)*200; 
	endX = (startX+200);
	endY = (startY+200);
	
	if(visited[box_num]!=1) {
		if(turn==1) {
		//drawCrossMark(startY, startX, endY,endX);
		turn*= -1;
		visited[box_num]=1;
	}
    else{
    	//drawBigO(endX,endY);
    	turn*= -1;
		visited[box_num]=1;
    }
	drawn[box_num] = turn;
	}
	if(drawn[1]==drawn[4] && drawn[4]==drawn[7] && drawn[1]!=0)
		flagvar = 1;
	else if(drawn[2]==drawn[5] && drawn[5]==drawn[8] && drawn[2]!=0)
		flagvar = 1;
	else if(drawn[3]==drawn[6] && drawn[6]==drawn[9] && drawn[3]!=0)
		flagvar = 1;
	else if(drawn[1]==drawn[2] && drawn[2]==drawn[3] && drawn[1]!=0)
		flagvar = 1;
	else if(drawn[4]==drawn[5] && drawn[5]==drawn[6] && drawn[4]!=0)
		flagvar = 1;
	else if(drawn[7]==drawn[8] && drawn[8]==drawn[9] && drawn[7]!=0)
		flagvar = 1;
	else if(drawn[1]==drawn[5] && drawn[5]==drawn[9] && drawn[5]!=0)
		flagvar = 1;
	else if(drawn[3]==drawn[5] && drawn[5]==drawn[7] && drawn[7]!=0)
		flagvar = 1;
	for(int i=1;i<10;i++){
		if(visited[i]!=1){
			ctr=0;
			break;}
		else
			ctr++;
	}
	if(ctr==9)
		flagvar=1;
}

void drawnState() {
	for(int i=1;i<10;i++) {
		row = ceil(i/3.0);
		col = i-((row-1)*3);

		startX = (row-1)*200;
		startY = (col-1)*200; 
		endX = (startX+200);
		endY = (startY+200);
		if(drawn[i]<0)
			drawBigO(endY,endX);
		if(drawn[i]>0)
			drawCrossMark(startY, startX, endY,endX);
	}
}

void drawSquare1()
{	if (affSmile > 0.06)
	{
		//std::cout <<" You're smiling "; 
		glColor3fv(COLOR[4]);
		checkBoxNumber();
	}
    
	
	color1[0]=affFrus;
	color1[1]=affEngegement;
	color1[2]=affExcitement;
	glColor3fv(color1);
    
	
	glBegin(GL_POLYGON); 
		glVertex3f(MOUSEx-10,MOUSEy-10,0);
    	glVertex3f(MOUSEx+10,MOUSEy-10,0);
		glVertex3f(MOUSEx+10,MOUSEy+10,0);
    	glVertex3f(MOUSEx-10,MOUSEy+10,0);
  
    glEnd();
	//glFlush();
	
}   



void drawBoard() {
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 600, 0, 600, -1, 1);

	glColor3f(0.0,0.0,0.0);
    
    glBegin(GL_POLYGON);
	    glVertex3f(0,0,0);
    	glVertex3f(600,0,0);
    	glVertex3f(600,600,0);
    	glVertex3f(0,600,0);
    glEnd();

	glColor3f(0.0,0.0,1.0);

    glBegin(GL_LINES);
    	glVertex2d(200,0.0);
    	glVertex2d(200,600.0);
    glEnd();

    glBegin(GL_LINES);
    	glVertex2d(400,0.0);
    	glVertex2d(400,600.0);
    glEnd();

	glBegin(GL_LINES);
    	glVertex2d(0,200.0);
    	glVertex2d(600,200.0);
    glEnd();

    glBegin(GL_LINES);
    	glVertex2d(0,400.0);
    	glVertex2d(600,400.0);
    glEnd();

    //drawCrossMark(200,200,400,0);
    //drawBigO(400,400);
}
void drawText(const char *msg){
	glRasterPos2f(-1,-1);
	while(*msg){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*msg);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*msg++);
	}
	//glutBitmapString(GLUT_BITMAP_HELVETICA_12,msg);
}
void youwin(){
	glColor3f(0.4,0.6,0.8);
	if(ctr==9){
		drawText("Match Drawn");
				if (flagwin == 1){ 
		
		std::cout<<"\nMatch Drawn";

			flagwin = 2;
		}
	}
	else{
		if (flagwin == 1){ 
		std::cout<<"\nYou Win !";
		flagwin = 2;
		}
		drawText("You Win ! ");
		
	}
	drawnState();
	glFlush();
	//getch();
	//exit(0);
}

void display(void)
{   
    //glClearColor (0.0,0.0,0.0,1.0);
    //glClear (GL_COLOR_BUFFER_BIT);
    if(flagvar==-1){
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		drawBoard();
		drawnState();
		drawSquare1();
		glFlush();
		glutPostRedisplay();
		glutSwapBuffers();
	}
	if(flagvar==1){
		glLoadIdentity();
		drawBoard();
		drawnState();
		youwin();
		glFlush();

	}
}

void updateScreen(void)
{	affective();
	int gyroX = 0,gyroY = 0;
    EE_HeadsetGetGyroDelta(0,&gyroX,&gyroY);
	MOUSEx += gyroX/20;
	MOUSEy += gyroY/20;
	if(MOUSEx<10)
		MOUSEx=10;
	if(MOUSEx>590)
		MOUSEx=590;
	if(MOUSEy<10)
		MOUSEy=10;
	if(MOUSEy>590)
		MOUSEy=590;
	
	//printf ("gyrox is %d gyroy is %d ",gyroX, gyroY);
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
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Tic Tac Toe");
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutIdleFunc(updateScreen);
    glutReshapeFunc(reshape);
    glutMainLoop(); 
	/*INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx=0;
	input.mi.dy=0;
	input.mi.dwFlags=(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE|MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP);
	input.mi.mouseData=0;
	input.mi.dwExtraInfo=NULL;
	SendInput(1,&input,sizeof(INPUT));
	*/

	/*HWND h = (hwnd of window);
	WORD mouseX = 10;
	WORD mouseY = 10;
	PostMessage(hwnd,WM_LBUTTONDOWN,0,MAKELPARAM(mouseX,mouseY));
  */
   EE_EngineDisconnect();
   EE_EmoStateFree(eState);
   EE_EmoEngineEventFree(eEvent);	

   return 0;
}
