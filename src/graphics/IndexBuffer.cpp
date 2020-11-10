#include "IndexBuffer.h"

#include "Renderer.h"

/// <summary>
/// Constructs an index buffer
/// </summary>
/// <param name="data">The indicies to be used for the index buffer</param>
/// <param name="count">The number of indicies there are in the array</param>
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

/// <summary>
/// Makes sure the buffer doesn't cause a memory leak
/// </summary>
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

/// <summary>
/// Binds this index buffer to be the current one
/// </summary>
void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

/// <summary>
/// Unbinds this index buffer from the program
/// </summary>
void IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
