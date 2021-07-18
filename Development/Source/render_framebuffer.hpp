#pragma once

#include "mathematics.hpp"

#include <GLEW\\glew.h>
#include <vector>

class RenderFramebuffer final
{
public:
	~RenderFramebuffer();

	void createColorTexture(Ivec2 position, Ivec2 size, unsigned int amount, bool isTextureClamped);
	void createDepthTexture(Ivec2 position, Ivec2 size);
	void reset();

	void bind();
	void unbind();

	Ivec2 getSize();

	GLuint getFBO();
	GLuint getTexture(int ID);

private:
	GLuint _fbo = 0;
	GLuint _rbo = 0;

	std::vector<GLuint> _textures;

	Ivec2 _position = Ivec2(0);
	Ivec2 _size = Ivec2(0);

	bool _isInitialized = false;
};