#include "blur_renderer.hpp"
#include "render_storage.hpp"
#include "configuration.hpp"

using std::make_shared;

void BlurRenderer::inject(shared_ptr<CaptureBuffer> captureBuffer)
{
	_captureBuffer = captureBuffer;
}

void BlurRenderer::bind()
{
	_shaderBuffer->bind();

	_shaderBuffer->uploadUniform("u_diffuseMap", 0);
}

void BlurRenderer::unbind()
{
	_shaderBuffer->unbind();
}

const shared_ptr<TextureBuffer> BlurRenderer::blurTexture(const shared_ptr<Quad2dEntity> entity, shared_ptr<TextureBuffer> texture, unsigned int blurCount, float intensity, BlurDirectionType direction)
{
	_shaderBuffer->uploadUniform("u_intensity", intensity);

	if((direction == BlurDirectionType::BOTH) || (direction == BlurDirectionType::HORIZONTAL))
	{
		_shaderBuffer->uploadUniform("u_isHorizontal", true);

		for(unsigned int index = 0; index < blurCount; index++)
		{
			_captureBuffer->bind();
			_render(entity, texture);
			_captureBuffer->unbind();
			texture = _captureBuffer->getTexture(0);
		}
	}

	if((direction == BlurDirectionType::BOTH) || (direction == BlurDirectionType::VERTICAL))
	{
		_shaderBuffer->uploadUniform("u_isHorizontal", false);

		for(unsigned int index = 0; index < blurCount; index++)
		{
			_captureBuffer->bind();
			_render(entity, texture);
			_captureBuffer->unbind();
			texture = _captureBuffer->getTexture(0);
		}
	}

	return texture;
}

void BlurRenderer::_render(const shared_ptr<Quad2dEntity> entity, shared_ptr<TextureBuffer> texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTboId());

	glBindVertexArray(entity->getVertexBuffer()->getVaoId());

	glDrawArrays(GL_TRIANGLES, 0, entity->getVertexBuffer()->getVertexCount());

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}