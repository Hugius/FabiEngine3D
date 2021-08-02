#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;

void MasterRenderer::_renderSkyEntity()
{
	if (_entityBus->getMainSkyEntity() != nullptr)
	{
		// Bind
		_skyEntityRenderer.bind();

		// Render SKY entity
		_skyEntityRenderer.render(_entityBus->getMainSkyEntity(), _entityBus->getMixSkyEntity());

		// Unbind
		_skyEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if (_entityBus->getTerrainEntity() != nullptr)
	{
		// Bind
		_terrainEntityRenderer.bind();

		// Render LIGHT entities
		_terrainEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render TERRAIN entity
		_terrainEntityRenderer.render(_entityBus->getTerrainEntity());

		// Unbind
		_terrainEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if (_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		_waterEntityRenderer.bind();

		// Render LIGHT entities
		_waterEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render WATER entity
		_waterEntityRenderer.render(_entityBus->getWaterEntity());

		// Unbind
		_waterEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderModelEntities()
{
	if (!_entityBus->getModelEntities().empty())
	{
		// Bind
		_modelEntityRenderer.bind();

		// Render lights
		_modelEntityRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render MODEL entities
		auto allModelEntities = _entityBus->getModelEntities();
		for (const auto& [keyID, modelEntity] : allModelEntities)
		{
			// Check if LOD entity needs to be rendered
			if (modelEntity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				auto foundPair = allModelEntities.find(modelEntity->getLodEntityID());
				if (foundPair != allModelEntities.end())
				{
					auto lodEntity = foundPair->second;

					// Save original transformation
					Vec3 originalPosition = lodEntity->getPosition();
					Vec3 originalRotation = lodEntity->getRotation();
					Vec3 originalSize = lodEntity->getSize();
					bool originalVisibility = lodEntity->isVisible();

					// Change transformation
					lodEntity->setPosition(modelEntity->getPosition());
					lodEntity->setRotation(modelEntity->getRotation());
					lodEntity->setSize((modelEntity->getSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
					lodEntity->setVisible(modelEntity->isVisible());
					lodEntity->updateModelMatrix();

					// Render LOD entity
					_modelEntityRenderer.render(lodEntity);

					// Revert to original transformation
					lodEntity->setPosition(originalPosition);
					lodEntity->setRotation(originalRotation);
					lodEntity->setSize(originalSize);
					lodEntity->setVisible(originalVisibility);
					lodEntity->updateModelMatrix();
				}
				else
				{
					Logger::throwError("Model entity with ID \"" + modelEntity->getID() + "\" has a non-existing LOD entity with ID \"" + modelEntity->getLodEntityID() + "\"");
				}
			}
			else // Render high-quality entity
			{
				_modelEntityRenderer.render(modelEntity);
			}
		}

		// Unbind
		_modelEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderBillboardEntities()
{
	if (!_entityBus->getBillboardEntities().empty())
	{
		// Bind
		_billboardEntityRenderer.bind();

		// Render BILLBOARD entities
		for (const auto& [keyID, entity] : _entityBus->getBillboardEntities())
		{
			_billboardEntityRenderer.render(entity);
		}

		// Unbind
		_billboardEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if (_renderBus.isAabbFrameRenderingEnabled())
	{
		if (!_entityBus->getAabbEntities().empty())
		{
			// Bind
			_aabbEntityRenderer.bind();

			// Render AABB entities
			for (const auto& [keyID, entity] : _entityBus->getAabbEntities())
			{
				_aabbEntityRenderer.render(entity);
			}

			// Unbind
			_aabbEntityRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalSceneTexture()
{
	_finalRenderer.bind();
	_finalRenderer.render(_finalSurface, _renderBus.getFinalSceneMap(), _renderBus.getMotionBlurMap());
	_finalRenderer.unbind();
}

void MasterRenderer::_renderGUI()
{
	if (!_entityBus->getImageEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		// Bind
		_imageEntityRenderer.bind();

		// Sort rendering order
		map<unsigned int, shared_ptr<ImageEntity>> orderedEntityMap;
		for (const auto& [keyID, entity] : _entityBus->getImageEntities())
		{
			// Custom cursor entity must be rendered last
			if (entity->getID() != _renderBus.getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
			}
		}
		for (const auto& [keyID, entity] : _entityBus->getTextEntities())
		{
			orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
		}

		// Render entities
		for (const auto& [keyID, entity] : orderedEntityMap)
		{
			// Check if entity is a TEXT entity
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if (castedTextEntity == nullptr) // IMAGE entity
			{
				_imageEntityRenderer.render(entity);
			}
			else // TEXT entity
			{
				if (castedTextEntity->isDynamic()) // Dynamic text rendering
				{
					// Render every character individually
					for (const auto& characterEntity : castedTextEntity->getCharacterEntities())
					{
						_imageEntityRenderer.render(characterEntity);
					}
				}
				else // Static text rendering
				{
					_imageEntityRenderer.render(castedTextEntity);
				}
			}
		}

		// Unbind
		_imageEntityRenderer.unbind();
	}
}

void MasterRenderer::_renderCustomCursor()
{
	for (const auto& [keyID, entity] : _entityBus->getImageEntities())
	{
		if (entity->getID() == _renderBus.getCursorEntityID())
		{
			_imageEntityRenderer.bind();
			_imageEntityRenderer.render(entity);
			_imageEntityRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderDebugScreens()
{
	// Temporary values
	const string fontPath = "engine_assets\\fonts\\font.ttf";
	const Vec3 textColor = Vec3(0.75f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	std::function<float(string)> calcTextWidth = [&](string text) { return static_cast<float>(text.size()) * charWidth; };

	// Scene - surface
	shared_ptr<ImageEntity> sceneSurface = make_shared<ImageEntity>("sceneSurface");
	sceneSurface->setDiffuseMap(_renderBus.getPrimarySceneMap());
	sceneSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.666f, 0.666f, 0.666f, true, false));
	sceneSurface->setMirroredVertically(true);

	// Shadow - surface
	shared_ptr<ImageEntity> shadowSurface = make_shared<ImageEntity>("shadowSurface");
	shadowSurface->setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface->setColor(Vec3(static_cast<float>(_renderBus.getShadowMap() != 0)));
	shadowSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true, false));
	shadowSurface->setMirroredVertically(true);

	// Bloom - surface
	shared_ptr<ImageEntity> bloomSurface = make_shared<ImageEntity>("bloomSurface");
	bloomSurface->setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface->setColor(Vec3(static_cast<float>(_renderBus.getBloomMap() != 0)));
	bloomSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true, false));
	bloomSurface->setMirroredVertically(true);

	// Scene reflection - surface
	shared_ptr<ImageEntity> sceneReflectionSurface = make_shared<ImageEntity>("sceneReflectionSurface");
	sceneReflectionSurface->setDiffuseMap(_renderBus.getSceneReflectionMap());
	sceneReflectionSurface->setColor(Vec3(static_cast<float>(_renderBus.getSceneReflectionMap() != 0)));
	sceneReflectionSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true, false));
	sceneReflectionSurface->setMirroredVertically(true);

	// Water reflection - surface
	shared_ptr<ImageEntity> waterReflectionSurface = make_shared<ImageEntity>("waterReflectionSurface");
	waterReflectionSurface->setDiffuseMap(_renderBus.getWaterReflectionMap());
	waterReflectionSurface->setColor(Vec3(static_cast<float>(_renderBus.getWaterReflectionMap() != 0)));
	waterReflectionSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true, false));
	waterReflectionSurface->setMirroredVertically(true);

	// Water refraction - surface
	shared_ptr<ImageEntity> waterRefractionSurface = make_shared<ImageEntity>("waterRefractionSurface");
	waterRefractionSurface->setDiffuseMap(_renderBus.getWaterRefractionMap());
	waterRefractionSurface->setColor(Vec3(static_cast<float>(_renderBus.getWaterRefractionMap() != 0)));
	waterRefractionSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true, false));
	waterRefractionSurface->setMirroredVertically(true);

	// Depth - surface
	shared_ptr<ImageEntity> depthSurface = make_shared<ImageEntity>("depthSurface");
	depthSurface->setDiffuseMap(_renderBus.getSceneDepthMap());
	depthSurface->setColor(Vec3(static_cast<float>(_renderBus.getSceneDepthMap() != 0)));
	depthSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true, false));
	depthSurface->setMirroredVertically(true);
	depthSurface->setPerspectiveDepthEntity(true);

	// DOF - surface
	shared_ptr<ImageEntity> dofSurface = make_shared<ImageEntity>("dofSurface");
	dofSurface->setDiffuseMap(_renderBus.getDofMap());
	dofSurface->setColor(Vec3(static_cast<float>(_renderBus.getDofMap() != 0)));
	dofSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true, false));
	dofSurface->setMirroredVertically(true);

	// Motion blur - surface
	shared_ptr<ImageEntity> motionBlurSurface = make_shared<ImageEntity>("motionBlurSurface");
	motionBlurSurface->setDiffuseMap(_renderBus.getMotionBlurMap());
	motionBlurSurface->setColor(Vec3(static_cast<float>(_renderBus.getMotionBlurMap() != 0)));
	motionBlurSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true, false));
	motionBlurSurface->setMirroredVertically(true);

	// Scene - text
	shared_ptr<TextEntity> sceneText = make_shared<TextEntity>("sceneText");
	sceneText->setDiffuseMap(_textureLoader.getText("Scene Render", fontPath));
	sceneText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.4f, calcTextWidth("Scene Render"), charHeight, true, false));
	sceneText->setColor(textColor);

	// Shadow - text
	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setDiffuseMap(_textureLoader.getText("Shadow Render", fontPath));
	shadowText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true, false));
	shadowText->setColor(textColor);

	// Bloom - text
	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setDiffuseMap(_textureLoader.getText("Bloom Render", fontPath));
	bloomText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true, false));
	bloomText->setColor(textColor);
	
	// Scene reflection - text
	shared_ptr<TextEntity> sceneReflectionText = make_shared<TextEntity>("sceneReflectionText");
	sceneReflectionText->setDiffuseMap(_textureLoader.getText("Scene Reflection Render", fontPath));
	sceneReflectionText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.26f, calcTextWidth("Scene Reflection Render"), charHeight, true, false));
	sceneReflectionText->setColor(textColor);

	// Water reflection - text
	shared_ptr<TextEntity> waterReflectionText = make_shared<TextEntity>("waterReflectionText");
	waterReflectionText->setDiffuseMap(_textureLoader.getText("Water Reflection Render", fontPath));
	waterReflectionText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true, false));
	waterReflectionText->setColor(textColor);

	// Water refraction - text
	shared_ptr<TextEntity> waterRefractionText = make_shared<TextEntity>("waterRefractionText");
	waterRefractionText->setDiffuseMap(_textureLoader.getText("Water Refraction Render", fontPath));
	waterRefractionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true, false));
	waterRefractionText->setColor(textColor);

	// Depth - text
	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setDiffuseMap(_textureLoader.getText("Depth Render", fontPath));
	depthText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true, false));
	depthText->setColor(textColor);

	// DOF - text
	shared_ptr<TextEntity> dofText = make_shared<TextEntity>("dofText");
	dofText->setDiffuseMap(_textureLoader.getText("DOF Render", fontPath));
	dofText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true, false));
	dofText->setColor(textColor);

	// Motion blur - text
	shared_ptr<TextEntity> motionText = make_shared<TextEntity>("motionBlurText");
	motionText->setDiffuseMap(_textureLoader.getText("Motion Blur Render", fontPath));
	motionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true, false));
	motionText->setColor(textColor);
	
	// Bind
	_imageEntityRenderer.bind();

	// Render debug surfaces
	_imageEntityRenderer.render(sceneSurface);
	_imageEntityRenderer.render(shadowSurface);
	_imageEntityRenderer.render(bloomSurface);
	_imageEntityRenderer.render(sceneReflectionSurface);
	_imageEntityRenderer.render(waterReflectionSurface);
	_imageEntityRenderer.render(waterRefractionSurface);
	_imageEntityRenderer.render(depthSurface);
	_imageEntityRenderer.render(dofSurface);
	_imageEntityRenderer.render(motionBlurSurface);

	// Render debug text
	_imageEntityRenderer.render(sceneText);
	_imageEntityRenderer.render(shadowText);
	_imageEntityRenderer.render(bloomText);
	_imageEntityRenderer.render(sceneReflectionText);
	_imageEntityRenderer.render(waterReflectionText);
	_imageEntityRenderer.render(waterRefractionText);
	_imageEntityRenderer.render(depthText);
	_imageEntityRenderer.render(dofText);
	_imageEntityRenderer.render(motionText);

	// Unbind
	_imageEntityRenderer.unbind();
}