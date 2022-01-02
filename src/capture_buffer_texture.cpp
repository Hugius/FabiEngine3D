#include "capture_buffer.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "render_bus.hpp"

CaptureBuffer::~CaptureBuffer()
{
	reset();
}

void CaptureBuffer::createColorTexture(ivec2 position, ivec2 size, unsigned int count, bool isTextureClamped)
{
	if(!_isInitialized)
	{
		_position = position;
		_size = size;

		glGenFramebuffers(1, &_fbo);
		_isInitialized = true;

		bind();

		for(unsigned int i = 0; i < count; i++)
		{
			_textures.push_back(0);

			glGenTextures(1, &_textures[i]);

			glBindTexture(GL_TEXTURE_2D, _textures[i]);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _size.x, _size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

			if(isTextureClamped)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _textures[i], 0);
		}

		glGenRenderbuffers(1, &_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _size.x, _size.y);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo);

		vector<BufferID> attachments;
		for(unsigned int i = 0; i < count; i++)
		{
			attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		glDrawBuffers(count, &attachments[0]);

		unbind();

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Logger::throwError("CaptureBuffer::createColorTexture::1");
		}
	}
	else
	{
		Logger::throwError("CaptureBuffer::createColorTexture::2");
	}
}

void CaptureBuffer::createDepthTexture(ivec2 position, ivec2 size)
{
	if(!_isInitialized)
	{
		_position = position;
		_size = size;

		glGenFramebuffers(1, &_fbo);
		_isInitialized = true;

		bind();

		_textures.push_back(0);

		glGenTextures(1, &_textures[0]);

		glBindTexture(GL_TEXTURE_2D, _textures[0]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _size.x, _size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		const float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _textures[0], 0);

		unbind();

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Logger::throwError("CaptureBuffer::createDepthTexture::1");
		}
	}
	else
	{
		Logger::throwError("CaptureBuffer::createDepthTexture::2");
	}
}