#pragma once

class IndexBuffer
{
private:
	//The buffers id
	unsigned int m_RendererID;
	//The number of indicies in the buffer
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};