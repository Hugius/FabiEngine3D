#include "blur_renderer.hpp"
#include "render_storage.hpp"
#include "tools.hpp"

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

const shared_ptr<TextureBuffer> BlurRenderer::blurTexture(const shared_ptr<Quad2d> quad2d, shared_ptr<TextureBuffer> texture, int blurCount, float intensity, BlurDirectionType direction)
{
	_shaderBuffer->uploadUniform("u_intensity", intensity);

	if((direction == BlurDirectionType::BOTH) || (direction == BlurDirectionType::HORIZONTAL))
	{
		_shaderBuffer->uploadUniform("u_isHorizontal", true);

		for(int index = 0; index < blurCount; index++)
		{
			_captureBuffer->bind();

			_render(quad2d, texture);

			_captureBuffer->unbind();

			texture = _captureBuffer->getTexture(0);
		}
	}

	if((direction == BlurDirectionType::BOTH) || (direction == BlurDirectionType::VERTICAL))
	{
		_shaderBuffer->uploadUniform("u_isHorizontal", false);

		for(int index = 0; index < blurCount; index++)
		{
			_captureBuffer->bind();

			_render(quad2d, texture);

			_captureBuffer->unbind();

			texture = _captureBuffer->getTexture(0);
		}
	}

	return texture;
}

void BlurRenderer::_render(const shared_ptr<Quad2d> quad2d, shared_ptr<TextureBuffer> texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getTboId());
	glBindVertexArray(quad2d->getVertexBuffer()->getVaoId());
	glDrawArrays(GL_TRIANGLES, 0, quad2d->getVertexBuffer()->getVertexCount());
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}