#pragma once

#include "buffer_type.hpp"
#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class RenderBuffer final
{
public:
	RenderBuffer() = delete;
	RenderBuffer(BufferType type, float data[], unsigned int dataCount);   // 3D
	RenderBuffer(float x, float y, float w, float h, bool isCentered, bool isText); // 2D
	~RenderBuffer();
	
	void addInstancing(const vector<Vec3>& offsets);
	void removeInstancing();

	const BufferID getVAO() const;

	const unsigned int getVertexCount() const;
	const unsigned int getInstancedOffsetCount() const;
	
	const bool isInstanced() const;

	const BufferType getBufferType() const;

	const vector<Vec3>& getInstancedOffsets() const;

private:
	void _create3D(BufferType type, float data[], unsigned int dataCount);
	void _create2D(float x, float y, float w, float h, bool isCentered, bool isText);
	
	unsigned int _vertexCount = 0;
	unsigned int _offsetCount = 0;

	bool _isInstanced = false;

	BufferID _vao = 0;
	BufferID _vbo = 0;
	BufferID _vbo_instanced = 0;

	BufferType _bufferType = BufferType();

	vector<Vec3> _instancedOffsets;
};

