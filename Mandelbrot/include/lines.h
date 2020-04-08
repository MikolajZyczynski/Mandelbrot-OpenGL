#pragma once
#pragma once
#ifndef LINES_H
#define LINES_H

#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/gtc/type_ptr.hpp>

#include <resource_manager.h>
#include <shaders.h>


class Lines
{
public:
    //Constructor
    Lines(Shader& shader);

    // Draws lines
    void DrawLines();

    // Destructor
    ~Lines();
private:
    // Render state
    Shader shader;
    GLuint VAO, VBO;
    // Initializes and configures vertex attributes
    void initRenderData();

    const char* lines_vs__shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\lines.vs";
    const char* lines_fs_shader = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\lines.fs";
};

#endif 