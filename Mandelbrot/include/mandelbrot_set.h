#pragma once
#ifndef MANDELBROT_SET_H
#define MANDELBROT_SET_H

#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/gtc/type_ptr.hpp>

#include <resource_manager.h>
#include <shaders.h>

// Mandelbrot params
struct Mandelbrot
{
    float x;
    float y;
    float scale_x;
    float scale_y;
    float zoom;
    int max_iterations;
};

class MandelbrotSet
{
public:
    //Constructor
    MandelbrotSet(Shader &shader);
    
    // Create data set
    Mandelbrot data {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 75};

    // Pre-compiles a list of characters from the given font
    void Update(int& width, int& heigth, Mandelbrot& data);

    // Destructor
    ~MandelbrotSet();
private:
    // Render state
    Shader shader;
    GLuint VAO, VBO, EBO;
    // Initializes and configures vertex attributes
    void initRenderData();

    const char* vertex_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\vertex_shader.vs";
    const char* fragment_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\fragment_shader.fs";
};

#endif 