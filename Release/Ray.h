#pragma once
#include <GLM/glm.hpp>

//struct to hold the important info of the rays
struct Ray
{
	glm::vec3 Origin;
	glm::vec3 Dir;
};