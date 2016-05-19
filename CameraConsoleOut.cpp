#include "CameraConsoleOut.h"
#include "main.h"
//M_PI 3.14159265358979323846 3.141592654

CameraConsoleOut::CameraConsoleOut()
{
	
}


void CameraConsoleOut::AssetInit(void)
{
	cubepositions();
}//positions of the cubes


void CameraConsoleOut::cubepositions(void)
{//set the positions of the cubes

	for (int i = 0; i<10; i++)
	{	
		int positionz[10] = { rand() % 5 + 5 };
		int positionx[10] = { rand() % 5 + 5 };
	}
}




//draw the cube
void CameraConsoleOut::cube(void) {
	for (int i = 0; i<10; i++)
	{
		glPushMatrix();

		glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] * 10); //translate the cube
		glutSolidCube(2); //draw the cube
		glPopMatrix();
	}
}

void CameraConsoleOut::camera(void)
{
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
		glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the	y - axis(up and down)
		glTranslated(-xpos, -ypos, -zpos ); //translate the screen to the position of our camera
}





CameraConsoleOut::~CameraConsoleOut()
{
}
/*
if (yrot < -360)
{
	yrot += 360;
}
*/