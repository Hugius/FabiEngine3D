#include "render_framebuffer.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

RenderFramebuffer::~RenderFramebuffer()
{
	reset();
}

void RenderFramebuffer::createMsaaTexture(Ivec2 position, Ivec2 size, int amount, int aaSamples)
{
	// Check if already loaded
	if (!_isInitialized)
	{
		// Dimensions
		_position = position;
		_size = size;

		// Enable OpenGL Anti-Aliasing
		_aaSamples = aaSamples;
		glEnable(GL_MULTISAMPLE);

		// Generate FBO
		glGenFramebuffers(1, &_fbo);

		// Bind
		bind();

		// Texture generation
		for (int i = 0; i < amount; i++)
		{
			_textures.push_back(0);
			glGenTextures(1, &_textures[i]);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _textures[i]);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, aaSamples, GL_RGB, _size.x, _size.y, GL_TRUE);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, _textures[i], 0);
		}

		// Renderbuffers
		glGenRenderbuffers(1, &_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, aaSamples, GL_DEPTH24_STENCIL8, _size.x, _size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

		// Multiple textures
		std::vector<GLuint> attachments;
		for (int i = 0; i < amount; i++)
		{
			attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		glDrawBuffers(amount, &attachments[0]);

		// Unbind
		unbind();

		// Error checking
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Logger::throwError("Framebuffer not initialized properly!");
		}

		_isInitialized = true;
	}
	else
	{
		Logger::throwError("Framebuffer already initialized!");
	}
}

void RenderFramebuffer::createColorTexture(Ivec2 position, Ivec2 size, int amount, bool textureClamp)
{
	// Check if already loaded
	if (!_isInitialized)
	{
		// Dimensions
		_position = position;
		_size = size;

		// Generate FBO
		glGenFramebuffers(1, &_fbo);
		_isInitialized = true;

		// Bind
		bind();

		// Texture generation
		for (int i = 0; i < amount; i++)
		{
			// Add empty texture ID
			_textures.push_back(0);

			// Texture generation
			glGenTextures(1, &_textures[i]);
			glBindTexture(GL_TEXTURE_2D, _textures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _size.x, _size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

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
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _textures[i], 0);
		}

		// Generate RBO
		glGenRenderbuffers(1, &_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _size.x, _size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo);

		// Multiple textures
		std::vector<GLuint> attachments;
		for (int i = 0; i < amount; i++)
		{
			attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		glDrawBuffers(amount, &attachments[0]);

		// Unbind
		unbind();

		// Error checking
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Logger::throwError("Framebuffer not initialized properly!");
		}
	}
	else
	{
		Logger::throwError("Framebuffer already initialized!");
	}
}

void RenderFramebuffer::createDepthTexture(Ivec2 position, Ivec2 size, int amount)
{
	// Check if already loaded
	if (!_isInitialized)
	{
		// Dimensions
		_position = position;
		_size = size;

		// Generate FBO
		glGenFramebuffers(1, &_fbo);
		_isInitialized = true;

		// Bind
		bind();

		// Texture generation
		for (int i = 0; i < amount; i++)
		{
			_textures.push_back(0);
			glGenTextures(1, &_textures[i]);
			glBindTexture(GL_TEXTURE_2D, _textures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, _size.x, _size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			float aniso;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _textures[i], 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}

		// Unbind
		unbind();

		// Error checking
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Logger::throwError("Framebuffer not initialized properly!");
		}
	}
	else
	{
		Logger::throwError("Framebuffer already initialized!");
	}
}

void RenderFramebuffer::reset()
{
	if (_isInitialized)
	{
		// Remove FBO & RBO
		glDeleteFramebuffers(1, &_fbo);
		glDeleteBuffers(1, &_rbo);

		// Remove textures
		for (size_t i = 0; i < _textures.size(); i++)
		{
			glDeleteTextures(1, &_textures[i]);
		}

		// Can recreate FBO texture again
		_isInitialized = false;
	}
}