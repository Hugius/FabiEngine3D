#include "render_engine.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

#include <chrono>
#include <algorithm>

// Capturing reflection texture
void RenderEngine::_captureSceneReflections(CameraManager& camera)
{
	bool waterReflectionEnabled = (_renderBus.isWaterEffectsEnabled() && _entityBus->getWaterEntity() != nullptr) &&
		_entityBus->getWaterEntity()->isReflective();
	bool sceneReflectionEnabled = _renderBus.isSceneReflectionsEnabled();
	
	// Check if needed to capture scene
	if (waterReflectionEnabled || sceneReflectionEnabled)
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance;
		if (camera.isLookatEnabled())
		{
			cameraDistance = (camera.getPosition().y - camera.getLookat().y);
		}
		else
		{
			cameraDistance = (camera.getPosition().y - _renderBus.getSceneReflectionHeight());
		}

		// Start capturing reflection
		glEnable(GL_CLIP_DISTANCE0);
		_sceneReflectionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Save and disable reflective entity
		string reflectiveEntityID;
		if (!waterReflectionEnabled)
		{
			for (auto& gameEntity : _entityBus->getGameEntities())
			{
				if (gameEntity->isSceneReflective() && gameEntity->isVisible())
				{
					gameEntity->setVisible(false);
					reflectiveEntityID = gameEntity->getID();
				}
			}
		}

		// Change camera angle
		vec3 cameraPos = camera.getPosition();
		vec3 newCameraPos = vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Save reflection exceptions
		bool shadowsEnabled = _renderBus.isShadowsEnabled(); // Shadows are performance-heavy with little visual impact on a reflection
		float oldLightness = _entityBus->getSkyEntity()->getLightness(); // SkyHDR must not be in reflections
		_renderBus.setShadowsEnabled(false);

		// I know this is considered bad practice, but this is the only exception in the entire code-base
		const_cast<SkyEntity*>(_entityBus->getSkyEntity())->setLightness(_entityBus->getSkyEntity()->getOriginalLightness());

		// Render scene
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderGameEntities();

		// Revert reflection exceptions
		_renderBus.setShadowsEnabled(shadowsEnabled);
		const_cast<SkyEntity*>(_entityBus->getSkyEntity())->setLightness(oldLightness);

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Restore reflective entity
		if (!waterReflectionEnabled)
		{
			for (auto& gameEntity : _entityBus->getGameEntities())
			{
				if (gameEntity->getID() == reflectiveEntityID)
				{
					gameEntity->setVisible(true);
				}
			}
		}

		// Stop capturing reflection
		_sceneReflectionFramebuffer.unbind();
		glDisable(GL_CLIP_DISTANCE0);

		// Assign texture
		_renderBus.setSceneReflectionMap(_sceneReflectionFramebuffer.getTexture(0));
	}
}

// Capturing water refraction texture
void RenderEngine::_captureSceneRefractions()
{
	bool waterRefractionEnabled = (_renderBus.isWaterEffectsEnabled() &&_entityBus->getWaterEntity() != nullptr) && 
		_entityBus->getWaterEntity()->isRefractive();

	if (waterRefractionEnabled)
	{
		// Bind
		_sceneRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render scene
		_renderTerrainEntity();
		_renderGameEntities();

		// Unbind
		_sceneRefractionFramebuffer.unbind();

		// Assign texture
		_renderBus.setSceneRefractionMap(_sceneRefractionFramebuffer.getTexture(0));
	}
}

// Capturing shadows
void RenderEngine::_captureShadows()
{
	if (_renderBus.isShadowsEnabled())
	{
		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_shadowRenderer.bind();

		// Render game entities
		for (auto& entity : _entityBus->getGameEntities()) 
		{ 
			_shadowRenderer.renderGameEntity(entity); 
		}

		// Unbind
		_shadowRenderer.unbind();
		_shadowFramebuffer.unbind();
		_renderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
}

// Capturing bloom parts
void RenderEngine::_captureBloom()
{
	if (_renderBus.isBloomEnabled())
	{
		// Process scene texture
		_bloomHdrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		_bloomHdrRenderer.bind();
		_bloomHdrRenderer.render(_finalSurface, _renderBus.getSceneMap());
		_bloomHdrRenderer.unbind();
		_bloomHdrFramebuffer.unbind();

		// Blur scene texture
		_blurRenderer.bind();
		_renderBus.setBloomMap(_blurRenderer.blurTexture(_finalSurface, _bloomHdrFramebuffer.getTexture(0), 
			static_cast<int>(BlurType::BLOOM), _renderBus.getBloomBlurSize(), _renderBus.getBloomIntensity(), BlurDirection::BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_captureSceneDepth()
{
	if (_renderBus.isDofEnabled() || _renderBus.isLensFlareEnabled())
	{
		// Bind
		_sceneDepthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_depthRenderer.bind();

		// Render terrain entity
		if (_entityBus->getTerrainEntity() != nullptr)
		{
			_depthRenderer.renderTerrainEntity(_entityBus->getTerrainEntity());
		}

		// Render water entity
		if (_entityBus->getWaterEntity() != nullptr)
		{
			_depthRenderer.renderWaterEntity(_entityBus->getWaterEntity());
		}

		// Render game entities
		for (auto& entity : _entityBus->getGameEntities())
		{
			if (entity->isDepthMapIncluded())
			{
				_depthRenderer.renderGameEntity(entity);
			}
		}

		// Render billboard entities
		for (auto& entity : _entityBus->getBillboardEntities())
		{
			_depthRenderer.renderBillboardEntity(entity);
		}

		// Unbind
		_depthRenderer.unbind();
		_sceneDepthFramebuffer.unbind();
		_renderBus.setSceneDepthMap(_sceneDepthFramebuffer.getTexture(0));
	}
}

void RenderEngine::_captureWaterDepth()
{
	// Depth is only needed for edge transparency
	bool waterDepthNeeded = (_renderBus.isWaterEffectsEnabled() && _entityBus->getWaterEntity() != nullptr) &&
		_entityBus->getWaterEntity()->getTransparency() > 0.0f;

	if (waterDepthNeeded)
	{
		// Bind
		_waterDepthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_depthRenderer.bind();

		// Render terrain entity
		if (_entityBus->getTerrainEntity() != nullptr)
		{
			_depthRenderer.renderTerrainEntity(_entityBus->getTerrainEntity());
		}

		// Unbind
		_depthRenderer.unbind();
		_waterDepthFramebuffer.unbind();
		_renderBus.setWaterDepthMap(_waterDepthFramebuffer.getTexture(0));
	}
}

void RenderEngine::_captureDofBlur()
{
	if (_renderBus.isDofEnabled())
	{
		_blurRenderer.bind();
		_renderBus.setBlurMap(_blurRenderer.blurTexture(_finalSurface, _renderBus.getSceneMap(), 
			static_cast<int>(BlurType::DOF), 6, 1.0f, BlurDirection::BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_capturePostProcessing()
{
	// Apply bloom, DOF & lens-flare on scene texture
	_postProcessingFramebuffer.bind();
	_postRenderer.bind();
	_postRenderer.render(_finalSurface);
	_postRenderer.unbind();
	_postProcessingFramebuffer.unbind();
	_renderBus.setPostProcessedSceneMap(_postProcessingFramebuffer.getTexture(0));
}

void RenderEngine::_captureMotionBlur(CameraManager& camera)
{
	static float lastYaw;
	static float lastPitch;

	// Timing variables
	static std::chrono::high_resolution_clock::time_point previous = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> timeDifference = std::chrono::duration_cast<std::chrono::duration<double>>(current - previous);
	float elapsedMS = static_cast<float>(timeDifference.count()) * 1000.0f;

	// Blur variables
	static int blurStrength;
	static bool firstTime = true;

	// If 1 frame passed
	if (elapsedMS >= Config::getInst().getUpdateMsPerFrame() || firstTime)
	{
		if (_renderBus.isMotionBlurEnabled())
		{
			// Set for next frame
			previous = current;
			
			// Camera speed and blur direction variables
			int xDifference = static_cast<int>(fabsf(camera.getYaw() - lastYaw) * _renderBus.getMotionBlurStrength());
			int yDifference = static_cast<int>(fabsf(camera.getPitch() - lastPitch) * _renderBus.getMotionBlurStrength());
			if (fabsf(camera.getYaw() - lastYaw) < 0.5f)
			{
				xDifference = 0;
			}
			static BlurDirection lastDirection = BlurDirection::NONE;
			BlurDirection direction = BlurDirection::NONE;
			firstTime = false;

			// Determine blur type & strength
			if (xDifference != 0 && yDifference != 0)
			{
				if (xDifference >= yDifference)
				{
					blurStrength = xDifference;
					direction = BlurDirection::HORIZONTAL;
				}
				else
				{
					blurStrength = yDifference;
					direction = BlurDirection::VERTICAL;
				}
			}
			else // No FPS camera movement
			{
				// Slowly fade out
				if (blurStrength > 0)
				{
					direction = lastDirection;
					blurStrength--;
				}
			}
			
			// Blur strength must be between 0 and 10
			blurStrength = std::clamp(blurStrength, 0, 10);

			// Set for next iteration
			lastYaw = camera.getYaw();
			lastPitch = camera.getPitch();

			// Apply motion blur
			_blurRenderer.bind();
			_renderBus.setMotionBlurMap(_blurRenderer.blurTexture(_finalSurface, _renderBus.getPostProcessedSceneMap(), 
				static_cast<int>(BlurType::MOTION), blurStrength, 1.0f, direction));
			_blurRenderer.unbind();

			// Set last direction
			lastDirection = direction;
		}
		else // No motion blur
		{
			_renderBus.setMotionBlurMap(_renderBus.getPostProcessedSceneMap());
		}
	}
}

void RenderEngine::_captureLensFlare()
{
	if (_renderBus.isLensFlareEnabled())
	{
		// Calculate screen position
		vec3 lightingPosition = _renderBus.getDirectionalLightingPosition();
		mat4 viewMatrix = _renderBus.getViewMatrix();
		mat4 projectionMatrix = _renderBus.getProjectionMatrix();
		vec4 clipSpacePosition = projectionMatrix * viewMatrix * vec4(lightingPosition, 1.0f);
		float alpha = 0.0f;

		// Calculate transparency value
		if (clipSpacePosition.w <= 0.0f)
		{
			alpha = 0.0f;
		}
		else
		{
			float x = clipSpacePosition.x / clipSpacePosition.w;
			float y = clipSpacePosition.y / clipSpacePosition.w;
			alpha = 1.0f - (max(fabsf(x), fabsf(y)) * _renderBus.getLensFlareMultiplier());
			alpha = std::clamp(alpha, 0.0f, 1.0f);
		}

		// Update post-processing shader values
		_renderBus.setLensFlareAlpha(alpha);
		_renderBus.setFlareSourcePositionClipspace(clipSpacePosition);
		_renderBus.setFlareSourcePosition(lightingPosition);
	}
}