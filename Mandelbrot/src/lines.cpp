#include <iostream>

#include <glm/glm/gtc/matrix_transform.hpp>
#include <text.h>
#include <lines.h>

Lines::Lines(Shader& shader)
{
    // Load and configure shader
    this->shader = ResourceManager::LoadShader(lines_vs__shader, lines_fs_shader, nullptr, "lines");
    this->initRenderData();
}

void Lines::DrawLines()
{
    this->shader.Use();
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_LINES, 0, 4);
}

void Lines::initRenderData()
{

    float linesVertex[] = {
     0.0f, 0.03f, 0.0f,
     0.0f, -0.03f, 0.0f,
    -0.02f, 0.0f, 0.0f,
     0.02f, 0.0f, 0.0f
    };

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), linesVertex, GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, this->VBO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

Lines::~Lines()
{
    glDeleteVertexArrays(1, &this->VAO);
}