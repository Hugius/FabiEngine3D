#include "vertex_buffer.hpp"

VertexBuffer::VertexBuffer(VertexBufferType type, const float data[], int dataCount)
{
	_bufferType = type;

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &_vboId);
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, (dataCount * sizeof(float)), &data[0], GL_STATIC_DRAW);

	switch(type)
	{
		case VertexBufferType::POS:
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(float)), (GLvoid *)(0 * sizeof(float)));

			_vertexCount = dataCount / 3;

			break;
		}
		case VertexBufferType::POS_UV:
		{
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (GLvoid *)(0 * sizeof(float)));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (GLvoid *)(3 * sizeof(float)));

			_vertexCount = dataCount / 5;

			break;
		}
		case VertexBufferType::POS_UV_NOR:
		{
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid *)(0 * sizeof(float)));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid *)(3 * sizeof(float)));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(float)), (GLvoid *)(5 * sizeof(float)));

			_vertexCount = dataCount / 8;

			break;
		}
		case VertexBufferType::POS_UV_NOR_TAN:
		{
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (GLvoid *)(0 * sizeof(float)));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (GLvoid *)(3 * sizeof(float)));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (GLvoid *)(5 * sizeof(float)));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, (11 * sizeof(float)), (GLvoid *)(8 * sizeof(float)));

			_vertexCount = dataCount / 11;

			break;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexBuffer::VertexBuffer(float x, float y, float w, float h, bool isCentered)
{
	float * vertices = nullptr;

	_bufferType = VertexBufferType::POS_UV;

	if(isCentered)
	{
		vertices = new float[24]
		{
			(x - (w * 0.5f)), (y - (h * 0.5f)), 0.0f, 0.0f,
				(x + (w * 0.5f)), (y - (h * 0.5f)), 1.0f, 0.0f,
				(x + (w * 0.5f)), (y + (h * 0.5f)), 1.0f, 1.0f,

				(x + (w * 0.5f)), (y + (h * 0.5f)), 1.0f, 1.0f,
				(x - (w * 0.5f)), (y + (h * 0.5f)), 0.0f, 1.0f,
				(x - (w * 0.5f)), (y - (h * 0.5f)), 0.0f, 0.0f
		};
	}
	else
	{
		vertices = new float[24]
		{
			x, y, 0.0f, 0.0f,
				x + w, y, 1.0f, 0.0f,
				x + w, y + h, 1.0f, 1.0f,

				x + w, y + h, 1.0f, 1.0f,
				x, y + h, 0.0f, 1.0f,
				x, y, 0.0f, 0.0f
		};
	}

	glGenVertexArrays(1, &_vaoId);
	glGenBuffers(1, &_vboId);
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	glBufferData(GL_ARRAY_BUFFER, (24 * sizeof(float)), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(float)), (GLvoid *)(0 * sizeof(float)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (4 * sizeof(float)), (GLvoid *)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	delete[] vertices;

	_vertexCount = 6;
}

VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &_vaoId);
	glDeleteBuffers(1, &_vboId);
}

const unsigned int VertexBuffer::getVaoId() const
{
	return _vaoId;
}

const unsigned int VertexBuffer::getVboId() const
{
	return _vboId;
}

const int VertexBuffer::getVertexCount() const
{
	return _vertexCount;
}

const VertexBufferType VertexBuffer::getBufferType() const
{
	return _bufferType;
}