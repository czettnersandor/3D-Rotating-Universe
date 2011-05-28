/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  3D rotating universe GL sample app 
 *
 *        Version:  0.1
 *        Created:  12/19/2009 12:38:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sandor Czettner (CzS), sandor@czettner.hu
 *        Company:  http://sandor.czettner.hu
 *
 * =====================================================================================
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

const int NPOINTS=3000;

GLfloat density = 0.3;
GLfloat fogColor[4] = {0.0, 0.0, 0.0, 1.0};

GLfloat angle = 3.14;
GLfloat points[NPOINTS][3], midp[NPOINTS][3], lastp[NPOINTS][3]; // points
GLfloat x, y, z, c;

void init (void) {
  for (int i = 0; i < NPOINTS; i++) {
    points[i][0] = double(rand())/(double(RAND_MAX))*8-4; // Radius
    points[i][1] = (double(rand())/(double(RAND_MAX))*2-1) * (1-fabs(points[i][0]/4)); // Z
    points[i][2] = double(rand())/(double(RAND_MAX))*360; // Starting angle
  }
  glEnable (GL_DEPTH_TEST); //enable the depth testing
  glEnable (GL_FOG); //enable the fog

  glFogi (GL_FOG_MODE, GL_LINEAR); //set the fog mode to GL_EXP2
  glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
  glFogf (GL_FOG_DENSITY, density); //set the density to the value above

  glHint (GL_FOG_HINT, GL_DONT_CARE); // set the fog to look the nicest, may slow down on older cards
  glFogf(GL_FOG_START, 7.0);                             // Fog Start Depth
  glFogf(GL_FOG_END, 15.0);

  glEnable( GL_POINT_SMOOTH );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glPointSize( 2.0 );


}

void calculate (void) {
  for (int i = 0; i < NPOINTS; i++) {
    GLfloat a;
    c = 1.3 - fabs(points[i][0]/4);
    a = angle * fabs(1/(points[i][0]))+points[i][2];
    x = points[i][0] * cos(a);
    y = points[i][0] * sin(a);
    z = points[i][1];
    glBegin(GL_LINE_STRIP);
    glColor3f(c, c, c);
    glVertex3f(x, y, z);
    glColor3f(c/2,c/2,c/2);
    glVertex3f(midp[i][0], midp[i][1], midp[i][2]);
    glColor3f(0, 0, 0);
    glVertex3f(lastp[i][0], lastp[i][1], lastp[i][2]);
    glEnd( );
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd( );
    lastp[i][0] = midp[i][0];
    lastp[i][1] = midp[i][1];
    lastp[i][2] = midp[i][2];
    midp[i][0] = x;
    midp[i][1] = y;
    midp[i][2] = z;
  }
}

void display (int value = 0) {
  glutTimerFunc(60, display, 0);
  glClearColor (0.0,0.0,0.0,1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt (0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
  glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
  // glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0, 0);
  glVertex3f(0, 0, -2);
  glColor3f(1,1,1);
  glVertex3f(0, 0, 0);
  glColor3f(0, 0, 0);
  glVertex3f(0, 0, 2);
  glEnd( );

  angle = angle + 0.1;
  calculate();
  glFinish();
  glutSwapBuffers();
}

void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv) {
  srand ( time(NULL) );
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize (640, 480);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("3D rotating universe");
  init();
  //glutDisplayFunc (display);
  //glutIdleFunc (display); //change any idle values accordingly
  glutTimerFunc(60, display, 0);
  glutReshapeFunc (reshape);
  glutMainLoop ();
  return 0;
}

