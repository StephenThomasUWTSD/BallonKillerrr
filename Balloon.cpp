#include "Balloon.h"
#include "main.h"




Balloon::Balloon() : position(0, 0, 0), BVposition(0, 0, 0) {
	intersect = false;
	BoundSphereRadius = 1.0;
	BVposition.x = position.x + 0;
	BVposition.y = position.y - 0;
	BVposition.z = position.z - 0;
}


bool Balloon::isBoundSphereIntersect(Ray v) {
	//calc collision
	cout << "line point distance squared is: " << v.LinePointDistanceSqd(BVposition) << "\n";


	if (v.LinePointDistanceSqd(BVposition) > (BoundSphereRadius*BoundSphereRadius))
		return false; //no intersection detected
	else true;//intersection detected
}
void Balloon::draw(void)
{
	//Description:
	//This routine draws the house from OGL primitives
	//Note all polygon windings are counter clockwise
	//If you look at the front of a polygon its vertices are
	//listed so that the polygon is drawn in counterclockwise manner.
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	  glPolygonMode(GL_BACK,GL_FILL); //uses also GL_FRONT_AND_BACK; GL_FILL, GL_POINT, GL_LINE  
	 glPolygonMode(GL_FRONT,GL_FILL);// to spec. whether poly's. front and back are drawn filled
	// as lines or points

	glCullFace(GL_BACK);//discards front or back facing polygons
	glEnable(GL_CULL_FACE);  
	glPushMatrix();
	glTranslatef(BVposition.x, BVposition.y, BVposition.z);
	glutWireSphere(BoundSphereRadius, 10, 10);

	/*glPopMatrix();
	glPushMatrix();

	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);//front norm is (0,0,-1)
	glVertex3f(0.0, -2.0, 0.0);
	glVertex3f(1.0, -2.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);//right (1,0,0)
	glVertex3f(1.0, -2.0, 0.0);
	glVertex3f(1.0, -2.0, -1.0);
	glVertex3f(1.0, 0.0, -1.0);

	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);//left (-1,0,0)
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, -2.0, -1.0);
	glVertex3f(0.0, -2.0, 0.0);

	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, -2.0, 0.0); //bottom (0,-1,0)
	glVertex3f(0.0, -2.0, -1.0);
	glVertex3f(1.0, -2.0, -1.0);
	glVertex3f(1.0, -2.0, 0.0);

	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, -1.0);//back (0,0,1)
	glVertex3f(1.0, 0.0, -1.0);
	glVertex3f(1.0, -2.0, -1.0);
	glVertex3f(0.0, -2.0, -1.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);//front gable (0,0,-1)
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.25, 0.0);

	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, -1.0);//back gable (0,0,1)
	glVertex3f(0.5, 1.25, -1.0);
	glVertex3f(1.0, 0.0, -1.0);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-0.9385, 0.3714, 0.0);
	glVertex3f(0.0, 0.0, 0.0);//left roof (-0.9385,0.3714,0.0) 
	glVertex3f(0.5, 1.25, 0.0);
	glVertex3f(0.5, 1.25, -1.0);
	glVertex3f(0.0, 0.0, -1.0);

	glNormal3f(0.9385, 0.3714, 0.0);
	glVertex3f(0.5, 1.25, 0.0);//right roof (0.9385,0.3714,0.0)
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, -1.0);
	glVertex3f(0.5, 1.25, -1.0);
	glEnd();*/
	glPopMatrix();
}