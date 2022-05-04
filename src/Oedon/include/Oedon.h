#pragma once

#ifdef _WIN32

#define OEDONAPI extern "C" __declspec(dllexport)
#define OEDONCLASS __declspec(dllexport)

#else

#define OEDONAPI extern "C"
#define OEDONCLASS 
#endif

class OEDONCLASS TestClass
{
public:

	// Currently doesn't support class members
};

struct OEDONCLASS Test1
{
	int A;
	double B;

};

struct OEDONCLASS Test2
{
	Test1* hello;
};

OEDONAPI int Sum(int a, int b);

OEDONAPI const char* Foo(const char* f);

OEDONAPI void Bar(Test1* t);
