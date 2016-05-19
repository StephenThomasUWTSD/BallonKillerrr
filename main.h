#pragma once
#include "glfw3.h"
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Vector.h"
#include "Box.h"
#include "PairsGame.h"
#include "Balloon.h"
#include "CameraConsoleOut.h"
#include "Controller.h"
#include "RenderClass.h"

using namespace std;
void rotateTiles(void);
void bounce(void);
void changeSize(int, int);
void drawBox(float, float, float);
//void computePos(float);
//void computeDir(float);
void renderScene(void);
void display(void);
float randColour(void);
void mouse(int, int, int, int);
//void blackGround();
void init(void);
//void glEnable(void);
void display(void);
void RenderAssets();
void pressKey(unsigned char key, int x, int y);
void camera(void);
void keyboardread(unsigned char key, int x, int y);
void deltaTime();