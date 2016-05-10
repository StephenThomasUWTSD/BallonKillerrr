#pragma once

#include "Vector.h"
class Balloon
{
public:


	Balloon();

	void sceneBound();

	bool isBoundSphereIntersect(Ray v);
	//void drawBox(float w, float h, float l);
	void draw();
	//void Balloon(int button, int state, int x, int y);
	//private:
	bool intersect;
	float BoundSphereRadius;
	float sceneBoundSphereRadius;

	Vector BVposition;//point

	Vector position; //point
					 //Vector BVposition;//point

					 //~Balloon();
};

