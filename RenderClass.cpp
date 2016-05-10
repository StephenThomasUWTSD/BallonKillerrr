#include "RenderClass.h"
#include "main.h"


RenderClass::RenderClass()
{
}
void RenderClass::RenderRend()
{	
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	// Reset transformations
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(4.0, 2.0, 0.001, 100000);
	//gluPerspective(45.0f, (GLfloat)800 / (GLfloat)600, 5.0f, 10000.0f); // We define the "viewing volume"
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	//gluLookAt(10.0*x*0.0175, 10.0, 5.0*z*0.0175, x + lx, -1.0f, z + lz, 0.0f, 1.0f, 0.0f);
	//gluLookAt(8.0*sin(float(theta)*0.0175), 11.0, 11.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(5.0*sin(float(theta)*0.0175), 5.0, 5.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnd();
	PairsGame game;
	for (Box box : game.boxes) {
		glPushMatrix();
		glTranslatef(box.x, box.y, box.z);

		//rotateTiles();

		glColor3f(box.r, box.g, box.b);
		drawBox(1, 1, 1);
		glPopMatrix();

	}
	//glEnd();
	//glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis 
	//glPopMatrix();
	glutSwapBuffers();
}

RenderClass::~RenderClass()
{
}
