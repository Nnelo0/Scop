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

/*-------- Structures --------*/

struct WindowInfo
{
	float	BackgroundColors[3];

	bool	pPressedLastFrame;
	bool	TPressedLastFrame;
	bool	TabPressedLastFrame;

	bool	showDebugWindow;
};

/*-------- Classes --------*/
class Obj;
class Shaders;
#include "Obj.hpp"
#include "Shaders.hpp"
#include "Vec3.hpp"
#include "Matrix.hpp"
#include "Camera.hpp"

/*-------- Functions -------*/

GLuint 			loadTexture(const char *path);

void 			processInput(GLFWwindow *window, Obj &obj, Camera &cam, WindowInfo &windowInfo);
GLFWwindow*		initWindow(string nameWindow, Camera &cam);
void			initWindowInfo(WindowInfo &windowInfo);

ImGuiIO&		initImGui(GLFWwindow *window);
void			FrameImGui();
void			OptionImGui(Obj &obj, Camera &cam, WindowInfo &windowInfo, ImGuiIO& io);
void			renderImGui();
void			ShutdownImGui();

unsigned int	initBuffers(Obj &obj);
void			render(Obj &obj, unsigned int &VAO, Shaders &shader);
void			matrixParameters(Shaders &shader);

/*-------- Defines --------*/
