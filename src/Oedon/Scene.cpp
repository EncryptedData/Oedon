#define JSON_NOEXCEPTION
#include <nlohmann/json.hpp>

#include "Scene.h"
#include "Operations.h"

OEDONAPI Scene * CreateScene()
{
	return new Scene();
}

OEDONAPI void __cdecl DoOperations(Scene * scene, const char * operations)
{

	nlohmann::json json(operations);
	
	std::map<std::string, nlohmann::json> ops;
	
	ops = json.get<std::map<std::string, nlohmann::json>>();

	scene;
}

Handle Scene::AddResource()
{
	return Handle();
}

Resource * Scene::GetResource(Handle /*resource_handle*/)
{
	return nullptr;
}
