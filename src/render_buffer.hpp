#pragma once

#include "buffer_type.hpp"
#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class RenderBuffer final
{
public:
	RenderBuffer(RenderBufferType type, const float data[], unsigned int dataCount); // 3D
	RenderBuffer(float x, float y, float w, float h, bool isCentered); // 2D
	~RenderBuffer();

	// UNSIGNED INT
	const unsigned int getVertexCount() const;

	// MISCELLANEOUS
	const BufferID getVAO() const;
	const RenderBufferType getBufferType() const;

private:
	// UNSIGNED INT
	unsigned int _vertexCount = 0;

	// MISCELLANEOUS
	RenderBufferType _bufferType;
	BufferID _vao = 0;
	BufferID _vbo = 0;
};

