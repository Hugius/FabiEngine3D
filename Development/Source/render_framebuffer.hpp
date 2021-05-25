#pragma once

#include "mathematics.hpp"

#include <GLEW\\glew.h>
#include <vector>

class RenderFramebuffer final
{
public:
	~RenderFramebuffer();

	void createMsaaTexture (Ivec2 position, Ivec2 size, int amount, int aaSamples);
	void createColorTexture(Ivec2 position, Ivec2 size, int amount, bool textureClamp);
	void createDepthTexture(Ivec2 position, Ivec2 size, int amount);
	void reset();

	void bind();
	void unbind();
	void processAAData(RenderFramebuffer * renderBuffer);

	int getAASamples();

	Ivec2 getSize();

	GLuint getFBO();
	GLuint getTexture(int ID);

private:
	GLuint _fbo = 0;
	GLuint _rbo = 0;

	std::vector<GLuint> _textures;

	int _aaSamples = 0;

	Ivec2 _position = Ivec2(0);
	Ivec2 _size = Ivec2(0);

	bool _isInitialized = false;
};