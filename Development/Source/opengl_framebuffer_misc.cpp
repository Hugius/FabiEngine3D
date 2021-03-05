#include "opengl_framebuffer.hpp"
#include "configuration.hpp"

//////////////////////
// Bind framebuffer //
//////////////////////
void OpenGLFramebuffer::bind()
{
	glViewport(_position.x, _position.y, _size.x, _size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

///////////////////////
// Unind framebuffer //
///////////////////////
void OpenGLFramebuffer::unbind()
{
	glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/////////////////////////////////////////////////////////////////////////////////
// Convert current framebuffer texture to AA texture and store in renderbuffer //
/////////////////////////////////////////////////////////////////////////////////
void OpenGLFramebuffer::processAAData(OpenGLFramebuffer* renderBuffer)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, renderBuffer->getFBO());
	glBlitFramebuffer(0, 0, GLint(_size.x), GLint(_size.y), 0, 0, GLint(_size.x), GLint(_size.y), GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

///////////////////////
// Return AA samples //
///////////////////////
int OpenGLFramebuffer::getAASamples()
{
	return _aaSamples;
}

/////////////////
// Return size //
/////////////////
Ivec2 OpenGLFramebuffer::getSize()
{
	return _size;
}

//////////////////////////
// Return actual buffer //
//////////////////////////
GLuint OpenGLFramebuffer::getFBO()
{
	return _fbo;
}

////////////////////
// Return texture //
////////////////////
GLuint OpenGLFramebuffer::getTexture(int ID)
{
	return _textures[ID];
}