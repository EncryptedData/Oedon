#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"

using Point = glm::vec3;
class PointField
{
	~PointField() {};
	//std::vector<Point> points;
};

enum class ResourceType
{
	Mesh,
};

union Data
{
	~Data() {};
	Mesh mesh;
	PointField point_field;
};

struct Resource
{
	~Resource() {};

	ResourceType type;
	Data data;
};