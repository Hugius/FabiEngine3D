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

Ivec2 CaptureBuffer::getSize()
{
	return _size;
}

BufferID CaptureBuffer::getFBO()
{
	return _fbo;
}

BufferID CaptureBuffer::getTexture(unsigned int index)
{
	return _textures[index];
}