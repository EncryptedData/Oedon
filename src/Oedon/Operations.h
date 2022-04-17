#pragma once
#include <functional>
#include <map>

#include "Scene.h"

using Operation = std::function<void(std::string)>;

void AddOperation(std::string name, Operation operation);

bool DoOperation(std::string operation, std::string parameters);
