#include "render_buffer.hpp"

RenderBuffer::RenderBuffer(BufferType type, const float data[], unsigned int dataCount)
{
	// Set buffer type
	_bufferType = type;
	
	// Create buffers
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	// Bind buffers
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Allocate buffer data
	glBufferData(GL_ARRAY_BUFFER, (dataCount * sizeof(float)), &data[0], GL_STATIC_DRAW);

	// Store buffer data
	switch (type)
	{
	case BufferType::MODEL:
	{
		_vertexCount = dataCount / 8;
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));
		break;
	}
	case BufferType::MODEL_TANGENT:
	{
		_vertexCount = dataCount / 11;
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(5 * sizeof(float)));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(8 * sizeof(float)));
		break;
	}
	case BufferType::SURFACE:
	{
		_vertexCount = dataCount / 5;
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		break;
	}
	case BufferType::AABB:
	{
		_vertexCount = dataCount / 3;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		break;
	}
	case BufferType::CUBEMAP:
	{
		_vertexCount = dataCount / 3;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		break;
	}
	}

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

RenderBuffer::RenderBuffer(float x, float y, float w, float h, bool isCentered, bool isText)
{
	// Temporary values
	float* data = nullptr;

	// Determine center point of the quad
	if (isCentered)
	{
		data = new float[24]
		{
			x - (w / 2.0f) , y - (h / 2.0f) , 0.0f, 0.0f,
			x + (w / 2.0f) , y - (h / 2.0f) , 1.0f, 0.0f,
			x + (w / 2.0f) , y + (h / 2.0f) , 1.0f, 1.0f,

			x + (w / 2.0f) , y + (h / 2.0f) , 1.0f, 1.0f,
			x - (w / 2.0f) , y + (h / 2.0f) , 0.0f, 1.0f,
			x - (w / 2.0f) , y - (h / 2.0f) , 0.0f, 0.0f
		};
	}
	else
	{
		data = new float[24]
		{
			x,     y,     0.0f, 0.0f,
			x + w, y,     1.0f, 0.0f,
			x + w, y + h, 1.0f, 1.0f,

			x + w, y + h, 1.0f, 1.0f,
			x,     y + h, 0.0f, 1.0f,
			x,     y,     0.0f, 0.0f
		};
	}

	// Create buffers
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	// Bind buffers
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Allocate buffer data
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &data[0], GL_STATIC_DRAW);

	// Store buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_vertexCount = 6;
}

RenderBuffer::~RenderBuffer()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_vbo_instanced);
}

void RenderBuffer::addInstancing(const vector<Vec3>& offsets)
{
	// Create instanced VBO
	glGenBuffers(1, &_vbo_instanced);

	// Bind VAO
	glBindVertexArray(_vao);

	// Bind instanced VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo_instanced);
	glBufferData(GL_ARRAY_BUFFER, (offsets.size() * sizeof(Vec3)), &offsets[0], GL_STATIC_DRAW);

	// Fill instanced VBO
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Miscellaneous
	_isInstanced = true;
	_instancedOffsets = offsets;
}

void RenderBuffer::removeInstancing()
{
	glDeleteBuffers(1, &_vbo_instanced);
	_isInstanced = false;
	_instancedOffsets.clear();
}

const BufferID RenderBuffer::getVAO()
{
	return _vao;
}

const unsigned int RenderBuffer::getVertexCount()
{
	return _vertexCount;
}

const bool RenderBuffer::isInstanced()
{
	return _isInstanced;
}

const BufferType RenderBuffer::getBufferType()
{
	return _bufferType;
}

const vector<Vec3>& RenderBuffer::getInstancedOffsets()
{
	return _instancedOffsets;
}