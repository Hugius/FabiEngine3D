#pragma once

#include "vertex_buffer_type.hpp"
#include "mathematics.hpp"

#include <vector>
#include <glew.h>

using std::vector;

using BufferId = GLuint;

class VertexBuffer final
{
public:
	VertexBuffer(VertexBufferType type, const float data[], unsigned int dataCount);
	VertexBuffer(float x, float y, float w, float h, bool isCentered);
	~VertexBuffer();

	const unsigned int getVertexCount() const;

	const BufferId getVaoId() const;
	const BufferId getVboId() const;

	const VertexBufferType getBufferType() const;

private:
	unsigned int _vertexCount = 0;

	VertexBufferType _bufferType;

	BufferId _vaoId = 0;
	BufferId _vboId = 0;
};