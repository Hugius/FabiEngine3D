#pragma once

#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class CaptureBuffer final
{
public:
	~CaptureBuffer();

	// VOID
	void createColorTexture(ivec2 position, ivec2 size, unsigned int count, bool isTextureClamped);
	void createDepthTexture(ivec2 position, ivec2 size);
	void reset();
	void bind();
	void unbind();

	// FVEC2
	const ivec2 getSize() const;

	// MISCELLANEOUS
	const BufferID getFBO() const;
	const TextureID getTexture(unsigned int index) const;

private:
	// FVEC2
	ivec2 _position = ivec2(0);
	ivec2 _size = ivec2(0);

	// BOOL
	bool _isInitialized = false;

	// MISCELLANEOUS
	vector<TextureID> _textures;
	BufferID _fbo = 0;
	BufferID _rbo = 0;
};