#include "render_framebuffer.hpp"
#include "configuration.hpp"

//////////////////////
// Bind framebuffer //
//////////////////////
void RenderFramebuffer::bind()
{
	glViewport(_position.x, _position.y, _size.x, _size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

///////////////////////
// Unind framebuffer //
///////////////////////
void RenderFramebuffer::unbind()
{
	glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/////////////////////////////////////////////////////////////////////////////////
// Convert current framebuffer texture to AA texture and store in renderbuffer //
/////////////////////////////////////////////////////////////////////////////////
void RenderFramebuffer::processAAData(RenderFramebuffer* renderBuffer)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, renderBuffer->getFBO());
	glBlitFramebuffer(0, 0, GLint(_size.x), GLint(_size.y), 0, 0, GLint(_size.x), GLint(_size.y), GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

///////////////////////
// Return AA samples //
///////////////////////
int RenderFramebuffer::getAASamples()
{
	return _aaSamples;
}

/////////////////
// Return size //
/////////////////
Ivec2 RenderFramebuffer::getSize()
{
	return _size;
}

//////////////////////////
// Return actual buffer //
//////////////////////////
GLuint RenderFramebuffer::getFBO()
{
	return _fbo;
}

////////////////////
// Return texture //
////////////////////
GLuint RenderFramebuffer::getTexture(int ID)
{
	return _textures[ID];
}