#include<iostream>
//#include<Windows.h>
#include<glad\glad.h>
#include<GLFW\glfw3.h>
//color consol
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define RESET_TEXT "\033[0m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[96m"

GLFWwindow* window;
std::string* nameA;


int main()
{
	//Set Error callback
	glfwSetErrorCallback(errorCallback);
	// check if glfwInit
	if (!glfwInit())
	{
		std::cerr << "failed to initialize window";
		return -1;
	}
	else
	{
		std::cout <<GREEN_TEXT<< "glfwInit works"<<RESET_TEXT<<std::endl;
	}
	// Set GLFW to not create an OpenGL context (we will use glad to load the OpenGL functions)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(800, 600, "My App", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "failed to initial GlFW";
		// cleanup and deallocation, window and context destruction, even system clean up
		glfwTerminate();
		return -1;
	}
	//make the window's context current
	glfwMakeContextCurrent(window);
	//load openGl function using glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize glad" << std::endl;
	}
	//mainloop
	int numbers = 0;
	while (!glfwWindowShouldClose(window))
	{
		//update
		std::cout << numbers++ << std::endl;


		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
		return 0;
}

void errorCallback(int error, const char* description)
{
	std::cerr << "error: " << error << " : " << description << std::endl;
}