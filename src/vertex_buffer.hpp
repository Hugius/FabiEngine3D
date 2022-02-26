#pragma once

#include "vertex_buffer_type.hpp"
#include "mathematics.hpp"

#include <vector>
#include <glew.h>

using std::vector;

class VertexBuffer final
{
public:
	VertexBuffer(VertexBufferType type, const float data[], unsigned int dataCount);
	VertexBuffer(float x, float y, float w, float h, bool isCentered);
	~VertexBuffer();

	const unsigned int getVertexCount() const;

	const unsigned int getVaoId() const;
	const unsigned int getVboId() const;

	const VertexBufferType getBufferType() const;

private:
	unsigned int _vertexCount = 0;

	VertexBufferType _bufferType;

	unsigned int _vaoId = 0;
	unsigned int _vboId = 0;
};