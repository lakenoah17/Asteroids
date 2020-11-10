#include "Renderer.h"
#include "VertexBufferLayout.h"
#include <iostream>

/// <summary>
/// Clears the error log of all possible errors
/// </summary>
void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

/// <summary>
/// Logs OpenGL errors from the log to the console
/// </summary>
/// <param name="function">The name of the function the error occurred in</param>
/// <param name="file">The file the error occurred in</param>
/// <param name="line">The line the error occurred on</param>
/// <returns>Returns false if errors were found true if they weren't</returns>
bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " in " << file << " on line: " << line << std::endl;
        return false;
    }
    return true;
}


/// <summary>
/// Creates a Renderable struct that contains all of the necessary objects for rendering with OpenGL
/// </summary>
/// <param name="shaderPath">The file path to where the shader resource is located</param>
/// <param name="verticies">Array of verticies to use for drawing</param>
/// <param name="verticiesLen">The number length of the verticies array</param>
/// <param name="strideLen">The number of elements each vertex contains</param>
/// <param name="indicies">Array of indicies of the verticies</param>
/// <param name="indiciesLen">The length of the indicies array</param>
/// <returns>A new Renderable object with everything needed for rendering</returns>
Renderable* Renderer::CreateRenderable(std::string shaderPath, float* verticies, unsigned int verticiesLen, unsigned int strideLen, unsigned int* indicies, unsigned int indiciesLen)
{
    VertexArray* vao = new VertexArray;

    Shader* shader = new Shader((const std::string&)shaderPath);

    VertexBuffer* vb = new VertexBuffer(verticies, verticiesLen * sizeof(float));

    VertexBufferLayout layout;


    //Need to make this dynamic
    layout.Push<float>(2);
    layout.Push<float>(2);

    //Adds the vertex buffer to the VAO
    vao->AddBuffer(*vb, layout);

    IndexBuffer* ib = new IndexBuffer(indicies, indiciesLen);

    //Binds the shader so its' color uniform can be set
    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    //Creates a new Renderable struct with the members created by this constructor
    return new Renderable{ shader, vb, vao, ib };
}

/// <summary>
/// Constructs a renderable struct from already defined rendering components
/// </summary>
/// <param name="shader">The shader to use for drawing</param>
/// <param name="vb">The VertexBuffer for the object</param>
/// <param name="vao">The VertexArray of the object</param>
/// <param name="ib">The IndexBuffer of the object</param>
/// <returns>A new Renderable object with everything needed for rendering</returns>
Renderable* Renderer::CreateRenderable(Shader* shader, VertexBuffer* vb, VertexArray* vao, IndexBuffer* ib)
{
    return new Renderable{ shader, vb, vao, ib };
}

/// <summary>
/// Clears the screen of everything
/// </summary>
void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

/// <summary>
/// Draws to the screen using a Renderable struct
/// </summary>
/// <param name="objToRender">The struct to use for rendering</param>
void Renderer::Draw(Renderable* objToRender) const {
    objToRender->BindRenderable();
    objToRender->shader->SetUniformMat4f("u_MVP", objToRender->mvp);

    GLCall(glDrawElements(GL_TRIANGLES, objToRender->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

/// <summary>
/// Draws to the screen using a Renderable struct and a draw type
/// </summary>
/// <param name="objToRender">The struct to use for rendering</param>
/// <param name="drawType">The type of drawing OpenGL will use to render the object</param>
void Renderer::Draw(Renderable* objToRender, unsigned int drawType) const {
    objToRender->BindRenderable();
    objToRender->shader->SetUniformMat4f("u_MVP", objToRender->mvp);
    GLCall(glDrawElements(drawType, objToRender->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}