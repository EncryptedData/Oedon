
#include "common.h"
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "include/Oedon.h"

// External C functions have to be marked like this
int Sum(int a, int b)
{
	return a + b;
}

const char* Foo(const char* f)
{
	return f;
}

void Bar(Test1* /*t*/)
{

}

// External classes need to be marked like this
class OEDONCLASS MeshStub
{

};
