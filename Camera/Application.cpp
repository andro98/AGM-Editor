//#include<glew.h>
#include<openglut.h>
#include <stdlib.h>
#include<cmath>
#include <iostream>

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f , lz = -1.0f;
// XZ position of the camera
float x = 0.0f , z = 5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

int xOrigin = -1;

void changeSize (int w , int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if ( h == 0 )
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode (GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity ();

	// Set the viewport to be the entire window
	glViewport (0 , 0 , w , h);

	// Set the correct perspective.
	gluPerspective (45 , ratio , 1 , 1000);

	// Get Back to the Modelview
	glMatrixMode (GL_MODELVIEW);
}

void drawSnowMan () {

	glColor3f (1.0f , 1.0f , 1.0f);

	// Draw Body
	glTranslatef (0.0f , 0.75f , 0.0f);
	glutSolidSphere (0.75f , 20 , 20);

	// Draw Head
	glTranslatef (0.0f , 1.0f , 0.0f);
	glutSolidSphere (0.25f , 20 , 20);

	// Draw Eyes
	glPushMatrix ();
	glColor3f (0.0f , 0.0f , 0.0f);
	glTranslatef (0.05f , 0.10f , 0.18f);
	glutSolidSphere (0.05f , 10 , 10);
	glTranslatef (-0.1f , 0.0f , 0.0f);
	glutSolidSphere (0.05f , 10 , 10);
	glPopMatrix ();

	// Draw Nose
	glColor3f (1.0f , 0.5f , 0.5f);
	glutSolidCone (0.08f , 0.5f , 10 , 2);
}

void drawHome ()
{

	/* main rec */
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (.5 , .75 , .35);
	glBegin (GL_POLYGON);
	glVertex3f (0.2 , 0.1 , 0.0);
	glVertex3f (0.9 , 0.1 , 0.0);
	glVertex3f (0.9 , 0.575 , 0.0);
	glVertex3f (0.2 , 0.575 , 0.0);
	glEnd ();

	/*back rec*/
	glColor3f (.5 , .75 , .35);
	glBegin (GL_POLYGON);
	glVertex3f (0.2 , 0.1 , 0.5);
	glVertex3f (0.9 , 0.1 , 0.5);
	glVertex3f (0.9 , 0.575 , 0.5);
	glVertex3f (0.2 , 0.575 , 0.5);
	glEnd ();

	/* left rec */
	glColor3f (.75 , 0.75 , .25);
	glBegin (GL_POLYGON);
	glVertex3f (0.2 , 0.1 , 0.5);
	glVertex3f (0.2 , 0.1 , 0.0);
	glVertex3f (0.2 , 0.575 , 0.0);
	glVertex3f (0.2 , 0.575 , 0.5);
	glEnd ();

	/* right rec */
	glColor3f (.75 , 0.75 , .25);
	glBegin (GL_POLYGON);
	glVertex3f (0.9 , 0.1 , 0.5);
	glVertex3f (0.9 , 0.1 , 0.0);
	glVertex3f (0.9 , 0.575 , 0.0);
	glVertex3f (0.9 , 0.575 , 0.5);
	glEnd ();

	/* left tri */
	glColor3f (.5 , 0.5 , .25);
	glBegin (GL_TRIANGLES);
	glVertex3f (0.9 , 0.575 , 0.0);
	glVertex3f (0.9 , 0.575 , 0.5);
	glVertex3f (0.9 , 0.8 , 0.25);
	glEnd ();

	/* right tri */
	glColor3f (.5 , 0.5 , .25);
	glBegin (GL_TRIANGLES);
	glVertex3f (0.2 , 0.575 , 0.0);
	glVertex3f (0.2 , 0.575 , 0.5);
	glVertex3f (0.2 , 0.8 , 0.25);
	glEnd ();

	/* roof */
	glColor3f (.55 , 0.35 , .2);
	glBegin (GL_POLYGON);
	glVertex3f (0.2 , 0.575 , 0.0);
	glVertex3f (0.9 , 0.575 , 0.0);
	glVertex3f (0.9 , 0.8 , 0.25);
	glVertex3f (0.2 , 0.8 , 0.25);
	glEnd ();

	/*back roof */
	glColor3f (.55 , 0.35 , .2);
	glBegin (GL_POLYGON);
	glVertex3f (0.2 , 0.575 , 0.5);
	glVertex3f (0.9 , 0.575 , 0.5);
	glVertex3f (0.9 , 0.8 , 0.25);
	glVertex3f (0.2 , 0.8 , 0.25);
	glEnd ();

	/* door */
	glColor3f (.15 , 0.2 , .3);
	glBegin (GL_POLYGON);
	glVertex3f (0.47 , 0.105 , 0.0);
	glVertex3f (0.65 , 0.105 , 0.0);
	glVertex3f (0.65 , 0.46 , 0.0);
	glVertex3f (0.47 , 0.46 , 0.0);
	glEnd ();

	/* window 1 */
	glColor3f (.3 , 0.2 , .1);
	glBegin (GL_POLYGON);
	glVertex3f (0.72 , 0.25 , 0.0);
	glVertex3f (0.83 , 0.25 , 0.0);
	glVertex3f (0.83 , 0.4 , 0.0);
	glVertex3f (0.72 , 0.4 , 0.0);
	glEnd ();

	/* window 2 */
	glColor3f (.3 , 0.2 , .1);
	glBegin (GL_POLYGON);
	glVertex3f (0.27 , 0.25 , 0.0);
	glVertex3f (0.38 , 0.25 , 0.0);
	glVertex3f (0.38 , 0.4 , 0.0);
	glVertex3f (0.27 , 0.4 , 0.0);
	glEnd ();


	//glFlush ();
	glPopMatrix ();
}

void computePos (float deltaMove) {

	x += deltaMove * lx * 0.01f;
	z += deltaMove * lz * 0.01f;
}

void computeDir (float deltaAngle) {

	angle += deltaAngle;
	lx = sin (angle);
	lz = -cos (angle);
}

void renderScene (void) {

	if ( deltaMove )
		computePos (deltaMove);
	if ( deltaAngle )
		computeDir (deltaAngle);

	// Clear Color and Depth Buffers

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor (0.0 , 0.3 , 0.3 , 1.0);
	// Reset transformations
	glLoadIdentity ();

	// Set the camera
	gluLookAt (x , 1.0f , z ,
		x + lx , 1.0f , z + lz ,
		0.0f , 1.0f , 0.0f);

	glRotatef (angle , 0.0f , 1.0f , 0.0f);

	// Draw ground
	glColor3f (0.9f , 0.0f , 0.9f);

	glBegin (GL_QUADS);
	glVertex3f (-100.0f , 0.0f , -100.0f);
	glVertex3f (-100.0f , 0.0f , 100.0f);
	glVertex3f (100.0f , 0.0f , 100.0f);
	glVertex3f (100.0f , 0.0f , -100.0f);
	glEnd ();

	// Draw 36 SnowMen
	for ( int i = -3; i < 3; i++ )
	for ( int j = -3; j < 3; j++ ) {
		glPushMatrix ();
		glTranslatef (i*10.0 , 0 , j * 10.0);
		drawSnowMan ();
		glPopMatrix ();
	}
	
	//drawHome ();

	glutSwapBuffers ();

}


//void mouseButton (int button , int state , int x , int y) {
//
//	// only start motion if the left button is pressed
//	if ( button == GLUT_LEFT_BUTTON ) {
//
//		// when the button is released
//		if ( state == GLUT_UP ) {
//			angle -= deltaAngle;
//			xOrigin = -1;
//		}
//		else {// state = GLUT_DOWN
//			xOrigin = x;
//		}
//	}
//}
//
//void mouseMove (int x , int y) {
//	if ( xOrigin >= 0 ) {
//
//		// update deltaAngle
//		deltaAngle = ( x - xOrigin ) * 0.001f;
//
//		// update camera's direction
//		lx = sin (angle + deltaAngle);
//		lz = -cos (angle + deltaAngle);
//	}
//}


void pressKey (int key , int xx , int yy) {

	switch ( key ) {
	case GLUT_KEY_LEFT: deltaAngle = -0.1f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.1f; break;
	case GLUT_KEY_UP: deltaMove =10.0f; break;
	case GLUT_KEY_DOWN: deltaMove = -10.0f; break;
	}
}

void releaseKey (int key , int x , int y) {

	switch ( key ) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}


void processNormalKeys (unsigned char key , int x , int y) {

	if ( key == 27 )
		exit (0);
}

int main (int argc , char **argv)
{
	// init GLUT and create Window
	glutInit (&argc , argv);
	glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition (0 , 0);
	glutInitWindowSize (1280 , 720);
	glutCreateWindow ("AGM-Camera");



	//// register callbacks
	glutDisplayFunc (renderScene);
	glutReshapeFunc (changeSize);
	glutReshapeWindow (1280 , 720);
	glutIdleFunc (renderScene);

	///	here are the new entries
	glutSpecialFunc (pressKey);
	glutKeyboardFunc (processNormalKeys);
	glutIgnoreKeyRepeat (1);
	glutSpecialUpFunc (releaseKey);

	// OpenGL init
	glEnable (GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop ();


	return 0;
}