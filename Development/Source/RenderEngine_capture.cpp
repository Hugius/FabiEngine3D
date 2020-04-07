#include <WE3D/RenderEngine.hpp>
#include <WE3D/ShaderBus.hpp>

// Capturing reflection texture
void RenderEngine::p_captureSSR(CameraManager & camera)
{
	if ((p_entityBus->getWaterEntity() != nullptr && p_shaderBus.isWaterEffectsEnabled()) || p_shaderBus.isSSREnabled())
	{
		// Calculate distance between camera and reflection surface
		float cameraDistance = (camera.getPosition().y - p_shaderBus.getSSRHeight());

		// Start capturing reflection
		glEnable(GL_CLIP_DISTANCE0);
		p_ssrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Change camera angle
		vec3 cameraPos = camera.getPosition();
		vec3 newCameraPos = vec3(cameraPos.x, cameraPos.y - (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Render scene
		bool shadows = p_shaderBus.isShadowsEnabled();
		p_shaderBus.setShadowsEnabled(false);
		p_renderSkyEntity();
		p_renderTerrainEntity();
		p_renderGameEntities();
		p_shaderBus.setShadowsEnabled(shadows);

		// Revert camera angle
		cameraPos = camera.getPosition();
		newCameraPos = vec3(cameraPos.x, cameraPos.y + (cameraDistance * 2.0f), cameraPos.z);
		camera.setPosition(newCameraPos);
		camera.invertPitch();
		camera.updateMatrices();

		// Stop capturing reflection
		p_ssrFramebuffer.unbind();
		glDisable(GL_CLIP_DISTANCE0);

		// Assign texture
		p_shaderBus.setSSRMap(p_ssrFramebuffer.getTexture(0));
	}
}

// Capturing water refraction texture
void RenderEngine::p_captureWaterRefractions()
{
	if ((p_entityBus->getWaterEntity() != nullptr && p_shaderBus.isWaterEffectsEnabled()))
	{
		// Bind
		p_waterRefractionFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render scene
		p_renderTerrainEntity();

		// Unbind
		p_waterRefractionFramebuffer.unbind();

		// Assign texture
		p_shaderBus.setWaterRefractionMap(p_waterRefractionFramebuffer.getTexture(0));
	}
}

// Capturing shadows
void RenderEngine::p_captureShadows()
{
	if (p_shaderBus.isShadowsEnabled())
	{
		// Bind
		p_shadowFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		p_shadowRenderer.bind();

		// Render game entities
		for (auto & entity : p_entityBus->getGameEntities()) { p_shadowRenderer.renderGameEntity(entity); }

		// Unbind
		p_shadowRenderer.unbind();
		p_shadowFramebuffer.unbind();
		p_shaderBus.setShadowMap(p_shadowFramebuffer.getTexture(0));
	}
}

// Capturing bloom parts
void RenderEngine::p_captureBloom()
{
	if (p_shaderBus.isBloomEnabled())
	{
		// Process scene texture
		p_bloomHdrFramebuffer.bind();
		glClear(GL_COLOR_BUFFER_BIT);
		p_bloomHdrRenderer.bind();
		p_bloomHdrRenderer.render(&p_finalSurface, p_shaderBus.getSceneMap());
		p_bloomHdrRenderer.unbind();
		p_bloomHdrFramebuffer.unbind();
	
		// Blur scene texture
		p_blurRenderer.bind();
		p_shaderBus.setBloomMap(p_blurRenderer.blurTexture(&p_finalSurface, p_bloomHdrFramebuffer.getTexture(0), BLUR_BLOOM, p_shaderBus.getBloomBlurSize(), p_shaderBus.getBloomIntensity(), BLUR_DIR_BOTH));
		p_blurRenderer.unbind();
	}
}

void RenderEngine::p_captureDepth()
{
	if (p_shaderBus.isDofEnabled() || p_shaderBus.isWaterEffectsEnabled())
	{
		// Bind
		p_depthFramebuffer.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		p_depthRenderer.bind();

		// Render terrain entity
		p_depthRenderer.renderTerrainEntity(p_entityBus->getTerrainEntity());

		// Render game entities
		for (auto & entity : p_entityBus->getGameEntities())
		{
			p_depthRenderer.renderGameEntity(entity);
		}

		// Render billboard entities
		for (auto & entity : p_entityBus->getBillboardEntities())
		{
			p_depthRenderer.renderBillboardEntity(entity);
		}

		// Unbind
		p_depthRenderer.unbind();
		p_depthFramebuffer.unbind();
		p_shaderBus.setDepthMap(p_depthFramebuffer.getTexture(0));
	}
}

void RenderEngine::p_captureDofBlur()
{
	if (p_shaderBus.isDofEnabled())
	{
		p_blurRenderer.bind();
		p_shaderBus.setBlurMap(p_blurRenderer.blurTexture(&p_finalSurface, p_shaderBus.getSceneMap(), BLUR_DOF, 4, 1.0f, BLUR_DIR_BOTH));
		p_blurRenderer.unbind();
	}
}

void RenderEngine::p_capturePostProcessing()
{	
	// Apply bloom and DOF on scene texture
	p_bloomDofAdditionFramebuffer.bind();
	p_postRenderer.bind();
	p_postRenderer.render(&p_finalSurface, p_shaderBus.getSceneMap(), p_shaderBus.getBloomMap(), p_shaderBus.getDepthMap(), p_shaderBus.getBlurMap());
	p_postRenderer.unbind();
	p_bloomDofAdditionFramebuffer.unbind();
	p_shaderBus.setBloomedDofSceneMap(p_bloomDofAdditionFramebuffer.getTexture(0));
}

void RenderEngine::p_captureMotionBlur(CameraManager & camera, ivec2 mousePos)
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

	strength *= p_shaderBus.isMotionBlurEnabled();

	// Blur the scene
	p_blurRenderer.bind();
	p_shaderBus.setMotionBlurMap(p_blurRenderer.blurTexture(&p_finalSurface, p_shaderBus.getBloomedDofSceneMap(), BLUR_MOTION, strength, 1.0f, type));
	p_blurRenderer.unbind();

	// Set for next iteration
	oldYaw = camera.getYaw();
	oldPitch = camera.getPitch();
}