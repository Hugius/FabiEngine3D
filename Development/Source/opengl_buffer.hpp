#pragma once

#include "buffer_type.hpp"
#include "mathematics.hpp"

#include <vector>
#include <GLEW\\glew.h>

using std::vector;

class OpenGLBuffer final
{
public:
	OpenGLBuffer() = delete;
	OpenGLBuffer(BufferType type, float data[], int dataCount);   // 3D
	OpenGLBuffer(float x, float y, float w, float h, bool isCentered, bool isText); // 2D
	~OpenGLBuffer();
	
	void addInstancing(const vector<Vec3>& offsets);
	void removeInstancing();

	const GLuint getVAO() const;

	const unsigned int getVertexCount() const;
	const unsigned int getInstancedOffsetCount() const;
	
	const bool isInstanced() const;

	const BufferType getBufferType() const;

	const vector<Vec3>& getInstancedOffsets() const;

private:
	void _create3D(BufferType type, float data[], int dataCount);
	void _create2D(float x, float y, float w, float h, bool isCentered, bool isText);
	
	unsigned int _vertexCount;
	unsigned int _offsetCount;

	bool _isInstanced = false;

	GLuint _vao;
	GLuint _vbo;
	GLuint _vbo_instanced;

	BufferType _bufferType;

	vector<Vec3> _instancedOffsets;
};

