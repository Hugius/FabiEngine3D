#pragma once

#define GLEW_STATIC

#include "vertex_buffer_type.hpp"
#include "mathematics.hpp"

#include <vector>
#include <glew.h>

using std::vector;

class VertexBuffer final
{
public:
	VertexBuffer(VertexBufferType type, const float data[], int dataCount);
	VertexBuffer(float x, float y, float w, float h, bool isCentered);
	~VertexBuffer();

	const unsigned int getVaoId() const;
	const unsigned int getVboId() const;

	const int getVertexCount() const;

	const VertexBufferType getBufferType() const;

private:
	unsigned int _vaoId = 0;
	unsigned int _vboId = 0;

	int _vertexCount = 0;

	VertexBufferType _bufferType = {};
};