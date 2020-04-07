#include <WE3D/OpenGLBuffer.hpp>

// 3D
OpenGLBuffer::OpenGLBuffer(int type, float data[], int dataCount)
{
	p_create3D(type, data, dataCount);
}

OpenGLBuffer::OpenGLBuffer(float data[], int dataCount, const vector<vec3> & offsets)
{
	p_create3D_instanced(data, dataCount, offsets);
}

// 2D
OpenGLBuffer::OpenGLBuffer(float x, float y, float w, float h, bool centered)
{
	p_create2D(x, y, w, h, centered);
}

void OpenGLBuffer::p_create3D(int type, float data[], int dataCount)
{
	// Create buffers
	glGenVertexArrays(1, &p_vao);
	glGenBuffers(1, &p_vbo);

	// Bind buffers
	glBindVertexArray(p_vao);
	glBindBuffer(GL_ARRAY_BUFFER, p_vbo);

	// Allocate buffer dataCount
	glBufferData(GL_ARRAY_BUFFER, dataCount * sizeof(float), &data[0], GL_STATIC_DRAW);

	// Store buffer data
	switch (type)
	{
	case SHAPE_3D: // Fill 3D buffers
		p_vertexCount = dataCount / 8;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
		break;

	case SHAPE_SURFACE: // Fill surface buffers
		p_vertexCount = dataCount / 5;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		break;

	case SHAPE_AABB: // Fill AABB buffers
		p_vertexCount = dataCount / 3;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		break;

	case SHAPE_CUBEMAP: // Fill cubemap buffers
		p_vertexCount = dataCount / 3;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		break;
	}

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGLBuffer::p_create3D_instanced(float data[], int dataCount, const vector<vec3> & offsets)
{
	// Create 3D
	p_create3D(SHAPE_3D, data, dataCount);

	// Create instanced VBO
	glGenBuffers(1, &p_vbo_instanced);

	// Bind VAO
	glBindVertexArray(p_vao);

	// Bind instanced VBO
	glBindBuffer(GL_ARRAY_BUFFER, p_vbo_instanced);
	glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(vec3), &offsets[0], GL_STATIC_DRAW);

	// Fill instanced VBO
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Other
	p_isInstanced = true;
	p_offsetCount = offsets.size();
}

void OpenGLBuffer::p_create2D(float x, float y, float w, float h, bool centered)
{
	// Generate vertices
	float* data = nullptr;

	if (centered)
	{
		data = new float[24]
		{
			x - (w / 2.0f) , y - (h / 2.0f) , 0.0f, 0.0f,
			x + (w / 2.0f) , y - (h / 2.0f) , 1.0f, 0.0f,
			x + (w / 2.0f) , y + (h / 2.0f) , 1.0f, 1.0f,

			x + (w / 2.0f) , y + (h / 2.0f) , 1.0f, 1.0,
			x - (w / 2.0f) , y + (h / 2.0f) , 0.0f, 1.0,
			x - (w / 2.0f) , y - (h / 2.0f) , 0.0f, 0.0f
		};
	}
	else
	{
		data = new float[24]
		{
			x, y, 0.0f, 0.0f,
			x + w, y, 1.0f, 0.0f,
			x + w, y + h, 1.0f, 1.0f,

			x + w, y + h, 1.0f, 1.0,
			x, y + h, 0.0f, 1.0,
			x, y, 0.0f, 0.0f
		};
	}

	// Create buffers
	glGenVertexArrays(1, &p_vao);
	glGenBuffers(1, &p_vbo);

	// Bind buffers
	glBindVertexArray(p_vao);
	glBindBuffer(GL_ARRAY_BUFFER, p_vbo);

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

	p_vertexCount = 6;
}

OpenGLBuffer::~OpenGLBuffer()
{
	glDeleteVertexArrays(1, &p_vao);
	glDeleteBuffers(1, &p_vbo);
	glDeleteBuffers(1, &p_vbo_instanced);
}

const GLuint OpenGLBuffer::getVAO() const
{
	return p_vao;
}

const int OpenGLBuffer::getVertexCount() const
{
	return p_vertexCount;
}

const int OpenGLBuffer::getOffsetCount() const
{
	return p_offsetCount;
}

const bool OpenGLBuffer::isInstanced() const
{
	return p_isInstanced;
}