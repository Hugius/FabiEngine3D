#pragma once

#include <GLM/glm.hpp>
#include <GLEW/glew.h>
#include <vector>

using glm::ivec2;

class Framebuffer final
{
public:
	Framebuffer() = default;
	~Framebuffer();

	void createMsaaTexture (ivec2 size, int amount, int aaSamples);
	void createColorTexture(ivec2 size, int amount, bool textureClamp);
	void createDepthTexture(ivec2 size, int amount);

	void bind();
	void unbind();
	void processAAData(Framebuffer * renderBuffer);

	int getAASamples();

	ivec2 getSize();

	GLuint getFBO();
	GLuint getTexture(int ID);

private:
	GLuint p_fbo = 0;
	GLuint p_rbo = 0;
	std::vector<GLuint> p_textures;

	int p_aaSamples = 0;
	ivec2 p_size = ivec2(0);

	bool p_textureInitialized = false;
};