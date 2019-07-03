#include "pch.h"
#include "RayT.h"

RayT::RayT()
{
	//these are the two hard coded spheres
	sphere = new Sphere();
	sphere->pos = { 300, 240, -100 };
	sphere->r = 100;
	sphere->col = { 255,0,0 }; // Red

	sphere2 = new Sphere();
	sphere2->pos = { 240, 360, -150 };
	sphere2->r = 75;
	sphere2->col = { 0,255,0 }; // Green

}

glm::vec3 RayT::Trace(Ray howard)
{
	// this is where i check each of the shperes indiviually
	// if i had more time to work on this project, i would have instead used a vector on objects
	// i could then use a for loop to run through the checks for all of the objects at once.
	if (sphere->intersect(howard).hit == true)
	{
		glm::vec3 colour = Colour(howard, sphere->pos, sphere->intersect(howard).dis, sphere->col);
		return colour;
	}
	else if (sphere2->intersect(howard).hit == true)
	{
		//I wasnt able to finsih this code, however i do have a decent idea what was wrong with it
		//I i would have just needed to make my math problems a little less hard coded in the sphere.cpp file
		//I have just run out of time to accomplish this however
		/*bool blocked = false;

		Ray currentRay = genRay(howard.Origin.x, howard.Origin.y, sphere2->pos.z);
		
		if (sphere->intersect(currentRay).hit == true)
		{
			return { 0,0,0 };
		}*/

		glm::vec3 colour = Colour(howard, sphere2->pos, sphere2->intersect(howard).dis, sphere2->col);
		return colour;
	}

	//this is to change the background, it makes it easier to see the "shading"
	return glm::vec3{ 0,0,255}; //Blue
}

//This Function deals with the very basic diffuse shading that goes on here
glm::vec3 RayT::Colour(Ray howard, glm::vec3 pos, float dis, glm::vec3 col)
{
	glm::vec3 hitPoint = howard.Origin + howard.Dir * dis;

	glm::vec3 normal = hitPoint - pos;
	glm::vec3 vNormal = glm::normalize(normal);

	glm::vec3 lightDir = (lightSource - hitPoint);
	glm::vec3 vLightDir = glm::normalize(lightDir);

	float d = glm::dot(vNormal, lightDir);
	if (d < 0.0f)
	{
		d = 0.0f;
	}

	return (col * d * lightColour);
}


//This was for my attemp at the actual ray tracing,
// i think it would have been better to have this set up as a virtual class and have a few templates for it
Ray RayT::genRay(int x, int y, int z)
{
	Ray val;
	val.Origin = glm::vec3(x, y, z);
	val.Dir = lightSource;
	return val;
}