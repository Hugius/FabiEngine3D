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

	// VOID
	void enableInstancing(const vector<fvec3>& offsets);
	void disableInstancing();

	// FVEC3
	const vector<fvec3>& getInstancedOffsets() const;

	// UNSIGNED INT
	const unsigned int getVertexCount() const;

	// BOOL
	const bool isInstanced() const;

	// Miscellaneous
	const BufferID getVAO() const;
	const RenderBufferType getBufferType() const;

private:
	// FVEC3
	vector<fvec3> _instancedOffsets;

	// UNSIGNED INT
	unsigned int _vertexCount = 0;
	unsigned int _offsetCount = 0;

	// BOOL
	bool _isInstanced = false;

	// Miscellaneous
	RenderBufferType _bufferType;
	BufferID _vao = 0;
	BufferID _vbo = 0;
	BufferID _vbo_instanced = 0;
};

