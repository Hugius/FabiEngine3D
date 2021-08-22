#include "render_buffer.hpp"
#include "logger.hpp"

RenderBuffer::RenderBuffer(RenderBufferType type, const float data[], unsigned int dataCount)
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
	case RenderBufferType::VERTEX:
	{
		_vertexCount = dataCount / 3;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		break;
	}
	case RenderBufferType::VERTEX_UV:
	{
		_vertexCount = dataCount / 5;
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		break;
	}
	case RenderBufferType::VERTEX_UV_NORMAL:
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
	case RenderBufferType::VERTEX_UV_NORMAL_TANGENT:
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
	}

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

RenderBuffer::RenderBuffer(float x, float y, float w, float h, bool isCentered)
{
	// Temporary values
	float* data = nullptr;

	// Set buffer type
	_bufferType = RenderBufferType::VERTEX_UV;

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
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

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

void RenderBuffer::enableInstancing(const vector<Vec3>& offsets)
{
	if (_isInstanced)
	{
		Logger::throwError("RenderBuffer::enableInstancing::1");
	}
	else
	{
		// Validate offsets
		if (offsets.empty())
		{
			Logger::throwError("RenderBuffer::enableInstancing::2");
		}

		// Create buffers
		glGenBuffers(1, &_vbo_instanced);

		// Bind buffers
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo_instanced);

		// Allocate buffer data
		glBufferData(GL_ARRAY_BUFFER, (offsets.size() * sizeof(Vec3)), &offsets[0], GL_STATIC_DRAW);

		// Store buffer data
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glVertexAttribDivisor(4, 1);

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Miscellaneous
		_isInstanced = true;
		_instancedOffsets = offsets;
	}
}

void RenderBuffer::disableInstancing()
{
	if (_isInstanced)
	{
		glDeleteBuffers(1, &_vbo_instanced);
		_isInstanced = false;
		_instancedOffsets.clear();
	}
	else
	{
		Logger::throwError("RenderBuffer::disableInstancing");
	}
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

const RenderBufferType RenderBuffer::getBufferType()
{
	return _bufferType;
}

const vector<Vec3>& RenderBuffer::getInstancedOffsets()
{
	return _instancedOffsets;
}