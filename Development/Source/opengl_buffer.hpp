#pragma once

#include <vector>
#include <GLM\\glm.hpp>
#include <GLEW\\glew.h>

using std::vector;
using glm::vec2;
using glm::vec3;
using glm::vec4;

enum class BufferType
{
	MODEL,
	MODEL_TANGENT,
	CUBEMAP,
	SURFACE,
	AABB
};

class OpenGLBuffer final
{
public:
	OpenGLBuffer() = delete;
	OpenGLBuffer(BufferType type, float data[], int dataCount);   // 3D
	OpenGLBuffer(float x, float y, float w, float h, bool centered); // 2D
	~OpenGLBuffer();
	
	void addInstancing(const vector<vec3>& offsets);
	void removeInstancing();

	const GLuint getVAO() const;

	const unsigned int getVertexCount() const;
	const unsigned int getInstancedOffsetCount() const;
	
	const bool isInstanced() const;

	const BufferType getBufferType() const;

	const vector<vec3> getInstancedOffsets() const;

private:
	void _create3D(BufferType type, float data[], int dataCount);
	void _create2D(float x, float y, float w, float h, bool centered);
	
	unsigned int _vertexCount;
	unsigned int _offsetCount;

	bool _isInstanced = false;

	GLuint _vao;
	GLuint _vbo;
	GLuint _vbo_instanced;

	BufferType _bufferType;

	vector<vec3> _instancedOffsets;
};

