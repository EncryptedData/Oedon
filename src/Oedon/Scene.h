#pragma once
#include <vector>

#include "common.h"
#include "Resources.h"

using Handle = unsigned int;

class Scene
{
public:
	Handle AddResource();
	Resource * GetResource(Handle resource_handle);
private:
	std::vector<Resource> resources;
};

OEDONAPI Scene * CreateScene();

OEDONAPI void DoOperations(Scene * scene, const char * operations);
