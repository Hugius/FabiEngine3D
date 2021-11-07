#include "capture_buffer.hpp"
#include "configuration.hpp"

void CaptureBuffer::bind()
{
	glViewport(_position.x, _position.y, _size.x, _size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void CaptureBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
}

const Ivec2 CaptureBuffer::getSize() const
{
	return _size;
}

const BufferID CaptureBuffer::getFBO() const
{
	return _fbo;
}

const BufferID CaptureBuffer::getTexture(unsigned int index) const
{
	return _textures[index];
}