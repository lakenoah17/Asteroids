#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

/// <summary>
/// Contructs the VertexArray
/// </summary>
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

/// <summary>
/// Destroys the VertexArray
/// </summary>
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

/// <summary>
/// Adds a Vertex buffer to the VertexArray
/// </summary>
/// <param name="vb">The buffer to add</param>
/// <param name="layout">The layout of the buffer</param>
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	//Binds the VAO before the VBO
	Bind();
	vb.Bind();

	//Gets the elements of the VBO
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	// Loops through the VAO adding the elements from the vb
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));

		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *) offset));

		//The offset of bytes from the start of the vbo
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

/// <summary>
/// Binds the VAO to be the current one being used
/// </summary>
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

/// <summary>
/// Unbinds the VAO from the program
/// </summary>
void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
