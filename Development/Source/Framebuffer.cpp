#include <vector>
#include <GLEW/glew.h>

#include <WE3D/Framebuffer.hpp>
#include <WE3D/Logger.hpp>
#include <WE3D/Configuration.hpp>
#include <WE3D/ShaderBus.hpp>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

////////////////
// Destructor //
////////////////
Framebuffer::~Framebuffer()
{
	if (p_textureInitialized) 
	{
		glDeleteFramebuffers(1, &p_fbo);
		glDeleteBuffers(1, &p_rbo);
		glDeleteTextures(1, &p_textures[0]);
		glDeleteTextures(1, &p_textures[1]);
	}

}

//////////////////////////////////
// Create Anti Aliasing texture //
//////////////////////////////////
void Framebuffer::createMsaaTexture(ivec2 size, int amount, int aaSamples)
{
	p_size = size;

	// Enable OpenGL Anti-Aliasing
	p_aaSamples = aaSamples;
	glEnable(GL_MULTISAMPLE);

	// Initialize
	if (!p_textureInitialized) 
	{
		glGenFramebuffers(1, &p_fbo);
		p_textureInitialized = true;
	}
	
	// Bind
	bind();

	// Texture generation
	for (int i = 0; i < amount; i++)
	{
		p_textures.push_back(0);
		glGenTextures(1, &p_textures[i]);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, p_textures[i]);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, aaSamples, GL_RGBA16, p_size.x, p_size.y, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, p_textures[i], 0);
	}

	// Renderbuffers
	glGenRenderbuffers(1, &p_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, p_rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, aaSamples, GL_DEPTH24_STENCIL8, p_size.x, p_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, p_rbo);

	// Unbind
	unbind();

	// Error checking
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		Logger::getInst().throwError("Framebuffer not initialized properly!");
	}
}

//////////////////////////
// Create color texture //
//////////////////////////
void Framebuffer::createColorTexture(ivec2 size, int amount, bool textureClamp)
{
	p_size = size;

	// Frame buffer object
	if (!p_textureInitialized)
	{
		glGenFramebuffers(1, &p_fbo);
		p_textureInitialized = true;
	}
	
	// Bind
	bind();

	// Texture generation
	for (int i = 0; i < amount; i++)
	{
		p_textures.push_back(0);

		// Texture generation
		glGenTextures(1, &p_textures[i]);
		glBindTexture(GL_TEXTURE_2D, p_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, p_size.x, p_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		// Optional texture clamp
		if (textureClamp)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		// Texture filtering
		float aniso;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, p_textures[i], 0);
	}

	// Render buffer object
	glGenRenderbuffers(1, &p_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, p_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, p_size.x, p_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, p_rbo);

	// Multiple textures
	std::vector<GLuint> attachments;
	for (int i = 0; i < amount; i++)
	{
		attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
	}

	glDrawBuffers(amount, &attachments[0]);

	unbind();

	// Error checking
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		Logger::getInst().throwError("Framebuffer not initialized properly!");
	}
}

//////////////////////////
// Create depth texture //
//////////////////////////
void Framebuffer::createDepthTexture(ivec2 size, int amount)
{
	p_size = size;

	if (!p_textureInitialized)
	{
		glGenFramebuffers(1, &p_fbo);
		p_textureInitialized = true;
	}

	bind();

	for (int i = 0; i < amount; i++)
	{
		p_textures.push_back(0);
		glGenTextures(1, &p_textures[i]);
		glBindTexture(GL_TEXTURE_2D, p_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, p_size.x, p_size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		float aniso;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, p_textures[i], 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	unbind();

	// Error checking
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		Logger::getInst().throwError("Framebuffer not initialized properly!");
	}
}