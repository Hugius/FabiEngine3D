#pragma once

#include <GLM/glm.hpp>
#include <GLEW/glew.h>
#include <vector>

using glm::ivec2;

class OpenGLFramebuffer final
{
public:
	OpenGLFramebuffer() = default;
	~OpenGLFramebuffer();

	void createMsaaTexture (ivec2 position, ivec2 size, int amount, int aaSamples);
	void createColorTexture(ivec2 position, ivec2 size, int amount, bool textureClamp);
	void createDepthTexture(ivec2 position, ivec2 size, int amount);

	void bind();
	void unbind();
	void processAAData(OpenGLFramebuffer * renderBuffer);

	int getAASamples();

	ivec2 getSize();

	GLuint getFBO();
	GLuint getTexture(int ID);

private:
	GLuint _fbo = 0;
	GLuint _rbo = 0;
	std::vector<GLuint> _textures;

	int _aaSamples = 0;
	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	bool _textureInitialized = false;
};