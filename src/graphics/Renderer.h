#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "glm/gtc/matrix_transform.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

struct Renderable {
    Shader* shader;
    VertexBuffer* vb;
    VertexArray* vao;
    IndexBuffer* ib;
};

class Renderer {
public:
    ~Renderer();
    Renderable CreateRenderable(std::string shaderPath, float* verticies, unsigned int verticiesLen, unsigned int strideLen, unsigned int* indicies, unsigned int indiciesLen);
    void Clear() const;
    void Draw(glm::mat4 mvp, Renderable objToRender) const;
    void Draw(glm::mat4 mvp, Renderable objToRender, unsigned int drawType) const;
};
