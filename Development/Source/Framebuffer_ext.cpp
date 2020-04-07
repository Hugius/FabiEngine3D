#include "Framebuffer.hpp"
#include "Configuration.hpp"

//////////////////////
// Bind framebuffer //
//////////////////////
void Framebuffer::bind()
{
	glViewport(0, 0, _size.x, _size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

///////////////////////
// Unind framebuffer //
///////////////////////
void Framebuffer::unbind()
{
	glViewport(0, 0, Config::getInst().getWindowWidth(), Config::getInst().getWindowHeight());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/////////////////////////////////////////////////////////////////////////////////
// Convert current framebuffer texture to AA texture and store in renderbuffer //
/////////////////////////////////////////////////////////////////////////////////
void Framebuffer::processAAData(Framebuffer * renderBuffer)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, renderBuffer->getFBO());
	glBlitFramebuffer(0, 0, GLint(_size.x), GLint(_size.y), 0, 0, GLint(_size.x), GLint(_size.y), GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

///////////////////////
// Return AA samples //
///////////////////////
int Framebuffer::getAASamples()
{
	return _aaSamples;
}

/////////////////
// Return size //
/////////////////
ivec2 Framebuffer::getSize()
{
	return _size;
}

//////////////////////////
// Return actual buffer //
//////////////////////////
GLuint Framebuffer::getFBO()
{
	return _fbo;
}

////////////////////
// Return texture //
////////////////////
GLuint Framebuffer::getTexture(int ID)
{
	return _textures[ID];
}