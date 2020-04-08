#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <shaders.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <map>
#include <text.h>
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <resource_manager.h>
#include <mandelbrot_set.h>
#include <lines.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

// Enable optimus!
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

// Settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

// Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInputs(GLFWwindow* window, Mandelbrot& data);
void getCoordinates(std::string coordinates[], Mandelbrot& data);

int main()
{
    /************************************************************
      ------------- Glfw: initialize and configure --------------
      ***********************************************************/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mandelbrot", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /************************************************************
    ---------------- Instattiate MandelbrotSet shader -----------
    //***********************************************************/
    Shader mandelbrotShader = ResourceManager::GetShader("mandelbrot");
    ResourceManager::GetShader("mandelbrot").Use(); //.SetInteger("mandelbrot", 0);
    MandelbrotSet* Mandelbrot = new MandelbrotSet(mandelbrotShader);

    /************************************************************
    ------------------- Instattiate line shader -----------------
    //***********************************************************/
    Shader lineShader = ResourceManager::GetShader("lines");
    ResourceManager::GetShader("lines").Use().SetInteger("lines", 0);
    Lines* Line = new Lines(lineShader);

    /************************************************************
    ------------------------ Set font -------------------------
    //***********************************************************/
    TextRenderer* Text = new TextRenderer(SCR_WIDTH, SCR_HEIGHT);
    Text->Load(25);

    int width, height;
    std::string coordinates[2];

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // track window size
        glfwGetWindowSize(window, &width, &height);
        // input
        processInputs(window, Mandelbrot->data);
        glClear(GL_COLOR_BUFFER_BIT);

        Mandelbrot->Update(width, height, Mandelbrot->data);
        Line->DrawLines();
        
        getCoordinates(coordinates, Mandelbrot->data);
        Text->RenderText("x:" + coordinates[0], 5.0f, 5.0f, 1.0f);
        Text->RenderText("i:" + coordinates[1], 5.0f, 40.0f, 1.0f);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInputs(GLFWwindow* window, Mandelbrot& data)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);    
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        data.zoom -= -2.0f * data.zoom + data.x + data.scale_x < 0.01f ? 0.005f : 0.01f;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        data.zoom += -2.0f * data.zoom + data.x + data.scale_x < 0.01f ? 0.005f : 0.01f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        data.scale_y += -2.0f * data.zoom + data.x + data.scale_x < 0.01f ? 0.005f : 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        data.scale_y -= -2.0f * data.zoom + data.x + data.scale_x < 0.01f ? 0.005f : 0.01f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        data.scale_x += -2.0f * data.zoom + data.x + data.scale_x < 0.01f ? 0.005f : 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        data.scale_x -= -2.0f * data.zoom + data.x + data.scale_x < 0.01f ? 0.005f : 0.01f;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        ++data.max_iterations;    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        --data.max_iterations;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void getCoordinates(std::string coordinates[], Mandelbrot& data)
{
    std::stringstream ss;
    ss << ((-2.0f * data.zoom + data.x + data.scale_x) + (1.0f * data.zoom + data.x + data.scale_x)) / 2 << " "
       << ((-1.0f * data.zoom + data.y + data.scale_y) + (1.0f * data.zoom + data.y + data.scale_y)) / 2;
    std::string x, i; 
    ss >> x >> i;
    coordinates[0] = x;
    coordinates[1] = i;
}

