#include "capture_buffer.hpp"
#include "configuration.hpp"
#include "render_storage.hpp"

using std::make_shared;

CaptureBuffer::~CaptureBuffer()
{
	glDeleteFramebuffers(1, &_fboId);
	glDeleteBuffers(1, &_rboId);
}

CaptureBuffer::CaptureBuffer(const ivec2 & position, const ivec2 & size, unsigned int count, bool isTextureClamped)
{
	_position = position;
	_size = size;

	glGenFramebuffers(1, &_fboId);

	bind();

	for(unsigned int index = 0; index < count; index++)
	{
		unsigned int textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _size.x, _size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (isTextureClamped ? GL_CLAMP_TO_EDGE : GL_REPEAT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (isTextureClamped ? GL_CLAMP_TO_EDGE : GL_REPEAT));
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, textureId, 0);

		_textures.push_back(make_shared<TextureBuffer>(textureId));
	}

	glGenRenderbuffers(1, &_rboId);
	glBindRenderbuffer(GL_RENDERBUFFER, _rboId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _size.x, _size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rboId);

	vector<unsigned int> attachments;
	for(unsigned int index = 0; index < count; index++)
	{
		attachments.push_back(GL_COLOR_ATTACHMENT0 + index);
	}
	glDrawBuffers(count, &attachments[0]);

	unbind();

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		abort();
	}
}

CaptureBuffer::CaptureBuffer(const ivec2 & position, const ivec2 & size)
{
	_position = position;
	_size = size;

	glGenFramebuffers(1, &_fboId);

	bind();

	unsigned int textureId;
	glGenTextures(1, &textureId);
	_textures.push_back(make_shared<TextureBuffer>(textureId));

	glBindTexture(GL_TEXTURE_2D, _textures[0]->getTboId());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _size.x, _size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	const float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _textures[0]->getTboId(), 0);

	unbind();

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		abort();
	}
}

void CaptureBuffer::bind()
{
	glViewport(_position.x, _position.y, _size.x, _size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
}

void CaptureBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Configuration::getInst().getWindowSize().x, Configuration::getInst().getWindowSize().y);
}

const ivec2 & CaptureBuffer::getPosition() const
{
	return _position;
}

const ivec2 & CaptureBuffer::getSize() const
{
	return _size;
}

const int CaptureBuffer::getFboId() const
{
	return _fboId;
}

const int CaptureBuffer::getRboId() const
{
	return _rboId;
}

const shared_ptr<TextureBuffer> CaptureBuffer::getTexture(unsigned int index) const
{
	return _textures[index];
}