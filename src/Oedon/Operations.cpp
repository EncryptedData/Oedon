#include "Operations.h"

std::map<std::string, Operation> operations;

void AddOperation(std::string name, Operation operation)
{
	operations[name] = operation;
}

bool DoOperation(std::string operation, std::string parameters)
{
	if (operations.find(operation) == operations.end())
		return false;
	
	operations[operation](parameters);
	return true;
}
