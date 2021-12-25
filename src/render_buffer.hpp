#pragma once

#include "buffer_type.hpp"
#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class RenderBuffer final
{
public:
	RenderBuffer(RenderBufferType type, const float data[], unsigned int dataCount);
	RenderBuffer(float x, float y, float w, float h, bool isCentered);
	~RenderBuffer();

	const unsigned int getVertexCount() const;

	const BufferID getVAO() const;
	const RenderBufferType getBufferType() const;

private:
	unsigned int _vertexCount = 0;

	RenderBufferType _bufferType;
	BufferID _vao = 0;
	BufferID _vbo = 0;
};

