#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ImGui includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Color constants for console output
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define RESET_TEXT "\033[0m"
//GLFW
GLFWwindow* window;
//imgui

void errorCallback(int error, const char* description);
void buttonCall();
int main() {

    // trace glfw error

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        std::cerr << RED_TEXT << "Failed to initialize GLFW" << RESET_TEXT << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ImGui + GLFW App", nullptr, nullptr);
    if (!window) {
        std::cerr << RED_TEXT << "Failed to create GLFW window" << RESET_TEXT << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << RED_TEXT << "Failed to initialize GLAD" << RESET_TEXT << std::endl;
        return -1;
    }
    // Get the OpenGL version
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    std::cout <<GREEN_TEXT<< "Renderer: " << RED_TEXT << renderer << std::endl;
    std::cout <<GREEN_TEXT<< "OpenGL version supported: " <<RED_TEXT<< version << RESET_TEXT<<std::endl;

    // ImGui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //imgui variable initialization
    
    
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui content
        ImGui::Begin("Demo window");
             static int sliderValue = 10;
            ImGui::SliderInt("Slider", &sliderValue, 0, 100);
            static float f = 0.5;
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            const static int intTextA = 1995;
            ImGui::Text("Hello, world %d", intTextA);
            //const static float spacing = 4;
            //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

            ImGui::SameLine(0.0f,-10.0f);
            if(ImGui::Button("run"))buttonCall();
            // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
            //IMGUI_DEMO_MARKER("Widgets/Basic/Buttons (Colored)");
            for (int i = 0; i < 7; i++)
            {
                if (i > 0)
                    ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
                ImGui::Button("Click");
                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }

        //->end
        ImGui::End();

        // Rendering
        //  ---Imgui
        ImGui::Render();
        //  ---glfw
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    //   --imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    //   --glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


void errorCallback(int error, const char* description) {
    std::cerr << RED_TEXT << "Error: " << error << " : " << description << RESET_TEXT << std::endl;
}
void buttonCall()
{
    std::cout << "run button calling" << std::endl;
};
