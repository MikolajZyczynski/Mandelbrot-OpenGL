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
    //DrawShader;
    Shader DrawShader;
    
    // Create data set
    Mandelbrot data {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 75};

    // Shaders paths
    const char* vertex_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\vertex_shader.vs";
    const char* fragment_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\fragment_shader.fs";

    // Constructor
    MandelbrotSet();
    // Pre-compiles a list of characters from the given font
    //void DrawRenderer();
    void Update(int& width, int& heigth, Mandelbrot& data);
    void Load();
    // Renders a string of text using the precompiled list of characters
    //void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

    // Destructor
    ~MandelbrotSet();
private:
    // Render state
    GLuint VAO, VBO, EBO;

};

#endif 