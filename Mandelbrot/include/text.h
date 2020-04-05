#pragma once
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/gtc/type_ptr.hpp>

#include <resource_manager.h>
#include <shaders.h>

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};

// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
    //TextShader;
    Shader TextShader;
    // Shaders paths
    const char* text_vs = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\text.vs";
    const char* text_fs = "C:\\Users\\Varth\\Desktop\\-\\Projekty\\OpenGL\\Mandelbrot\\shaders\\text.fs";
    // Holds a list of pre-compiled Characters
    std::map<GLchar, Character> Characters;
    // Constructor
    TextRenderer(GLuint width, GLuint height);
    // Pre-compiles a list of characters from the given font
    void Load(std::string font, GLuint fontSize);
    // Renders a string of text using the precompiled list of characters
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

    ~TextRenderer();

private:
    // Render state
   GLuint VAO, VBO;
};

#endif 