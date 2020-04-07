#include "RenderEngine.hpp"
#include "ShaderBus.hpp"

// Capturing reflection texture
void RenderEngine::_captureSSR(CameraManager & camera)
{
	if ((_entityBus->getWaterEntity() != nullptr && _shaderBus.isWaterEffectsEnabled()) || _shaderBus.isSSREnabled())
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (camera.getPosition().y - _shaderBus.getSSRHeight());

		// Start capturing reflection
		glEnable(GL_CLIP_DISTANCE0);
		_ssrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Change camera angle
		vec3 cameraPos = camera.getPosition();
		vec3 newCameraPos = vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Render scene
		bool shadows = _shaderBus.isShadowsEnabled();
		_shaderBus.setShadowsEnabled(false);
		_renderSkyEntity();
		_renderTerrainEntity();
		_renderGameEntities();
		_shaderBus.setShadowsEnabled(shadows);

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Stop capturing reflection
		_ssrFramebuffer.unbind();
		glDisable(GL_CLIP_DISTANCE0);

		// Assign texture
		_shaderBus.setSSRMap(_ssrFramebuffer.getTexture(0));
	}
}

// Capturing water refraction texture
void RenderEngine::_captureWaterRefractions()
{
	if ((_entityBus->getWaterEntity() != nullptr && _shaderBus.isWaterEffectsEnabled()))
	{
		// Bind
		_waterRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render scene
		_renderTerrainEntity();

		// Unbind
		_waterRefractionFramebuffer.unbind();

		// Assign texture
		_shaderBus.setWaterRefractionMap(_waterRefractionFramebuffer.getTexture(0));
	}
}

// Capturing shadows
void RenderEngine::_captureShadows()
{
	if (_shaderBus.isShadowsEnabled())
	{
		// Bind
		_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_shadowRenderer.bind();

		// Render game entities
		for (auto & entity : _entityBus->getGameEntities()) { _shadowRenderer.renderGameEntity(entity); }

		// Unbind
		_shadowRenderer.unbind();
		_shadowFramebuffer.unbind();
		_shaderBus.setShadowMap(_shadowFramebuffer.getTexture(0));
	}
}

// Capturing bloom parts
void RenderEngine::_captureBloom()
{
	if (_shaderBus.isBloomEnabled())
	{
		// Process scene texture
		_bloomHdrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		_bloomHdrRenderer.bind();
		_bloomHdrRenderer.render(&_finalSurface, _shaderBus.getSceneMap());
		_bloomHdrRenderer.unbind();
		_bloomHdrFramebuffer.unbind();
	
		// Blur scene texture
		_blurRenderer.bind();
		_shaderBus.setBloomMap(_blurRenderer.blurTexture(&_finalSurface, _bloomHdrFramebuffer.getTexture(0), BLUR_BLOOM, _shaderBus.getBloomBlurSize(), _shaderBus.getBloomIntensity(), BLUR_DIR_BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_captureDepth()
{
	if (_shaderBus.isDofEnabled() || _shaderBus.isWaterEffectsEnabled())
	{
		// Bind
		_depthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		_depthRenderer.bind();

		// Render terrain entity
		_depthRenderer.renderTerrainEntity(_entityBus->getTerrainEntity());

		// Render game entities
		for (auto & entity : _entityBus->getGameEntities())
		{
			_depthRenderer.renderGameEntity(entity);
		}

		// Render billboard entities
		for (auto & entity : _entityBus->getBillboardEntities())
		{
			_depthRenderer.renderBillboardEntity(entity);
		}

		// Unbind
		_depthRenderer.unbind();
		_depthFramebuffer.unbind();
		_shaderBus.setDepthMap(_depthFramebuffer.getTexture(0));
	}
}

void RenderEngine::_captureDofBlur()
{
	if (_shaderBus.isDofEnabled())
	{
		_blurRenderer.bind();
		_shaderBus.setBlurMap(_blurRenderer.blurTexture(&_finalSurface, _shaderBus.getSceneMap(), BLUR_DOF, 4, 1.0f, BLUR_DIR_BOTH));
		_blurRenderer.unbind();
	}
}

void RenderEngine::_capturePostProcessing()
{	
	// Apply bloom and DOF on scene texture
	_bloomDofAdditionFramebuffer.bind();
	_postRenderer.bind();
	_postRenderer.render(&_finalSurface, _shaderBus.getSceneMap(), _shaderBus.getBloomMap(), _shaderBus.getDepthMap(), _shaderBus.getBlurMap());
	_postRenderer.unbind();
	_bloomDofAdditionFramebuffer.unbind();
	_shaderBus.setBloomedDofSceneMap(_bloomDofAdditionFramebuffer.getTexture(0));
}

void RenderEngine::_captureMotionBlur(CameraManager & camera, ivec2 mousePos)
{
	// Declare variables
	static float oldYaw;
	static float oldPitch;
	int xDifference = int((camera.getYaw() - oldYaw));
	int yDifference = int((camera.getPitch() - oldPitch));
	int type;
	int strength;

	// No negative differences
	xDifference = abs(xDifference) * 2;
	yDifference = abs(yDifference) * 2;
	
	// Horizontal blur
	if (xDifference > yDifference)
	{
		type = BLUR_DIR_HORIZONTAL;
		strength = xDifference > 8 ? 8 : xDifference;
	}
	else // Vertical blur
	{
		type = BLUR_DIR_VERTICAL;
		strength = yDifference > 8 ? 8 : yDifference;
	}

	strength *= _shaderBus.isMotionBlurEnabled();

	// Blur the scene
	_blurRenderer.bind();
	_shaderBus.setMotionBlurMap(_blurRenderer.blurTexture(&_finalSurface, _shaderBus.getBloomedDofSceneMap(), BLUR_MOTION, strength, 1.0f, type));
	_blurRenderer.unbind();

	// Set for next iteration
	oldYaw = camera.getYaw();
	oldPitch = camera.getPitch();
}