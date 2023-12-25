#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imGuiUtils.h"
#include "testFuction.h"

ImGuiUtils::ImGuiUtils(GLFWwindow* window)
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    std::cout << "successful initializing Imgui"<<std::endl;

    // set variable
    parentWindow = window;
}

void ImGuiUtils::startFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiUtils::mainBarMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Close", "Ctrl+W")) { glfwSetWindowShouldClose(parentWindow, 1); }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void ImGuiUtils::testwidget()
{
    ImGui::Begin("Demo window");


        static int sliderValue = 10;
        ImGui::SliderInt("Slider", &sliderValue, 0, 100);
        static float f = 0.5;
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        const static int intTextA = 1995;
        ImGui::Text("Hello, world %d", intTextA);
        //const static float spacing = 4;
        //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

        ImGui::SameLine(0.0f, -10.0f);
        if (ImGui::Button("run"))buttonCalling();
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

        // Set the item spacing to 10 pixels in both x and y directions
        const static float spacing = 20;
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(sliderValue, spacing));

        // Now create some widgets
        if (ImGui::Button("Button 1"))
        {
            // Handle button click
        }

        ImGui::SameLine();

        if (ImGui::Button("Button 2"))
        {
            // Handle button click
        }

        // Don't forget to pop the style variable when you're done with it!
        ImGui::PopStyleVar();

    //->end
    ImGui::End();
}

void ImGuiUtils::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ImGuiUtils::cleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

ImGuiUtils::~ImGuiUtils()
{
    std::cout << "remove IMGUI"<<std::endl;
}
