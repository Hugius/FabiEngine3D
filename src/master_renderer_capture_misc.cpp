#include "master_renderer.hpp"
#include "render_storage.hpp"

void MasterRenderer::_captureWorldDepth()
{
	if(!_renderStorage->isDofEnabled() && !_renderStorage->isLensFlareEnabled())
	{
		_renderStorage->setDepthMap(nullptr);
		return;
	}

	_worldDepthCaptor->bind();

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

		for(const auto& [key, modelEntity] : _modelEntityManager->getEntities())
		{
			if(modelEntity->isDepthMapIncluded())
			{
				if(modelEntity->isLevelOfDetailed())
				{
					auto foundPair = _modelEntityManager->getEntities().find(modelEntity->getLevelOfDetailEntityId());

					if(foundPair != _modelEntityManager->getEntities().end())
					{
						const auto levelOfDetailEntity = _modelEntityManager->getEntities().find(modelEntity->getLevelOfDetailEntityId())->second;
						const auto originalPosition = levelOfDetailEntity->getBasePosition();
						const auto originalRotation = levelOfDetailEntity->getBaseRotation();
						const auto originalSize = levelOfDetailEntity->getBaseSize();
						const auto originalVisibility = levelOfDetailEntity->isVisible();

						levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
						levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
						levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
						levelOfDetailEntity->setVisible(modelEntity->isVisible());
						levelOfDetailEntity->updateTransformation();

						_modelEntityDepthRenderer->render(levelOfDetailEntity);

						levelOfDetailEntity->setBasePosition(originalPosition);
						levelOfDetailEntity->setBaseRotation(originalRotation);
						levelOfDetailEntity->setBaseSize(originalSize);
						levelOfDetailEntity->setVisible(originalVisibility);
						levelOfDetailEntity->updateTransformation();
					}
					else
					{
						abort();
					}
				}
				else
				{
					_modelEntityDepthRenderer->render(modelEntity);
				}
			}
		}

		_modelEntityDepthRenderer->unbind();
	}

	if(!_quad3dEntityManager->getEntities().empty())
	{
		_quad3dEntityDepthRenderer->bind();

		for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->isDepthMapIncluded())
			{
				_quad3dEntityDepthRenderer->render(entity);
			}
		}

		_quad3dEntityDepthRenderer->unbind();
	}

	if(!_text3dEntityManager->getEntities().empty())
	{
		_quad3dEntityDepthRenderer->bind();

		for(const auto& [key, textEntity] : _text3dEntityManager->getEntities())
		{
			for(const auto& characterEntity : textEntity->getCharacterEntities())
			{
				_quad3dEntityDepthRenderer->render(characterEntity);
			}
		}

		_quad3dEntityDepthRenderer->unbind();
	}

	if(!_aabbEntityManager->getEntities().empty())
	{
		_aabbEntityDepthRenderer->bind();

		for(const auto& [key, entity] : _aabbEntityManager->getEntities())
		{
			_aabbEntityDepthRenderer->render(entity);
		}

		_aabbEntityDepthRenderer->unbind();
	}

	_worldDepthCaptor->unbind();

	_renderStorage->setDepthMap(_worldDepthCaptor->getTexture(0));
}

void MasterRenderer::_captureDof()
{
	if(_renderStorage->isDofEnabled())
	{
		_dofBlurRenderer->bind();
		_renderStorage->setDofMap(_dofBlurRenderer->blurTexture(_renderSurface, _renderStorage->getFinalSceneMap(), 2, 1.0f, BlurDirection::BOTH));
		_dofBlurRenderer->unbind();

		_dofCaptor->bind();
		_dofRenderer->bind();
		_dofRenderer->render(_renderSurface);
		_dofRenderer->unbind();
		_dofCaptor->unbind();

		_renderStorage->setFinalSceneMap(_dofCaptor->getTexture(0));
	}
	else
	{
		_renderStorage->setDofMap(nullptr);
	}
}

void MasterRenderer::_captureLensFlare()
{
	if(_renderStorage->isLensFlareEnabled())
	{
		_lensFlareCaptor->bind();
		_lensFlareRenderer->bind();
		_lensFlareRenderer->render(_renderSurface);
		_lensFlareRenderer->unbind();
		_lensFlareCaptor->unbind();

		_renderStorage->setFinalSceneMap(_lensFlareCaptor->getTexture(0));
	}
}

void MasterRenderer::_captureMotionBlur()
{
	if(_renderStorage->isMotionBlurEnabled())
	{
		const auto difference = (_renderStorage->getMotionBlurDifference() * _renderStorage->getMotionBlurIntensity());

		bool hasMoved = false;
		BlurDirection direction;

		if(difference.x != 0.0f || difference.y != 0.0f)
		{
			if(difference.x >= difference.y)
			{
				hasMoved = true;
				direction = BlurDirection::HORIZONTAL;
				_renderStorage->setMotionBlurMixValue(difference.x);
			}
			else
			{
				hasMoved = true;
				direction = BlurDirection::VERTICAL;
				_renderStorage->setMotionBlurMixValue(difference.y);
			}
		}

		if(hasMoved)
		{
			_motionBlurBlurRenderer->bind();
			_renderStorage->setMotionBlurMap(_motionBlurBlurRenderer->blurTexture(_renderSurface, _renderStorage->getFinalSceneMap(), 5, 1.0f, direction));
			_motionBlurBlurRenderer->unbind();
		}
		else
		{
			_renderStorage->setMotionBlurMixValue(0.0f);
			_renderStorage->setMotionBlurMap(nullptr);
		}

		_motionBlurCaptor->bind();
		_motionBlurRenderer->bind();
		_motionBlurRenderer->render(_renderSurface);
		_motionBlurRenderer->unbind();
		_motionBlurCaptor->unbind();

		_renderStorage->setFinalSceneMap(_motionBlurCaptor->getTexture(0));
	}
	else
	{
		_renderStorage->setMotionBlurMap(nullptr);
	}
}

void MasterRenderer::_captureAntiAliasing()
{
	if(_renderStorage->isAntiAliasingEnabled())
	{
		_antiAliasingCaptor->bind();
		_antiAliasingRenderer->bind();
		_antiAliasingRenderer->render(_renderSurface);
		_antiAliasingRenderer->unbind();
		_antiAliasingCaptor->unbind();

		_renderStorage->setFinalSceneMap(_antiAliasingCaptor->getTexture(0));
	}
}

void MasterRenderer::_captureBloom()
{
	if(_renderStorage->isBloomEnabled())
	{
		if(_renderStorage->getBloomType() == BloomType::EVERYTHING)
		{
			_renderStorage->setBloomMap(_renderStorage->getPrimarySceneMap());
		}
		else
		{
			_renderStorage->setBloomMap(_renderStorage->getSecondarySceneMap());
		}

		_bloomBlurRendererHighQuality->bind();
		_renderStorage->setBloomMap(_bloomBlurRendererHighQuality->blurTexture(_renderSurface, _renderStorage->getBloomMap(), _renderStorage->getBloomBlurCount(), _renderStorage->getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererHighQuality->unbind();

		_bloomBlurRendererLowQuality->bind();
		_renderStorage->setBloomMap(_bloomBlurRendererLowQuality->blurTexture(_renderSurface, _renderStorage->getBloomMap(), _renderStorage->getBloomBlurCount(), _renderStorage->getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererLowQuality->unbind();

		_bloomCaptor->bind();
		_bloomRenderer->bind();
		_bloomRenderer->render(_renderSurface);
		_bloomRenderer->unbind();
		_bloomCaptor->unbind();

		_renderStorage->setFinalSceneMap(_bloomCaptor->getTexture(0));
	}
	else
	{
		_renderStorage->setBloomMap(nullptr);
	}
}

void MasterRenderer::_captureShadows()
{
	if(_renderStorage->isShadowsEnabled())
	{
		_shadowCaptor->bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		if(!_modelEntityManager->getEntities().empty())
		{
			_modelEntityShadowRenderer->bind();

			for(const auto& [key, modelEntity] : _modelEntityManager->getEntities())
			{
				if(modelEntity->isLevelOfDetailed())
				{
					auto foundPair = _modelEntityManager->getEntities().find(modelEntity->getLevelOfDetailEntityId());

					if(foundPair != _modelEntityManager->getEntities().end())
					{
						const auto levelOfDetailEntity = _modelEntityManager->getEntities().find(modelEntity->getLevelOfDetailEntityId())->second;
						const auto originalPosition = levelOfDetailEntity->getBasePosition();
						const auto originalRotation = levelOfDetailEntity->getBaseRotation();
						const auto originalSize = levelOfDetailEntity->getBaseSize();
						const auto originalVisibility = levelOfDetailEntity->isVisible();

						levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
						levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
						levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
						levelOfDetailEntity->setVisible(modelEntity->isVisible());
						levelOfDetailEntity->updateTransformation();

						_modelEntityShadowRenderer->render(levelOfDetailEntity);

						levelOfDetailEntity->setBasePosition(originalPosition);
						levelOfDetailEntity->setBaseRotation(originalRotation);
						levelOfDetailEntity->setBaseSize(originalSize);
						levelOfDetailEntity->setVisible(originalVisibility);
						levelOfDetailEntity->updateTransformation();
					}
					else
					{
						abort();
					}
				}
				else
				{
					_modelEntityShadowRenderer->render(modelEntity);
				}
			}

			_modelEntityShadowRenderer->unbind();
		}

		if(!_quad3dEntityManager->getEntities().empty())
		{
			_quad3dEntityShadowRenderer->bind();

			for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
			{
				_quad3dEntityShadowRenderer->render(entity);
			}

			_quad3dEntityShadowRenderer->unbind();
		}

		if(!_text3dEntityManager->getEntities().empty())
		{
			_quad3dEntityShadowRenderer->bind();

			for(const auto& [key, textEntity] : _text3dEntityManager->getEntities())
			{
				for(const auto& characterEntity : textEntity->getCharacterEntities())
				{
					_quad3dEntityShadowRenderer->render(characterEntity);
				}
			}

			_quad3dEntityShadowRenderer->unbind();
		}

		_shadowCaptor->unbind();

		_renderStorage->setShadowMap(_shadowCaptor->getTexture(0));
	}
	else
	{
		_renderStorage->setShadowMap(nullptr);
	}
}