#pragma once
#include "Ray.h"
#include "IntersectResult.h"

class Sphere
{

public:
	
	glm::vec3 pos;
	glm::vec3 col;
	float r;

	//function
	IntRes intersect(Ray howard);

};