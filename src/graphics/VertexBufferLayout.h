#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

/// <summary>
/// Struct allowing for ease of getting size in bytes of elements
/// </summary>
struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:   return 4;
		case GL_UNSIGNED_BYTE:  return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	/// <summary>
	/// Constructs the layout
	/// </summary>
	VertexBufferLayout()
		: m_Stride(0) {}

	/// <summary>
	/// If the type hasn't been specified it will throw an error
	/// </summary>
	/// <typeparam name="T">Generic type to push</typeparam>
	/// <param name="count">The number of elements of type T to push</param>
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	/// <summary>
	/// Pushes floats to the layout
	/// </summary>
	/// <param name="count">The number of floats to push</param>
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	/// <summary>
	/// Pushes unsigned ints to the layout
	/// </summary>
	/// <param name="count">The number of uints to push</param>
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	/// <summary>
	/// Pushes unsigned chars to the layout
	/// </summary>
	/// <param name="count">The number of uchars to push</param>
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};