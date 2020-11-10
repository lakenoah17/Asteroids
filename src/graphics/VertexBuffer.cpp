#include "VertexBuffer.h"

#include "Renderer.h"

/// <summary>
/// Constructs a new VertexBuffer
/// </summary>
/// <param name="data">The data to use in the buffer</param>
/// <param name="size">The size in bytes of the buffer</param>
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

/// <summary>
/// Deletes the buffer from memory
/// </summary>
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

/// <summary>
/// Binds the buffer to be the current one
/// </summary>
void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

/// <summary>
/// Unbinds the buffer from the program
/// </summary>
void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
