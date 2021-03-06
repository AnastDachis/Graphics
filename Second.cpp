#define GLUT_DISABLE_ATEXIT_HACK
#include<iostream>
#include <windows.h>
#include <gl/glut.h> 
#include <math.h>
///////////////// 
#include <chrono> 
#include <stdlib.h>
////////////////
#define PI 3.14159 
#define ellipsePoints 256 
#define circlePoints 256
bool visible = true;
using namespace std;

void circles(GLfloat xo,GLfloat yo,GLfloat radius,GLfloat co1,GLfloat co2,GLfloat co3)
{
	int i;
	
	GLfloat angleStep=2*PI/(float)circlePoints;
	GLuint pointsPerQuarter=circlePoints/4;
	GLuint pointsPerOctant=circlePoints/8;
	GLfloat x[circlePoints];
	GLfloat y[circlePoints];
	

	glColor3f(co1,co2,co3);
	glLineWidth(2);
	

	for(i=0;i<=pointsPerOctant;i++)
	{
		//Define points in first quadrant
		x[i]=radius*cos(i*angleStep);
		y[i]=radius*sin(i*angleStep);
		x[pointsPerQuarter-i]=y[i];
		y[pointsPerQuarter-i]=x[i];
		//Define points in second quadrant
		x[pointsPerQuarter+i]=-y[i];
		y[pointsPerQuarter+i]=x[i];
		x[2*pointsPerQuarter-i]=-x[i];
		y[2*pointsPerQuarter-i]=y[i];
		//Define points in third quadrant
		x[2*pointsPerQuarter+i]=-x[i];
		y[2*pointsPerQuarter+i]=-y[i];
		x[3*pointsPerQuarter-i]=-y[i];
		y[3*pointsPerQuarter-i]=-x[i];
		//Define points in fourth quadrant
		x[3*pointsPerQuarter+i]=y[i];
		y[3*pointsPerQuarter+i]=-x[i];
		x[(4*pointsPerQuarter-i)%circlePoints]=x[i];
		y[(4*pointsPerQuarter-i)%circlePoints]=-y[i];
	}
	glBegin(GL_LINE_LOOP);
		for (i=0;i<circlePoints;i++)
		{
			glVertex2f(x[i]+xo,y[i]+yo);
		}
	glEnd();
	
}
////////////////////////////////////////////////
void eclipse() 
{ 
	int i;
	GLfloat angleStep=2*PI/(float)ellipsePoints; 
	GLuint pointsPerQuarter=ellipsePoints;///4; 
	GLfloat x[ellipsePoints]; 
	GLfloat y[ellipsePoints]; 
	GLfloat rx=15; 
	GLfloat ry=10; 
	glClearColor(1,1,1,0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0); 
	glLineWidth(3); 
	glBegin(GL_LINE_LOOP); 
		for(i=0;i<pointsPerQuarter;i++) 
		{ 
			x[i]=rx*cos(i*angleStep); 
			y[i]=ry*sin(i*angleStep); 
		} 
		
		for(i=0;i<ellipsePoints;i++) 
		{ 
			glVertex2f(x[i],y[i]); 
		} 
	glEnd(); 
	
}
////////////////////////////////////////////////
void update(int value) 
{
    glutTimerFunc(5000, update, 0);
    visible = !visible;
}
////////////////////////////////////////////////
void orbit_circle()
{
	int i;
	GLfloat angleStep=2*PI/(float)circlePoints;
	GLuint pointsPerQuarter=circlePoints/4;
	GLuint pointsPerOctant=circlePoints/8;
	GLfloat xo=15; 
	GLfloat yo=10;
	GLfloat radius=1;
	GLfloat x[circlePoints];
	GLfloat y[circlePoints];
	GLfloat rx=15; 
	GLfloat ry=10;

	glColor3f(0,0,1);
	glLineWidth(2);
	for(i=0;i<=pointsPerOctant;i++)
	{
		//Define points in first quadrant
		x[i]=radius*cos(i*angleStep);
		y[i]=radius*sin(i*angleStep);
		x[pointsPerQuarter-i]=y[i];
		y[pointsPerQuarter-i]=x[i];
		//Define points in second quadrant
		x[pointsPerQuarter+i]=-y[i];
		y[pointsPerQuarter+i]=x[i];
		x[2*pointsPerQuarter-i]=-x[i];
		y[2*pointsPerQuarter-i]=y[i];
		//Define points in third quadrant
		x[2*pointsPerQuarter+i]=-x[i];
		y[2*pointsPerQuarter+i]=-y[i];
		x[3*pointsPerQuarter-i]=-y[i];
		y[3*pointsPerQuarter-i]=-x[i];
		//Define points in fourth quadrant
		x[3*pointsPerQuarter+i]=y[i];
		y[3*pointsPerQuarter+i]=-x[i];
		x[(4*pointsPerQuarter-i)%circlePoints]=x[i];
		y[(4*pointsPerQuarter-i)%circlePoints]=-y[i];
	}
	
	for(int j = 0 ; j < ellipsePoints ; j++){
		rx=rx*cos(j*angleStep); 
		ry=ry*sin(j*angleStep);  
	
	glBegin(GL_LINE_LOOP);
	for (i=0;i<circlePoints;i++)
		{
			glVertex2f(x[i]+rx,y[i]+ry);
		}
	glEnd();
	}
}
////////////////////////////////////////////////
////////////////////////////////////////////////

void display()
{	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    
	//if ( visible )
	//{
		
		orbit_circle();
	//}
	//orbit();
	//glutTimerFunc(1000, update, 0);
	
	//glutSwapBuffers();
	//glutPostRedisplay();
	glFlush();	
    
}

int main(int argc, char** argv) 
{ 	
	glutInit(&argc,argv); 
	glutInitWindowPosition(50,50); 
	glutInitWindowSize(640,480); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA); 
	glutCreateWindow("Ellipse drawing"); 
	glMatrixMode(GL_PROJECTION); 
	gluOrtho2D(-32,32,-24,24); 
	eclipse();//?????????? ?????????? //???????????? ???????? ?????? ?????? ????????
	circles(-6,0,4,1,0.8,0); //yellow (1,1,0) // ??????????
	
	//////////////////////////
	
	glutDisplayFunc(display);
	//////////////////////////	
	glutMainLoop(); 
	return 0; 
} 
