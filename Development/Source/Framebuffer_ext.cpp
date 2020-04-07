#include <WE3D/Framebuffer.hpp>
#include <WE3D/Configuration.hpp>

//////////////////////
// Bind framebuffer //
//////////////////////
void Framebuffer::bind()
{
	glViewport(0, 0, p_size.x, p_size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, p_fbo);
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
	glBindFramebuffer(GL_READ_FRAMEBUFFER, p_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, renderBuffer->getFBO());
	glBlitFramebuffer(0, 0, GLint(p_size.x), GLint(p_size.y), 0, 0, GLint(p_size.x), GLint(p_size.y), GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

///////////////////////
// Return AA samples //
///////////////////////
int Framebuffer::getAASamples()
{
	return p_aaSamples;
}

/////////////////
// Return size //
/////////////////
ivec2 Framebuffer::getSize()
{
	return p_size;
}

//////////////////////////
// Return actual buffer //
//////////////////////////
GLuint Framebuffer::getFBO()
{
	return p_fbo;
}

////////////////////
// Return texture //
////////////////////
GLuint Framebuffer::getTexture(int ID)
{
	return p_textures[ID];
}