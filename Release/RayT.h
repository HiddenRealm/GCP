#pragma once
#include "Ray.h"
#include "IntersectResult.h"
#include "Sphere.h"
#include "Camera.h"

class RayT
{

protected:

	Camera * myCamera;
	Sphere * sphere;
	Sphere * sphere2;

public:
	//Functions
	RayT();
	glm::vec3 Trace(Ray howard);
	Ray genRay(int x, int y, int z);
	glm::vec3 Colour(Ray howard, glm::vec3 pos, float dis, glm::vec3 col);

private:
	//setting up where the main light is in the project
	glm::vec3 lightSource{ 375, 20, 150};
	glm::vec3 lightColour{ 255,255,255 };
};