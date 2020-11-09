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

Renderable* Renderer::CreateRenderable(std::string shaderPath, float* verticies, unsigned int verticiesLen, unsigned int strideLen, unsigned int* indicies, unsigned int indiciesLen, VertexArray* vao)
{
    Shader* shader = new Shader((const std::string&)shaderPath);

    VertexBuffer* vb = new VertexBuffer(verticies, verticiesLen * sizeof(float));

    if (!vao)
    {
        vao = new VertexArray();
    }

    currVAO = vao;

    VertexBufferLayout layout;

    //Need to make this dynamic
    layout.Push<float>(2);
    layout.Push<float>(2);

    vao->AddBuffer(*vb, layout);

    IndexBuffer* ib = new IndexBuffer(indicies, indiciesLen);

    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    Renderable* renderableObj = new Renderable();

    renderableObj->shader = shader;
    renderableObj->ib = ib;
    renderableObj->vao = vao;
    renderableObj->vb = vb;

    return renderableObj;
}

Renderable* Renderer::CreateRenderable(Shader* shader, VertexBuffer* vb, VertexArray* vao, IndexBuffer* ib)
{
    return new Renderable{shader, vb, vao, ib};
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(glm::mat4 mvp, Renderable* objToRender) const {
    objToRender->BindRenderable();
    objToRender->shader->SetUniformMat4f("u_MVP", mvp);

    GLCall(glDrawElements(GL_TRIANGLES, objToRender->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(glm::mat4 mvp, Renderable* objToRender, unsigned int drawType) const {
    objToRender->BindRenderable();
    objToRender->shader->SetUniformMat4f("u_MVP", mvp);
    GLCall(glDrawElements(drawType, objToRender->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}