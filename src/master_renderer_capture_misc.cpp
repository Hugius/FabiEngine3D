#include "master_renderer.hpp"
#include "render_bus.hpp"

void MasterRenderer::_captureWorldDepth(EntityBus& entityBus)
{
	auto modelEntities = entityBus.getModelEntities();
	auto billboardEntities = entityBus.getBillboardEntities();
	float clippingY = numeric_limits<float>::lowest();
	const bool waterDepthNeeded = (entityBus.getWaterEntity() != nullptr) && (entityBus.getWaterEntity()->getTransparency() > 0.0f);
	bool isUnderWater = false;

	if(waterDepthNeeded)
	{
		auto waterEntity = entityBus.getWaterEntity();
		float waveHeight = (waterEntity->hasDisplacementMap() ? waterEntity->getWaveHeight() : 0.0f);
		isUnderWater = (_renderBus.getCameraPosition().y < (waterEntity->getHeight() + waveHeight));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().x < (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z > (waterEntity->getSize() / 2.0f)));
		isUnderWater = (isUnderWater && (_renderBus.getCameraPosition().z < (waterEntity->getSize() / 2.0f)));

		if(isUnderWater)
		{
			clippingY = waterEntity->getHeight();
		}
		else
		{
			clippingY = (waterEntity->getHeight() + waveHeight);
		}
	}

	if(_renderBus.isDofEnabled() || _renderBus.isLensFlareEnabled() || waterDepthNeeded)
	{
		_worldDepthCaptor->bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		if(entityBus.getTerrainEntity() != nullptr)
		{
			_terrainEntityDepthRenderer.bind();

			_terrainEntityDepthRenderer.render(entityBus.getTerrainEntity());

			_terrainEntityDepthRenderer.unbind();
		}

		if(!modelEntities.empty())
		{
			_modelEntityDepthRenderer.bind();

			for(const auto& [key, modelEntity] : modelEntities)
			{
				if(modelEntity->isDepthMapIncluded())
				{
					if(modelEntity->isLevelOfDetailed())
					{
						auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
						if(foundPair != modelEntities.end())
						{
							auto levelOfDetailEntity = foundPair->second;

							fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
							fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
							fvec3 initialSize = levelOfDetailEntity->getBaseSize();
							bool initialVisibility = levelOfDetailEntity->isVisible();

							levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
							levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
							levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
							levelOfDetailEntity->setVisible(modelEntity->isVisible());
							levelOfDetailEntity->updateTransformationMatrix();

							_modelEntityDepthRenderer.render(levelOfDetailEntity, clippingY, isUnderWater);

							levelOfDetailEntity->setBasePosition(initialPosition);
							levelOfDetailEntity->setBaseRotation(initialRotation);
							levelOfDetailEntity->setBaseSize(initialSize);
							levelOfDetailEntity->setVisible(initialVisibility);
							levelOfDetailEntity->updateTransformationMatrix();
						}
						else
						{
							Logger::throwError("MasterRenderer::_captureWorldDepth");
						}
					}
					else
					{
						_modelEntityDepthRenderer.render(modelEntity, clippingY, isUnderWater);
					}
				}
			}

			_modelEntityDepthRenderer.unbind();
		}

		if(!billboardEntities.empty())
		{
			_billboardEntityDepthRenderer.bind();

			for(const auto& [key, entity] : billboardEntities)
			{
				if(entity->isDepthMapIncluded())
				{
					_billboardEntityDepthRenderer.render(entity, clippingY, isUnderWater);
				}
			}

			_billboardEntityDepthRenderer.unbind();
		}

		_worldDepthCaptor->unbind();

		_renderBus.setDepthMap(_worldDepthCaptor->getTexture(0));
	}
	else
	{
		_renderBus.setDepthMap(0);
	}
}

void MasterRenderer::_captureDOF()
{
	if(_renderBus.isDofEnabled())
	{
		_dofBlurRenderer.bind();
		_renderBus.setDofMap(_dofBlurRenderer.blurTexture(_renderQuad, _renderBus.getFinalSceneMap(), 2, 1.0f, BlurDirection::BOTH));
		_dofBlurRenderer.unbind();

		_dofCaptor->bind();
		_dofRenderer.bind();
		_dofRenderer.render(_renderQuad);
		_dofRenderer.unbind();
		_dofCaptor->unbind();
		_renderBus.setFinalSceneMap(_dofCaptor->getTexture(0));
	}
	else
	{
		_renderBus.setDofMap(0);
	}
}

void MasterRenderer::_captureLensFlare()
{
	if(_renderBus.isLensFlareEnabled())
	{
		_lensFlareCaptor->bind();
		_lensFlareRenderer.bind();
		_lensFlareRenderer.render(_renderQuad);
		_lensFlareRenderer.unbind();
		_lensFlareCaptor->unbind();
		_renderBus.setFinalSceneMap(_lensFlareCaptor->getTexture(0));
	}
}

void MasterRenderer::_captureMotionBlur()
{
	if(_renderBus.isMotionBlurEnabled())
	{
		float xDifference = (_cameraYawDifference * _renderBus.getMotionBlurStrength());
		float yDifference = (_cameraPitchDifference * _renderBus.getMotionBlurStrength());

		bool hasMoved = false;
		BlurDirection direction;

		if(xDifference != 0.0f || yDifference != 0.0f)
		{
			if(xDifference >= yDifference)
			{
				hasMoved = true;
				direction = BlurDirection::HORIZONTAL;
				_renderBus.setMotionBlurMixValue(xDifference);
			}
			else
			{
				hasMoved = true;
				direction = BlurDirection::VERTICAL;
				_renderBus.setMotionBlurMixValue(yDifference);
			}
		}

		if(hasMoved)
		{
			_motionBlurBlurRenderer.bind();
			_renderBus.setMotionBlurMap(_motionBlurBlurRenderer.blurTexture(_renderQuad, _renderBus.getFinalSceneMap(), 5, 1.0f, direction));
			_motionBlurBlurRenderer.unbind();
		}
		else
		{
			_renderBus.setMotionBlurMixValue(0.0f);
			_renderBus.setMotionBlurMap(0);
		}

		_motionBlurCaptor->bind();
		_motionBlurRenderer.bind();
		_motionBlurRenderer.render(_renderQuad);
		_motionBlurRenderer.unbind();
		_motionBlurCaptor->unbind();
		_renderBus.setFinalSceneMap(_motionBlurCaptor->getTexture(0));
	}
	else
	{
		_renderBus.setMotionBlurMap(0);
	}
}

void MasterRenderer::_captureAntiAliasing()
{
	if(_renderBus.isAntiAliasingEnabled())
	{
		_antiAliasingCaptor->bind();
		_antiAliasingRenderer.bind();
		_antiAliasingRenderer.render(_renderQuad);
		_antiAliasingRenderer.unbind();
		_antiAliasingCaptor->unbind();
		_renderBus.setFinalSceneMap(_antiAliasingCaptor->getTexture(0));
	}
}

void MasterRenderer::_captureBloom()
{
	if(_renderBus.isBloomEnabled() && _renderBus.getBloomBlurCount() > 0 && _renderBus.getBloomIntensity() > 0.0f)
	{
		shared_ptr<TextureBuffer> textureToBlur = nullptr;
		if(_renderBus.getBloomType() == BloomType::EVERYTHING)
		{
			textureToBlur = _renderBus.getPrimarySceneMap();
		}
		else
		{
			textureToBlur = _renderBus.getSecondarySceneMap();
		}

		_bloomBlurRendererHighQuality.bind();
		_renderBus.setBloomMap(_bloomBlurRendererHighQuality.blurTexture(_renderQuad, textureToBlur,
							   _renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererHighQuality.unbind();

		_bloomBlurRendererLowQuality.bind();
		_renderBus.setBloomMap(_bloomBlurRendererLowQuality.blurTexture(_renderQuad, _renderBus.getBloomMap(),
							   _renderBus.getBloomBlurCount(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_bloomBlurRendererLowQuality.unbind();

		_bloomCaptor->bind();
		_bloomRenderer.bind();
		_bloomRenderer.render(_renderQuad);
		_bloomRenderer.unbind();
		_bloomCaptor->unbind();
		_renderBus.setFinalSceneMap(_bloomCaptor->getTexture(0));
	}
	else
	{
		_renderBus.setBloomMap(0);
	}
}

void MasterRenderer::_captureShadows(EntityBus& entityBus)
{
	if(_renderBus.isShadowsEnabled())
	{
		auto modelEntities = entityBus.getModelEntities();
		auto billboardEntities = entityBus.getBillboardEntities();

		_shadowCaptor->bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		if(!modelEntities.empty())
		{
			_modelEntityShadowRenderer.bind();

			for(const auto& [key, modelEntity] : modelEntities)
			{
				if(modelEntity->isLevelOfDetailed())
				{
					auto foundPair = modelEntities.find(modelEntity->getLevelOfDetailEntityID());
					if(foundPair != modelEntities.end())
					{
						auto levelOfDetailEntity = foundPair->second;

						fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
						fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
						fvec3 initialSize = levelOfDetailEntity->getBaseSize();
						bool initialVisibility = levelOfDetailEntity->isVisible();

						levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
						levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
						levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
						levelOfDetailEntity->setVisible(modelEntity->isVisible());
						levelOfDetailEntity->updateTransformationMatrix();

						_modelEntityShadowRenderer.render(levelOfDetailEntity);

						levelOfDetailEntity->setBasePosition(initialPosition);
						levelOfDetailEntity->setBaseRotation(initialRotation);
						levelOfDetailEntity->setBaseSize(initialSize);
						levelOfDetailEntity->setVisible(initialVisibility);
						levelOfDetailEntity->updateTransformationMatrix();
					}
					else
					{
						Logger::throwError("MasterRenderer::_captureShadows");
					}
				}
				else
				{
					_modelEntityShadowRenderer.render(modelEntity);
				}
			}

			_modelEntityShadowRenderer.unbind();
		}

		if(!billboardEntities.empty())
		{
			_billboardEntityShadowRenderer.bind();

			for(const auto& [key, entity] : entityBus.getBillboardEntities())
			{
				_billboardEntityShadowRenderer.render(entity);
			}

			_billboardEntityShadowRenderer.unbind();
		}

		_shadowCaptor->unbind();
		_renderBus.setShadowMap(_shadowCaptor->getTexture(0));
	}
	else
	{
		_renderBus.setShadowMap(0);
	}
}