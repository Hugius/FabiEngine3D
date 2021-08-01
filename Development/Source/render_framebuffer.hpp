#pragma once

#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

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

	BufferID getFBO();
	TextureID getTexture(int ID);

private:
	BufferID _fbo = 0;
	BufferID _rbo = 0;

	vector<TextureID> _textures;

	Ivec2 _position = Ivec2(0);
	Ivec2 _size = Ivec2(0);

	bool _isInitialized = false;
};