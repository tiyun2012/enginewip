#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

 //ImGui includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>
#include <fstream>
#include <sstream>

#include "imGuiUtils.h"

// Color constants for console output
#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define RESET_TEXT "\033[0m"

GLFWwindow* window;
GLFWwindow* renderWindow;
// Function prototypes
void errorCallback(int error, const char* description);
void buttonCall();
std::string readShaderSource(const char* filePath);
GLuint compileShader(GLenum type, const std::string& source);
GLuint createShaderProgram(const char* vertexFilePath, const char* fragmentFilePath);

int main() {
    // Error callback for GLFW
    glfwSetErrorCallback(errorCallback);

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << RED_TEXT << "Failed to initialize GLFW" << RESET_TEXT << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    window = glfwCreateWindow(1280, 720, "ImGui + GLFW App", nullptr, nullptr);
    if (!window) {
        std::cerr << RED_TEXT << "Failed to create GLFW window" << RESET_TEXT << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << RED_TEXT << "Failed to initialize GLAD" << RESET_TEXT << std::endl;
        return -1;
    }

    // Get and print the OpenGL version
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << GREEN_TEXT << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << RESET_TEXT << std::endl;

    // Initialize ImGui

    ImGuiUtils Initialize_ImGui(window);

    // Shader setup
    GLuint shaderProgram = createShaderProgram("src/vertex_shader.glsl", "src/fragment_shader.glsl");

    // Rectangle setup
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();


        // Clear the screen
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Start ImGui frame
        Initialize_ImGui.startFrame();
        Initialize_ImGui.mainBarMenuBar();
        Initialize_ImGui.testwidget();
        Initialize_ImGui.render();

        // Render rectangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //// Render ImGui draw data
        //Initialize_ImGui.render();

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    Initialize_ImGui.cleanUp();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void errorCallback(int error, const char* description) {
    std::cerr << RED_TEXT << "Error: " << error << " : " << description << RESET_TEXT << std::endl;
}

void buttonCall() {
    std::cout << "Run button pressed" << std::endl;
}

std::string readShaderSource(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(const char* vertexFilePath, const char* fragmentFilePath) {
    std::string vertexCode = readShaderSource(vertexFilePath);
    std::string fragmentCode = readShaderSource(fragmentFilePath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
