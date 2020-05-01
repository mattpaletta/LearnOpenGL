//
//  debug.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-30.
//

#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)
