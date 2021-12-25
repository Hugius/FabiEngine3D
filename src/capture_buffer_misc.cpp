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

const ivec2 CaptureBuffer::getSize() const
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

void CaptureBuffer::reset()
{
	if(_isInitialized)
	{
		glDeleteFramebuffers(1, &_fbo);
		glDeleteBuffers(1, &_rbo);

		for(size_t i = 0; i < _textures.size(); i++)
		{
			glDeleteTextures(1, &_textures[i]);
		}

		_isInitialized = false;
	}
}