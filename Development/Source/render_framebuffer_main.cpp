#include "render_framebuffer.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

RenderFramebuffer::~RenderFramebuffer()
{
	reset();
}

void RenderFramebuffer::createColorTexture(Ivec2 position, Ivec2 size, unsigned int amount, bool isTextureClamped)
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
		for (unsigned int i = 0; i < amount; i++)
		{
			// Add empty texture ID
			_textures.push_back(0);

			// Create texture
			glGenTextures(1, &_textures[i]);

			// Bind texture
			glBindTexture(GL_TEXTURE_2D, _textures[i]);

			// Fill texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _size.x, _size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

			// Texture clamping
			if (isTextureClamped)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			// Texture filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Unbind texture
			glBindTexture(GL_TEXTURE_2D, 0);

			// Put texture in framebuffer
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
		for (unsigned int i = 0; i < amount; i++)
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

void RenderFramebuffer::createDepthTexture(Ivec2 position, Ivec2 size)
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

		// Add empty texture ID
		_textures.push_back(0);

		// Create texture
		glGenTextures(1, &_textures[0]);

		// Bind texture
		glBindTexture(GL_TEXTURE_2D, _textures[0]);

		// Fill texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _size.x, _size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

		// Texture clamping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		// Texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Texture border
		const float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

		// Put texture in framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _textures[0], 0);

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