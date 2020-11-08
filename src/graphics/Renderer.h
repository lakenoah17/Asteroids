#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:
    Shader* shader;
    VertexBuffer* vb;
    VertexArray* vao;
    IndexBuffer* ib;
    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4* mvp;


public:
    Renderer(std::string shaderPath, float *verticies, unsigned int *indicies);
    void Clear() const;
    void Draw() const;
    void Draw(unsigned int drawType) const;
};
