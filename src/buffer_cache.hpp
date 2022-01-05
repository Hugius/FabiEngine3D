#pragma once

#include "shader_buffer.hpp"
#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"
#include "capture_buffer.hpp"

class BufferCache final
{
public:
	void storeTextureBuffer(const string& filePath, shared_ptr<TextureBuffer> textureBuffer);

	//shared_ptr<ShaderBuffer> getShaderBuffer();
	//shared_ptr<VertexBuffer> getVertexBuffer();
	shared_ptr<TextureBuffer> getTextureBuffer(const string& filePath);
	//shared_ptr<CaptureBuffer> getCaptureBuffer();

private:
	map<string, shared_ptr<ShaderBuffer>> _shaderBufferCache;
	map<string, shared_ptr<VertexBuffer>> _vertexBufferCache;
	map<string, shared_ptr<TextureBuffer>> _textureBufferCache;
	map<string, shared_ptr<CaptureBuffer>> _captureBufferCache;
};