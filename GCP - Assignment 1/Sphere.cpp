#include "pch.h"
#include "Sphere.h"

IntRes Sphere::intersect(Ray howard)
	{
	//this function deals with the basic maths of the ray caster
	//right now its pretty hard coded and i will be coming back to rework on this assignment
	//this function is going to be the first thing i work on
	IntRes result;

		glm::vec3 A = howard.Origin;
		glm::vec3 n = howard.Dir;

		float d = glm::length(pos - A - (glm::dot(pos - A, n) *n));
		float x = pow((r * r) - (d * d), 0.5);

		result.IntP = A + ((glm::dot(pos - A, n) - x) *n);

		result.dis = glm::length(result.IntP - howard.Origin);

		if (d < r)
		{
			result.hit = true;
		}
		else
		{
			result.hit = false;
		}

		return result;
	}