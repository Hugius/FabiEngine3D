#include "render_framebuffer.hpp"
#include "configuration.hpp"

void RenderFramebuffer::bind()
{
	glViewport(_position.x, _position.y, _size.x, _size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void RenderFramebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
}

Ivec2 RenderFramebuffer::getSize()
{
	return _size;
}

GLuint RenderFramebuffer::getFBO()
{
	return _fbo;
}

GLuint RenderFramebuffer::getTexture(int ID)
{
	return _textures[ID];
}