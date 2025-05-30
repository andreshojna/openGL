#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __builtin_trap()

#define GLCall(x) GLClearError();     \
    x;                                \
    ASSERT(GLLogcall(#x, __FILE__, __LINE__));

void GLClearError();

void GLCheckError();

bool GLLogcall(const char* func, const char* file, int line);