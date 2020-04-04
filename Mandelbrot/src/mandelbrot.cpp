#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <shaders.h>

// enable optimus!
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    const char* vertex_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\vertex_shader.vs";
    const char *fragment_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\fragment_shader.fs";
    Shader shader(vertex_shader, fragment_shader);

    constexpr float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    };

    /* VBO - vertex buffer objects  
       glBindBuffer(GL_ARRAY_BUFFER, VBO) - binds VBO to GL_ARRAY_BUFFER
       glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW) - a function specifically targeted to copy user-defined data into 
                                                                                   the currently bound buffe -> (target, size of data in bytes, actual data
       Actual data: 
         *GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times,
         *GL_STATIC_DRAW: the data is set only once and used many times,
         *GL_DYNAMIC_DRAW: the data is changed a lot and used many times.

    0. bind Vertex Array Object
    1. copy our vertices array in a buffer for OpenGL to use 
    */
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
   
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /*  tell OpenGL how it should interpret the vertex data
    glVertexAttribPointer(vertex attribute we want to configure - location = 0, size of the vertex attribute,
                          type of the data, pecifies if we want the data to be normalized, stride - tells us the space between consecutive vertex attributes,
                          offset of where the position data begins in the buffe)
    1. then set the vertex attributes pointers
    */

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glUseProgram(ID); 
    shader.use();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 2. use our shader program when we want to render an object
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}