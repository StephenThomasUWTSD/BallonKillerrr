#include "main.h"
#include "Balloon.h"
#include "Controller.h"
#include "RenderClass.h"

using namespace std;

bool tilesGenerated = false;
//Controller controls;
PairsGame game;
Balloon rayBound;
//CameraConsoleOut camera;
CameraConsoleOut cube;
static int theta = 4;
int winview[2]; //contains window view width [0] and height [1]
double WorldT[16];
double objectNear[4];
double objectFar[4];
// angle of rotation for the camera direction
//float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 3.0f, z = 1.0f;
//float angle = 0.0f;
float yrotrad;
float xrotrad;
float lastx, lasty;
float xpos = 0, ypos = 0, zpos = 0,
xrot = 0, yrot = 0, angle = 0.0;
bool movingUp = false; // Whether or not we are moving up or down  
float yLocation = 0.0f; // Keep track of our position on the y axis.  

float yRotationAngle = 0.0f; // The angle of rotation for our object  
// the key states. These variables will be zero
//when no key is being presses
float deltaMove = 0;
float deltaAngle = 0.0f;
int cursor = -1;


void init(void)
{
	WorldT[0] = 1; WorldT[4] = 0; WorldT[8] = 0; WorldT[12] = 0;
	WorldT[1] = 0; WorldT[5] = 1; WorldT[9] = 0; WorldT[13] = 0;
	WorldT[2] = 0; WorldT[6] = 0; WorldT[10] = 1; WorldT[14] = 0;
	WorldT[3] = 0; WorldT[7] = 0; WorldT[11] = 0; WorldT[15] = 1;
	GLfloat mat_specular[] = { 0.256777, 0.137622, 0.086014, 1.0 };
	GLfloat mat_diffuse[] = { 0.7083, 0.27048, 0.0828, 1.0 };
	GLfloat mat_ambient[] = { 0.79125, 0.6735, 0.6225, 1.0 };
	GLfloat mat_shininess[] = { 12.8 };

	GLfloat light_position[] = { -5.0, 20.0, -5.0, 0.0 };

	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);  //reset "empty" background colour
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glClearColor(0.0, 0.0, 0.0, 0.0);  //reset "empty" background colour
	glShadeModel(GL_SMOOTH);

	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	
}

void glEnable(void)
{
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader

}
void camera(void)
{
	//glPushMatrix();
	//glLoadIdentity();
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on teh x - axis(left and right)
	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the	y - axis(up and down)
	glTranslated(-xpos, -ypos, -zpos); //translate the screen to the position of our camera
	//glPopMatrix();
}
void fireRay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glLoadIdentity();//reset transformation (of modelview matrix)
	glGetDoublev(GL_MODELVIEW_MATRIX, WorldT);//get for use with gluUnproject	
	glBegin(GL_TRIANGLES);  //fire ray
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3d(objectNear[0], objectNear[1], objectNear[2]);
	glVertex3d(objectFar[0], objectFar[1], objectFar[2]);
	glVertex3d(objectNear[0] + 0.1, objectNear[1], objectNear[2]);
	glEnd();
}
void mouseMovement(int x, int y) {
	int diffx = x - lastx; //check the difference between the current x and the last x position
	int diffy = y - lasty; //check the difference between the current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += (float)diffy; //set the xrot to xrot with the addition of the difference in the y position
	yrot += (float)diffx;// set the xrot to yrot with the addition of the difference in the x position
}
void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		int view[4];
		//   double modelview[16];
		double proj[16];
		glGetIntegerv(GL_VIEWPORT, view);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		int realy = view[3] - (GLint)y - 1;
		int check = gluUnProject(x, realy, -1, WorldT, proj, view, objectNear, objectNear + 1, objectNear + 2);
		cout << "unprojected near co-ords are ";
		for (int i = 0; i<4; i++) 
		{
			cout << objectNear[i] << " ";
		} 
		cout << "\n";
		check = gluUnProject(x, realy, 1, WorldT, proj, view, objectFar, objectFar + 1, objectFar + 2);
		cout << "unprojected far co-ords are ";
		for (int i = 0; i<4; i++) 
		{
			cout << objectFar[i] << " ";
		} 
		cout << "\n";
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(0.0, 1.0, 1.0);
		glLoadIdentity();//reset transformation (of modelview matrix)
		glGetDoublev(GL_MODELVIEW_MATRIX, WorldT);//get for use with gluUnproject	
		glBegin(GL_TRIANGLES);  //fire ray
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3d(objectNear[0], objectNear[1], objectNear[2]);
		glVertex3d(objectFar[0], objectFar[1], objectFar[2]);
		glVertex3d(objectNear[0] + 0.1, objectNear[1], objectNear[2]);
		// nd();
		//prepare for collision test by making a ray
		Vector d(objectFar[0], objectFar[1], objectFar[2]);
		Vector p(objectNear[0], objectNear[1], objectNear[2]);
		Ray ray1;  //this is the ray cast
		ray1.SetOrigin(p);      //initialise ray with origin and direction vector
		ray1.SetDirection(d - p);
		glEnd();
		if (rayBound.isBoundSphereIntersect(ray1))
			cout << "hit" << endl;
		else
			cout << "miss" << endl;
		

		glutPostRedisplay();

	}

}


void bounce()
{
	if (movingUp) // If we are moving up  
		yLocation -= 0.005f; // Move up along our yLocation  
	else  // Otherwise  
		yLocation += 0.005f; // Move down along our yLocation  

	if (yLocation < -3.0f) // If we have gone up too far  
		movingUp = false; // Reverse our direction so we are moving down  
	else if (yLocation > 3.0f) // Else if we have gone down too far  
		movingUp = true; // Reverse our direction so we are moving up  
	glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis  

	
}



void changeSize(int w, int h) {
	GLfloat nRange = 10000.0f;
	glViewport(0, 0, w, h);
	
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;
	// Set the viewport to be the entire window
	//glGetDoublev(GL_MODELVIEW_MATRIX, WorldT);
	// Reset Matrix
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//             l,r,bot,top,near,far
	
	// Set the correct perspective.
	//glPopMatrix();
	//set the perspective (angle of sight, width, height, , depth)
	//gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0); 
	//glLoadIdentity();
	// Get Back to the Modelview
	//glMatrixMode(GL_MODELVIEW);
	// Establish clipping volume (left, right, bottom, top, near, far)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
		

	
	//glutSwapBuffers();
	glMatrixMode(GL_MODELVIEW);
	winview[0] = w; winview[1] = h;
	//glLoadIdentity();
}

//This function first translates a further x,y,z units then draws a box of
//width w, height h, length l
void drawBox(float w, float h, float l)
{
	
	glPushMatrix();//maybe in maybe not
	
	glTranslatef(rayBound.BVposition.x, rayBound.BVposition.y, rayBound.BVposition.z);
	glutWireSphere(rayBound.BoundSphereRadius, 20, 20);
	glPopMatrix();
	glPushMatrix();       //save modelview
	w = w / 2.0; h = h / 2.0; l = l / 2.0; //adjust values so centre is in middle of box
										   //draw faces of box
	glBegin(GL_POLYGON);
	glVertex3f(w, l, h);
	glVertex3f(w, l, -h);
	glVertex3f(-w, l, -h);
	glVertex3f(-w, l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(w, l, h);
	glVertex3f(-w, l, h);
	glVertex3f(-w, -l, h);
	glVertex3f(w, -l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(w, l, h);
	glVertex3f(w, -l, h);
	glVertex3f(w, -l, -h);
	glVertex3f(w, l, -h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-w, l, h);
	glVertex3f(-w, l, -h);
	glVertex3f(-w, -l, -h);
	glVertex3f(-w, -l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-w, -l, h);
	glVertex3f(-w, -l, -h);
	glVertex3f(w, -l, -h);
	glVertex3f(w, -l, h);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(w, -l, -h);
	glVertex3f(-w, -l, -h);
	glVertex3f(-w, l, -h);
	glVertex3f(w, l, -h);
	glEnd();
	glPopMatrix();   //restore previous modelview matrix so leaving things as you found them
}


void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void renderScene(void) 
{	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glEnable();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	// Reset transformations
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(4.0, 2.0, 0.001, 100000);
	gluPerspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.00001f, 500.0f); // We define the "viewing volume"
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the color buffer and the depth buffer
	glLoadIdentity();
	camera();
	

	//gluLookAt(8.0*sin(float(theta)*0.0175), 11.0, 11.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	//cube.cube(); //call the cube drawing function
	//glutSwapBuffers(); //swap the buffers
	
	//gluLookAt(5.0*sin(float(theta)*0.0175), 5.0, 5.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//drawBox(10,10,10);
	//glEnd();
	//glBegin(GL_POLYGON);
	//glEnable();
	for (Box box : game.boxes) 
	{
		glPushMatrix();
		glTranslatef(box.x, box.y, box.z);

		rotateTiles();

		glColor3f(box.r, box.g, box.b);
		drawBox(1, 1, 1);
		glPopMatrix();

	}
	//glEnd();
	//glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis 
	//glPopMatrix();
	glutSwapBuffers();
	angle++; //increase the angle
}


void SetupRC()
{

	// Black background
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);

}



void releaseKey(int key, int x, int y) 
{

	switch (key) 
	{
	case GLUT_KEY_END:
		yRotationAngle = 0;
		break;
	}
}

float randColour() 
{
	return (double)rand() / (RAND_MAX + 1.0);
}
/*
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the color buffer and the depth buffer
	glLoadIdentity();
	
	camera();
	//gluLookAt(8.0*sin(float(theta)*0.0175), 11.0, 11.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable();
	//cube.cube(); //call the cube drawing function
	glutSwapBuffers(); //swap the buffers
	angle++; //increase the angle
	
}
*/
void keyboardread(unsigned char key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glPushMatrix();
	glLoadIdentity();
	switch (key) {
	case 'q':
		xrot += 1;
		if (xrot > 360) xrot -= 360;
		cout << 'q' << endl;
		break;
	case 'z':
		xrot -= 1;
		if (xrot < -360) xrot += 360;
		cout << 'z' << endl;
		break;
	case 'w':
		xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
		cout << 'w' << endl;
		break;
	case 's':
		xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
		cout << 's' << endl;
		break;
	case 'd':
		yrot += 1;
		if (yrot >360) yrot -= 360;
		cout << 'd' << endl;
		break;
	case 'a':
		yrot -= 1;
		if (yrot < -360)yrot += 360;
		cout << 'a' << endl;
		break;
	case 'b':
		exit(27);
		cout << 'b' << endl;
		break;
	case 't':
		yLocation = 0.5;
		game.ShuffleBoxes();
		break;
		glPopMatrix();
	}
	
	void pressKey();
	glutPostRedisplay();
	
}


int main(int argc, char **argv) 
{
	// init GLUT and create window
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Match The Tiles: Ray Madness!");
	
	
	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	//glPushMatrix();
	//glutSwapBuffers();
	init();
	glutPassiveMotionFunc(mouseMovement);
	//SetupRC();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(keyboardread);
	glutMouseFunc(mouse);
	//glutDisplayFunc(display);
	//glutIdleFunc(display);
	//glutSpecialFunc(pressKey);
	//glutDisplayFunc(camera);
	// here are the new entries
	//glutIgnoreKeyRepeat(1);
	//glutSpecialUpFunc(releaseKey);
	
	// OpenGL init
	
	//glutInitDisplayMode(GLUT_DEPTH);
	//
	//raymouse.mouse();
	//glPushMatrix();
	game.ShuffleBoxes();
	//glPopMatrix();
	//glutMouseFunc(mouse);
	//blackGround();
	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
//glutReshapeFunc(ChangeSize);
void rotateTiles()
{
	
	yRotationAngle += 0.005f; // Increment our rotation value  
	if (yRotationAngle > 360.0f) // If we have rotated beyond 360 degrees (a full rotation)
		yRotationAngle -= 360.0f; // Subtract 360 degrees off of our rotation
	glRotatef(yRotationAngle, 0.0f, 0.0f, 1.0f); // Rotate our object around the y axis 
}
