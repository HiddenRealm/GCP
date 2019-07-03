#include "pch.h"
#include "Camera.h"

//Function that makes the ray
Ray Camera::genRay(int x, int y)
	{
		Ray val;
		val.Origin = glm::vec3(x, y, 0);
		val.Dir = glm::vec3(0, 0, -1);
		return val;
	}