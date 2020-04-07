#include <iostream>

#include <glm/glm/gtc/matrix_transform.hpp>
#include <text.h>
#include <mandelbrot_set.h>

MandelbrotSet::MandelbrotSet(Shader& shader)
{
    // Load and configure shader
    this->shader = ResourceManager::LoadShader(vertex_shader, fragment_shader, nullptr, "mandelbrot");
    this->initRenderData();
}

void MandelbrotSet::Update(int& width, int& heigth, Mandelbrot& data)
{
    this->shader.Use();
    this->shader.SetFloat("rect_width", width);
    this->shader.SetFloat("rect_height", width);
    this->shader.SetVector2f("area_w", -2.0f * data.zoom + data.x + data.scale_x,  1.0f * data.zoom + data.x + data.scale_x);
    this->shader.SetVector2f("area_h", -0.9f * data.zoom + data.y + data.scale_y,  1.4f * data.zoom + data.y + data.scale_y);
    this->shader.SetInteger("max_iterations", data.max_iterations);

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void MandelbrotSet::initRenderData()
{
    constexpr float vertices[] = {
        //positions
        1.0f,   1.0f,  0.0F,  // top right 
        1.0f,  -1.0f,  0.0F,  // bottom right
       -1.0f,  -1.0f,  0.0F,  // bottom left
       -1.0f,   1.0f,  0.0F   // top left
    };

    constexpr unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    /* VBO - vertex buffer objects
       glBindBuffer(GL_ARRAY_BUFFER, VBO) - binds VBO to GL_ARRAY_BUFFER
       glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW) - a function specifically targeted to copy user-defined data into
                                                                                   the currently bound buffe -> (target, size of data in bytes, actual data
       Actual data:
         *GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times,
         *GL_STATIC_DRAW: the data is set only once and used many times,
         *GL_DYNAMIC_DRAW: the data is changed a lot and used many times.*/
    this->shader.Use();
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    glBindVertexArray(this->VAO);

    // Rectangle buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Indices buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*  tell OpenGL how it should interpret the vertex data
        glVertexAttribPointer(vertex attribute we want to configure - location = 0, size of the vertex attribute,
        type of the data, pecifies if we want the data to be normalized, stride - tells us the space between consecutive vertex attributes,
        offset of where the position data begins in the buffe)*/
        // position attribute
    //glBindVertexArray(this->VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MandelbrotSet::~MandelbrotSet()
{

    glDeleteVertexArrays(1, &this->VAO);
}