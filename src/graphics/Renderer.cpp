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

Renderable Renderer::CreateRenderable(std::string shaderPath, float* verticies, unsigned int verticiesLen, unsigned int strideLen, unsigned int* indicies, unsigned int indiciesLen)
{
    Shader* shader = new Shader((const std::string&)shaderPath);

    VertexBuffer* vb = new VertexBuffer(verticies, verticiesLen * sizeof(float));

    VertexArray* vao = new VertexArray();

    VertexBufferLayout layout;

    //Need to make this dynamic
    layout.Push<float>(2);
    layout.Push<float>(2);

    vao->AddBuffer(*vb, layout);

    IndexBuffer* ib = new IndexBuffer(indicies, indiciesLen);

    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    Renderable renderableObj;

    renderableObj.shader = shader;
    renderableObj.ib = ib;
    renderableObj.vao = vao;
    renderableObj.vb = vb;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(glm::mat4 mvp, Renderable objToRender) const {
    objToRender.shader->Bind();
    objToRender.shader->SetUniformMat4f("u_MVP", mvp);
    objToRender.vao->Bind();
    objToRender.ib->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, objToRender.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(glm::mat4 mvp, Renderable objToRender, unsigned int drawType) const {
    objToRender.shader->Bind();
    objToRender.shader->SetUniformMat4f("u_MVP", mvp);
    objToRender.vao->Bind();
    objToRender.ib->Bind();
    GLCall(glDrawElements(drawType, objToRender.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}