#pragma once

#ifdef _WIN32

#define OEDONAPI extern "C" __declspec(dllexport)

#else

#define OEDONAPI extern "C"

#endif


