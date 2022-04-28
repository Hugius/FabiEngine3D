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

	if(_terrainEntityManager->getSelectedEntity() != nullptr)
	{
		_terrainEntityDepthRenderer->bind();

		_terrainEntityDepthRenderer->render(_terrainEntityManager->getSelectedEntity());

		_terrainEntityDepthRenderer->unbind();
	}

	if(_waterEntityManager->getSelectedEntity() != nullptr)
	{
		_waterEntityDepthRenderer->bind();

		_waterEntityDepthRenderer->render(_waterEntityManager->getSelectedEntity());

		_waterEntityDepthRenderer->unbind();
	}

	if(!_modelEntityManager->getEntities().empty())
	{
		_modelEntityDepthRenderer->bind();

		for(const auto & [modelId, model] : _modelEntityManager->getEntities())
		{
			if(model->isLevelOfDetailed())
			{
				auto foundPair = _modelEntityManager->getEntities().find(model->getLevelOfDetailId());

				if(foundPair != _modelEntityManager->getEntities().end())
				{
					const auto levelOfDetailModel = _modelEntityManager->getEntities().find(model->getLevelOfDetailId())->second;
					const auto originalPosition = levelOfDetailModel->getBasePosition();
					const auto originalRotation = levelOfDetailModel->getBaseRotation();
					const auto originalSize = levelOfDetailModel->getBaseSize();
					const auto originalVisibility = levelOfDetailModel->isVisible();

					levelOfDetailModel->setBasePosition(model->getBasePosition());
					levelOfDetailModel->setBaseRotation(model->getBaseRotation());
					levelOfDetailModel->setBaseSize(model->getBaseSize());
					levelOfDetailModel->setVisible(model->isVisible());
					levelOfDetailModel->updateTransformation();

					_modelEntityDepthRenderer->render(levelOfDetailModel);

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
				_modelEntityDepthRenderer->render(model);
			}
		}

		_modelEntityDepthRenderer->unbind();
	}

	if(!_quad3dEntityManager->getEntities().empty())
	{
		_quad3dEntityDepthRenderer->bind();

		for(const auto & [quad3dId, quad3d] : _quad3dEntityManager->getEntities())
		{
			_quad3dEntityDepthRenderer->render(quad3d);
		}

		_quad3dEntityDepthRenderer->unbind();
	}

	if(!_text3dEntityManager->getEntities().empty())
	{
		_quad3dEntityDepthRenderer->bind();

		for(const auto & [text3dId, text3d] : _text3dEntityManager->getEntities())
		{
			for(const auto & characterEntity : text3d->getCharacterEntities())
			{
				_quad3dEntityDepthRenderer->render(characterEntity);
			}
		}

		_quad3dEntityDepthRenderer->unbind();
	}

	if(!_aabbEntityManager->getEntities().empty())
	{
		_aabbEntityDepthRenderer->bind();

		for(const auto & [aabbId, aabb] : _aabbEntityManager->getEntities())
		{
			_aabbEntityDepthRenderer->render(aabb);
		}

		_aabbEntityDepthRenderer->unbind();
	}

	_worldDepthCaptureBuffer->unbind();

	_renderStorage->setDepthMap(_worldDepthCaptureBuffer->getTexture(0));
}

void MasterRenderer::captureDof()
{
	if(_renderStorage->isDofEnabled())
	{
		_dofBlurRenderer->bind();
		_renderStorage->setDofMap(_dofBlurRenderer->blurTexture(_renderSurface, _renderStorage->getFinalSceneTextureBuffer(), 2, 1.0f, BlurDirectionType::BOTH));
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

		bool hasMoved = false;
		BlurDirectionType direction;

		if(difference.x != 0.0f || difference.y != 0.0f)
		{
			if(difference.x >= difference.y)
			{
				hasMoved = true;
				direction = BlurDirectionType::HORIZONTAL;
				_renderStorage->setMotionBlurMixValue(difference.x);
			}
			else
			{
				hasMoved = true;
				direction = BlurDirectionType::VERTICAL;
				_renderStorage->setMotionBlurMixValue(difference.y);
			}
		}

		if(hasMoved)
		{
			_motionBlurBlurRenderer->bind();
			_renderStorage->setMotionBlurMap(_motionBlurBlurRenderer->blurTexture(_renderSurface, _renderStorage->getFinalSceneTextureBuffer(), 5, 1.0f, direction));
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
		if(_renderStorage->getBloomType() == BloomType::EVERYTHING)
		{
			_renderStorage->setBloomMap(_renderStorage->getPrimarySceneTextureBuffer());
		}
		else
		{
			_renderStorage->setBloomMap(_renderStorage->getSecondarySceneTextureBuffer());
		}

		_bloomBlurRendererHighQuality->bind();
		_renderStorage->setBloomMap(_bloomBlurRendererHighQuality->blurTexture(_renderSurface, _renderStorage->getBloomTextureBuffer(), _renderStorage->getBloomBlurCount(), _renderStorage->getBloomIntensity(), BlurDirectionType::BOTH));
		_bloomBlurRendererHighQuality->unbind();

		_bloomBlurRendererLowQuality->bind();
		_renderStorage->setBloomMap(_bloomBlurRendererLowQuality->blurTexture(_renderSurface, _renderStorage->getBloomTextureBuffer(), _renderStorage->getBloomBlurCount(), _renderStorage->getBloomIntensity(), BlurDirectionType::BOTH));
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

		if(!_modelEntityManager->getEntities().empty())
		{
			_modelEntityShadowRenderer->bind();

			for(const auto & [modelId, model] : _modelEntityManager->getEntities())
			{
				if(model->isLevelOfDetailed())
				{
					auto foundPair = _modelEntityManager->getEntities().find(model->getLevelOfDetailId());

					if(foundPair != _modelEntityManager->getEntities().end())
					{
						const auto levelOfDetailModel = _modelEntityManager->getEntities().find(model->getLevelOfDetailId())->second;
						const auto originalPosition = levelOfDetailModel->getBasePosition();
						const auto originalRotation = levelOfDetailModel->getBaseRotation();
						const auto originalSize = levelOfDetailModel->getBaseSize();
						const auto originalVisibility = levelOfDetailModel->isVisible();

						levelOfDetailModel->setBasePosition(model->getBasePosition());
						levelOfDetailModel->setBaseRotation(model->getBaseRotation());
						levelOfDetailModel->setBaseSize(model->getBaseSize());
						levelOfDetailModel->setVisible(model->isVisible());
						levelOfDetailModel->updateTransformation();

						_modelEntityShadowRenderer->render(levelOfDetailModel);

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
					_modelEntityShadowRenderer->render(model);
				}
			}

			_modelEntityShadowRenderer->unbind();
		}

		if(!_quad3dEntityManager->getEntities().empty())
		{
			_quad3dEntityShadowRenderer->bind();

			for(const auto & [quad3dId, quad3d] : _quad3dEntityManager->getEntities())
			{
				_quad3dEntityShadowRenderer->render(quad3d);
			}

			_quad3dEntityShadowRenderer->unbind();
		}

		if(!_text3dEntityManager->getEntities().empty())
		{
			_quad3dEntityShadowRenderer->bind();

			for(const auto & [text3dId, text3d] : _text3dEntityManager->getEntities())
			{
				for(const auto & characterEntity : text3d->getCharacterEntities())
				{
					_quad3dEntityShadowRenderer->render(characterEntity);
				}
			}

			_quad3dEntityShadowRenderer->unbind();
		}

		_shadowCaptureBuffer->unbind();

		_renderStorage->setShadowMap(_shadowCaptureBuffer->getTexture(0));
	}
	else
	{
		_renderStorage->setShadowMap(nullptr);
	}
}