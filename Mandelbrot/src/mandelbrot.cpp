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
#include <sstream>
#include <iostream>
#include <fstream>

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

int main()
{
    /************************************************************
      ------------- Glfw: initialize and configure --------------
      ***********************************************************/
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

    ///************************************************************
    // -------------------- Create rectangle ----------------------
    // ***********************************************************/
    //constexpr float vertices[] = {
    //    //positions
    //    1.0f,   1.0f,  0.0F,  // top right 
    //    1.0f,  -1.0f,  0.0F,  // bottom right
    //   -1.0f,  -1.0f,  0.0F,  // bottom left
    //   -1.0f,   1.0f,  0.0F   // top left
    //};

    //constexpr unsigned int indices[] = {
    //    0, 1, 3, // first triangle
    //    1, 2, 3  // second triangle
    //};

    ///* VBO - vertex buffer objects
    //   glBindBuffer(GL_ARRAY_BUFFER, VBO) - binds VBO to GL_ARRAY_BUFFER
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW) - a function specifically targeted to copy user-defined data into
    //                                                                               the currently bound buffe -> (target, size of data in bytes, actual data
    //   Actual data:
    //     *GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times,
    //     *GL_STATIC_DRAW: the data is set only once and used many times,
    //     *GL_DYNAMIC_DRAW: the data is changed a lot and used many times.*/
    //GLuint VAO, VBO,EBO;
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    //glBindVertexArray(VAO);
    //
    //// Rectangle buffer
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  
    //// Indices buffer
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    ///*  tell OpenGL how it should interpret the vertex data
    //    glVertexAttribPointer(vertex attribute we want to configure - location = 0, size of the vertex attribute,
    //    type of the data, pecifies if we want the data to be normalized, stride - tells us the space between consecutive vertex attributes,
    //    offset of where the position data begins in the buffe)*/
    //// position attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);


    /************************************************************
    ------------------------ Set font -------------------------
    //***********************************************************/
    // Shaders paths
    Shader shader = ResourceManager::GetShader("mandelbrot");
    ResourceManager::GetShader("mandelbrot").Use().SetInteger("mandelbrot", 0);
    MandelbrotSet* Mandelbrot = new MandelbrotSet(shader);

    TextRenderer* Text = new TextRenderer(SCR_WIDTH, SCR_HEIGHT);
    Text->Load(25);

    //Shader Shader;
    //Shader.load(vertex_shader, fragment_shader);
    //Mandelbrot* data = new Mandelbrot{0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 50};
   
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glUseProgram(ID); 
    int width, height;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // track window size
        glfwGetWindowSize(window, &width, &height);
        // input
        processInputs(window, Mandelbrot->data);
        glClear(GL_COLOR_BUFFER_BIT);

        Mandelbrot->Update(width, height, Mandelbrot->data);
        //glUniform1f(0, width);
        //glUniform1f(1, height);
        //glUniform2f(2, 
        //           -2.0f * data->zoom + data->x + data->scale_x, 
        //            1.0f * data->zoom + data->x + data->scale_x);
        //glUniform2f(3, 
        //           -1.2f * data->zoom + data->y + data->scale_y, 
        //            1.2f * data->zoom + data->y + data->scale_y);
        //glUniform1ui(4, data->max_iterations);

        //glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        std::stringstream ss; ss << (-2.0f * Mandelbrot->data.zoom + Mandelbrot->data.x + Mandelbrot->data.scale_x);
        Text->RenderText("x:" + ss.str(), 5.0f, 5.0f, 1.0f);
        ss << (-2.0f * Mandelbrot->data.zoom + Mandelbrot->data.x + Mandelbrot->data.scale_x);
        Text->RenderText("y:" + ss.str(), 5.0f, 40.0f, 1.0f);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

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

//void RenderText(Shader& s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
//{
//    // Activate corresponding render state	
//    s.use();
//    glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(VAO);
//
//    // Iterate through all characters
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        Character ch = Characters[*c];
//
//        GLfloat xpos = x + ch.Bearing.x * scale;
//        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        GLfloat w = ch.Size.x * scale;
//        GLfloat h = ch.Size.y * scale;
//        // Update VBO for each character
//        GLfloat vertices[6][4] = {
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos,     ypos,       0.0, 1.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//            { xpos + w, ypos + h,   1.0, 0.0 }
//        };
//        // Render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        // Update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        // Render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}