#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class ImGuiUtils
{
public:
	ImGuiUtils(GLFWwindow*);
	void startFrame();
	void mainBarMenuBar();
	void testwidget();
	void render();
	void cleanUp();
	
	~ImGuiUtils();

private:
	GLFWwindow* parentWindow;

};
