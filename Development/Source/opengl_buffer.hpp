#pragma once

#include <vector>
#include <GLM\\glm.hpp>
#include <GLEW\\glew.h>

using std::vector;
using glm::vec3;

enum ShapeType
{
	SHAPE_3D,
	SHAPE_CUBEMAP,
	SHAPE_SURFACE,
	SHAPE_AABB
};

class OpenGLBuffer final
{
public:
	OpenGLBuffer() = default;
	OpenGLBuffer(int type, float data[], int dataCount);   // 3D
	OpenGLBuffer(float data[], int dataCount, const vector<vec3> & offsets); // 3D instanced
	OpenGLBuffer(float x, float y, float w, float h, bool centered); // 2D
	~OpenGLBuffer();
	
	const GLuint getVAO() const;

	const int getVertexCount() const;
	const int getOffsetCount() const;
	
	const bool isInstanced() const;

private:
	void _create3D(int type, float data[], int dataCount);
	void _create3D_instanced(float data[], int dataCount, const vector<vec3> & offsets);
	void _create2D(float x, float y, float w, float h, bool centered);
	
	int _vertexCount;
	int _offsetCount;

	bool _isInstanced = false;

	GLuint _vao;
	GLuint _vbo;
	GLuint _vbo_instanced;
};

