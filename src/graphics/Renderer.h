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


/// <summary>
/// Stores all of the components of a draw call
/// </summary>
struct Renderable {
    Shader* shader;
    VertexBuffer* vb;
    VertexArray* vao;
    IndexBuffer* ib;

    //Sets up all of the matrices for a Model View Projection Matrix hardcoded to start
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp = proj * view * model;

    void BindRenderable() {
        vao->Bind();
    }
};

class Renderer {
public:
    static Renderable* CreateRenderable(std::string shaderPath, float* verticies, 
                                        unsigned int verticiesLen, unsigned int strideLen,
                                        unsigned int* indicies, unsigned int indiciesLen);

    static Renderable* CreateRenderable(Shader* shader, VertexBuffer* vb, VertexArray* vao, IndexBuffer* ib);

    void Clear() const;
    void Draw(Renderable* objToRender) const;
    void Draw(Renderable* objToRender, unsigned int drawType) const;
};
