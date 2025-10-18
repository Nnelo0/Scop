#pragma once

#define IMGUI_IMPL_OPENGL_LOADER_GLEW

/*-------- Include --------*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <array>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imconfig.h"
#include "imgui/imgui_internal.h"
#include "imgui/imstb_rectpack.h"
#include "imgui/imstb_textedit.h"
#include "imgui/imstb_truetype.h"

/*----- DEFINE COLORS -----*/
#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"

/*-------- Namespace -------*/
using namespace std;

/*-------- Classes --------*/
#include "Obj.hpp"
#include "Shaders.hpp"
#include "Vec3.hpp"
#include "Matrix.hpp"

/*-------- Functions -------*/
GLuint loadTexture(const char *path);

/*-------- Defines --------*/
