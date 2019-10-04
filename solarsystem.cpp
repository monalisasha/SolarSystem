/* Name: Monalisa Sha
   ID : 300001469
   Class : CSCI 272
   Project Name: Solar System
*/

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>
#define PI 3.14
using namespace std;


bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
const GLfloat yellow[]={0.7f,0.2f,0.0f,1.0f};
GLfloat sx=0.2,sy=0.2,sz=0.2;

float angleMoon=0.0, angleEarth=0.0,angleSun=0.0, angleJupiter=0.0;
GLfloat sc[8]={5.295,5.40,5.8,4.60,3.5,2.5,1.5,1.2};
bool start_flag = false;
double ang=2*PI/300;
double angular=2*PI/50;


/* GLUT callback Handlers */
static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
            glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
          glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,1,0.1f, 100.0f);
 }

//For drawing the orbit for the solar system
void orbit()
{
    glColor3f(1.0, 1.0, 1.0);
    int i=0;
    for(i=0;i<8;i++){
    glPushMatrix();
    if(i==10)
    {glRotatef(45,1.0,0.0,0.0);}
    else
    {glRotatef(63,1.0,0.0,0.0);}
    glScalef(sc[i],sc[i],sc[i]);
    glBegin(GL_POINTS);
    double ang1=0.0;
      int i=0;
      for(i=0;i<300;i++)
      {glVertex2d(cos(ang1),sin(ang1));
       ang1+=ang;  }
    glEnd();
    glPopMatrix();
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    orbit();
    glLoadIdentity();

    gluLookAt(0,10,10,0.0,0.0,0.0,0.0,5.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

       //Created Sun
       glPushMatrix();
       glColor3f(1.0, 1.0 ,0.0);
       glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,yellow);
       glutSolidSphere(0.75,50,50);
       glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,light_ambient);
       glPopMatrix();

         //Code to make earth and making it rotate around sun
         glRotatef(angleEarth,0.0,1.0,-0.5);
         glPushMatrix();
             glTranslatef(2.5,0.0,0.0);
             glColor3f(0.0,0.1,0.7);
             glScalef(0.5,0.5,0.5);
             glutSolidSphere(1,50,50);
                //inside earth making Moon to rotate around sun
                glPushMatrix();
                 glRotatef(angleMoon,0.0,1.0,-0.2);
                 glTranslatef(1.0,0.2,1.2);
                 glColor3f(1.0,1.0,1.0);
                 glScalef(0.3,0.3,0.3);
                 glutSolidSphere(1.5,50,50);
               glPopMatrix();//moon made
       glPopMatrix();//earth made

       //For Jupiter (another planet)
       glPushMatrix();
         glRotatef(angleJupiter,0.0,1.0,-0.5);
         glTranslatef(-4.5,0.0,0.0);
         glColor3f(0.4,0.2,0.0);
         glScalef(0.4,0.4,0.4);
         glutSolidSphere(1.5,50,50);
       glPopMatrix();//jupiter made


       //For drawing the galaxy astroid circle
        glPushMatrix();
             glColor3f(3.30,3.30,3.30);
             glRotatef(63,1.0,0.0,0.0);
             int j=0,i=0,div=90;float siz=2;
             float scl[4]={5.3,5.4,5.35,5.2};
             for(j=0;j<4;j++)
             {
             glPushMatrix();siz-=0.75;
             glPointSize(siz);
             glScalef(scl[j],scl[j],scl[j]);
             glBegin(GL_POINTS);
                double ang1=0.0 -angleSun,a=(2*PI)/div;
                for(i=0;i<div;i++)
                  {glVertex2d(cos(ang1),sin(ang1));
                   ang1+=a;  }
                   div+=10;
            glEnd();
            glPopMatrix();
             }
           glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
}

//Setting sun, moon , earth and jupiter angle
static void idle(void)
{

    angleMoon+=4;
    if(angleMoon>360){
        angleMoon-=360;}

    angleEarth+=2;
    if(angleEarth>360){
        angleEarth-=360;}

    angleSun+=0.03;
    if(angleSun>360){
        angleSun-=360;}

    angleJupiter+=0.5;
    if(angleJupiter>360){
        angleJupiter-=360;}

    glutPostRedisplay();
}

/*imulation starts once pressing UP_key here.
initially start_flag was false and making it true and calling idle function

*/

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        start_flag =! start_flag;
        if (start_flag)
            glutIdleFunc(idle);
        else
            glutIdleFunc(NULL);

    break;
   }
  glutPostRedisplay();
}


static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}


/* Program entry point
Calling all functions here */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutMainLoop();

    return EXIT_SUCCESS;
}
