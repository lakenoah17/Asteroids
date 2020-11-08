#include "Renderer.h"
#include "VertexBufferLayout.h"
#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " in " << file << " on line: " << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer(std::string shaderPath, float* verticies, unsigned int verticiesLen, unsigned int strideLen, unsigned int* indicies, unsigned int indiciesLen) {
    
    shader = new Shader((const std::string&)shaderPath);

    //Sets up all of the matrices for a Model View Projection Matrix hardcoded atm
    proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
    mvp = &(proj * view * model);

    vb = new VertexBuffer(verticies, verticiesLen * sizeof(float));

    vao = new VertexArray();

    VertexBufferLayout layout;

    //Need to make this dynamic
    layout.Push<float>(strideLen);

    vao->AddBuffer(*vb, layout);
    
    ib = new IndexBuffer(indicies, indiciesLen);

    shader->Bind();
    shader->SetUniformMat4f("u_MVP", *mvp);
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

Renderer::~Renderer()
{
    delete shader;
    delete vb;
    delete vao;
    delete ib;
    delete mvp;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw() const {
    shader->Bind();
    vao->Bind();
    ib->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(unsigned int drawType) const {
    shader->Bind();
    vao->Bind();
    ib->Bind();
    GLCall(glDrawElements(drawType, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}