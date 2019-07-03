#pragma once
#include <GLM/glm.hpp>

//struct to hold the results of any check intersections
struct IntRes
{
	bool hit;
	float dis;
	glm::vec3 IntP;
};