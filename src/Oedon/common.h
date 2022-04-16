#pragma once

#ifdef _WIN32

#define OEDONAPI extern "C" __declspec(dllexport)
#define OEDONCLASS __declspec(dllexport)

#else

#define OEDONAPI extern "C"
#define OEDONCLASS 
#endif


