#include "master_renderer.hpp"
#include "render_storage.hpp"

void MasterRenderer::captureWorldDepth()
{
	if(!_renderStorage->isDofEnabled() && !_renderStorage->isLensFlareEnabled())
	{
		_renderStorage->setDepthMap(nullptr);

		return;
	}

	_worldDepthCaptureBuffer->bind();

	glClear(GL_DEPTH_BUFFER_BIT);

	if(_terrainManager->getSelectedTerrain() != nullptr)
	{
		_terrainDepthRenderer->bind();

		_terrainDepthRenderer->render(_terrainManager->getSelectedTerrain());

		_terrainDepthRenderer->unbind();
	}

	if(_waterManager->getSelectedWater() != nullptr)
	{
		_waterDepthRenderer->bind();

		_waterDepthRenderer->render(_waterManager->getSelectedWater());

		_waterDepthRenderer->unbind();
	}

	if(!_modelManager->getModels().empty())
	{
		_modelDepthRenderer->bind();

		for(const auto & [modelId, model] : _modelManager->getModels())
		{
			if(model->isLevelOfDetailed())
			{
				auto foundPair = _modelManager->getModels().find(model->getLevelOfDetailId());

				if(foundPair != _modelManager->getModels().end())
				{
					const auto levelOfDetailModel = _modelManager->getModels().find(model->getLevelOfDetailId())->second;
					const auto originalPosition = levelOfDetailModel->getBasePosition();
					const auto originalRotation = levelOfDetailModel->getBaseRotation();
					const auto originalSize = levelOfDetailModel->getBaseSize();
					const auto originalVisibility = levelOfDetailModel->isVisible();

					levelOfDetailModel->setBasePosition(model->getBasePosition());
					levelOfDetailModel->setBaseRotation(model->getBaseRotation());
					levelOfDetailModel->setBaseSize(model->getBaseSize());
					levelOfDetailModel->setVisible(model->isVisible());
					levelOfDetailModel->updateTransformation();

					_modelDepthRenderer->render(levelOfDetailModel);

					levelOfDetailModel->setBasePosition(originalPosition);
					levelOfDetailModel->setBaseRotation(originalRotation);
					levelOfDetailModel->setBaseSize(originalSize);
					levelOfDetailModel->setVisible(originalVisibility);
					levelOfDetailModel->updateTransformation();
				}
				else
				{
					abort();
				}
			}
			else
			{
				_modelDepthRenderer->render(model);
			}
		}

		_modelDepthRenderer->unbind();
	}

	if(!_quad3dManager->getQuad3ds().empty())
	{
		_quad3dDepthRenderer->bind();

		for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
		{
			_quad3dDepthRenderer->render(quad3d);
		}

		_quad3dDepthRenderer->unbind();
	}

	if(!_text3dManager->getText3ds().empty())
	{
		_quad3dDepthRenderer->bind();

		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			for(const auto & quad3d : text3d->getQuad3ds())
			{
				_quad3dDepthRenderer->render(quad3d);
			}
		}

		_quad3dDepthRenderer->unbind();
	}

	if(!_aabbManager->getAabbs().empty())
	{
		_aabbDepthRenderer->bind();

		for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
		{
			_aabbDepthRenderer->render(aabb);
		}

		_aabbDepthRenderer->unbind();
	}

	_worldDepthCaptureBuffer->unbind();

	_renderStorage->setDepthMap(_worldDepthCaptureBuffer->getTexture(0));
}

void MasterRenderer::captureDof()
{
	if(_renderStorage->isDofEnabled())
	{
		_dofBlurRenderer->bind();
		_renderStorage->setDofMap(_dofBlurRenderer->getBlurredTexture(_renderSurface, _renderStorage->getFinalSceneTextureBuffer(), 2, 1.0f, BlurDirectionType::BOTH));
		_dofBlurRenderer->unbind();

		_dofCaptureBuffer->bind();
		_dofRenderer->bind();
		_dofRenderer->render(_renderSurface);
		_dofRenderer->unbind();
		_dofCaptureBuffer->unbind();

		_renderStorage->setFinalSceneMap(_dofCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setDofMap(nullptr);
	}
}

void MasterRenderer::captureLensFlare()
{
	if(_renderStorage->isLensFlareEnabled())
	{
		_lensFlareCaptureBuffer->bind();
		_lensFlareRenderer->bind();
		_lensFlareRenderer->render(_renderSurface);
		_lensFlareRenderer->unbind();
		_lensFlareCaptureBuffer->unbind();

		_renderStorage->setFinalSceneMap(_lensFlareCaptureBuffer->getTexture(0));
	}
}

void MasterRenderer::captureMotionBlur()
{
	if(_renderStorage->isMotionBlurEnabled())
	{
		const auto difference = (_renderStorage->getMotionBlurDifference() * _renderStorage->getMotionBlurIntensity());

		if(difference.x != 0.0f || difference.y != 0.0f)
		{
			BlurDirectionType direction;
			if(difference.x >= difference.y)
			{
				direction = BlurDirectionType::HORIZONTAL;
				_renderStorage->setMotionBlurMixValue(difference.x);
			}
			else
			{
				direction = BlurDirectionType::VERTICAL;
				_renderStorage->setMotionBlurMixValue(difference.y);
			}

			_motionBlurBlurRenderer->bind();
			_renderStorage->setMotionBlurMap(_motionBlurBlurRenderer->getBlurredTexture(_renderSurface, _renderStorage->getFinalSceneTextureBuffer(), 5, 1.0f, direction));
			_motionBlurBlurRenderer->unbind();
		}
		else
		{
			_renderStorage->setMotionBlurMixValue(0.0f);
			_renderStorage->setMotionBlurMap(nullptr);
		}

		_motionBlurCaptureBuffer->bind();
		_motionBlurRenderer->bind();
		_motionBlurRenderer->render(_renderSurface);
		_motionBlurRenderer->unbind();
		_motionBlurCaptureBuffer->unbind();

		_renderStorage->setFinalSceneMap(_motionBlurCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setMotionBlurMap(nullptr);
	}
}

void MasterRenderer::captureAntiAliasing()
{
	if(_renderStorage->isAntiAliasingEnabled())
	{
		_antiAliasingCaptureBuffer->bind();
		_antiAliasingRenderer->bind();
		_antiAliasingRenderer->render(_renderSurface);
		_antiAliasingRenderer->unbind();
		_antiAliasingCaptureBuffer->unbind();

		_renderStorage->setFinalSceneMap(_antiAliasingCaptureBuffer->getTexture(0));
	}
}

void MasterRenderer::captureBloom()
{
	if(_renderStorage->isBloomEnabled())
	{
		switch(_renderStorage->getBloomType())
		{
			case BloomType::EVERYTHING:
			{
				_renderStorage->setBloomMap(_renderStorage->getPrimarySceneTextureBuffer());

				break;
			}
			case BloomType::PARTS:
			{
				_renderStorage->setBloomMap(_renderStorage->getSecondarySceneTextureBuffer());

				break;
			}
		}

		_bloomBlurRendererHighQuality->bind();
		_renderStorage->setBloomMap(_bloomBlurRendererHighQuality->getBlurredTexture(_renderSurface, _renderStorage->getBloomTextureBuffer(), _renderStorage->getBloomBlurCount(), _renderStorage->getBloomIntensity(), BlurDirectionType::BOTH));
		_bloomBlurRendererHighQuality->unbind();

		_bloomBlurRendererLowQuality->bind();
		_renderStorage->setBloomMap(_bloomBlurRendererLowQuality->getBlurredTexture(_renderSurface, _renderStorage->getBloomTextureBuffer(), _renderStorage->getBloomBlurCount(), _renderStorage->getBloomIntensity(), BlurDirectionType::BOTH));
		_bloomBlurRendererLowQuality->unbind();

		_bloomCaptureBuffer->bind();
		_bloomRenderer->bind();
		_bloomRenderer->render(_renderSurface);
		_bloomRenderer->unbind();
		_bloomCaptureBuffer->unbind();

		_renderStorage->setFinalSceneMap(_bloomCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setBloomMap(nullptr);
	}
}

void MasterRenderer::captureShadows()
{
	if(_renderStorage->isShadowsEnabled())
	{
		_shadowCaptureBuffer->bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		if(_terrainManager->getSelectedTerrain() != nullptr)
		{
			_terrainShadowRenderer->bind();
			_terrainShadowRenderer->render(_terrainManager->getSelectedTerrain());
			_terrainShadowRenderer->unbind();
		}

		if(!_modelManager->getModels().empty())
		{
			_modelShadowRenderer->bind();

			for(const auto & [modelId, model] : _modelManager->getModels())
			{
				if(model->isLevelOfDetailed())
				{
					auto foundPair = _modelManager->getModels().find(model->getLevelOfDetailId());

					if(foundPair != _modelManager->getModels().end())
					{
						const auto levelOfDetailModel = _modelManager->getModels().find(model->getLevelOfDetailId())->second;
						const auto originalPosition = levelOfDetailModel->getBasePosition();
						const auto originalRotation = levelOfDetailModel->getBaseRotation();
						const auto originalSize = levelOfDetailModel->getBaseSize();
						const auto originalVisibility = levelOfDetailModel->isVisible();

						levelOfDetailModel->setBasePosition(model->getBasePosition());
						levelOfDetailModel->setBaseRotation(model->getBaseRotation());
						levelOfDetailModel->setBaseSize(model->getBaseSize());
						levelOfDetailModel->setVisible(model->isVisible());
						levelOfDetailModel->updateTransformation();

						_modelShadowRenderer->render(levelOfDetailModel);

						levelOfDetailModel->setBasePosition(originalPosition);
						levelOfDetailModel->setBaseRotation(originalRotation);
						levelOfDetailModel->setBaseSize(originalSize);
						levelOfDetailModel->setVisible(originalVisibility);
						levelOfDetailModel->updateTransformation();
					}
					else
					{
						abort();
					}
				}
				else
				{
					_modelShadowRenderer->render(model);
				}
			}

			_modelShadowRenderer->unbind();
		}

		if(!_quad3dManager->getQuad3ds().empty())
		{
			_quad3dShadowRenderer->bind();

			for(const auto & [quad3dId, quad3d] : _quad3dManager->getQuad3ds())
			{
				_quad3dShadowRenderer->render(quad3d);
			}

			_quad3dShadowRenderer->unbind();
		}

		if(!_text3dManager->getText3ds().empty())
		{
			_quad3dShadowRenderer->bind();

			for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
			{
				for(const auto & quad3d : text3d->getQuad3ds())
				{
					_quad3dShadowRenderer->render(quad3d);
				}
			}

			_quad3dShadowRenderer->unbind();
		}

		_shadowCaptureBuffer->unbind();

		_renderStorage->setShadowMap(_shadowCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setShadowMap(nullptr);
	}
}