#pragma once

#ifdef NOTGLM_EXPORTS
#define	NOTGLM_API __declspec(dllexport)
#else
#define NOTGLM_API __declspec(dllimport)
#endif

extern "C" NOTGLM_API float add_func(float a, float b);
extern "C" NOTGLM_API float times_func(float a, float b);
extern "C" NOTGLM_API float devide_func(float a, float b);