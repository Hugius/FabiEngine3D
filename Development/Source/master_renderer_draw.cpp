#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::_renderSkyEntity()
{
	// Validate existence
	if (_entityBus->getMainSkyEntity() != nullptr)
	{
		// Bind
		_skyEntityColorRenderer.bind();

		// Render SKY entity
		_skyEntityColorRenderer.render(_entityBus->getMainSkyEntity(), _entityBus->getMixSkyEntity());

		// Unbind
		_skyEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	// Validate existence
	if (_entityBus->getTerrainEntity() != nullptr)
	{
		// Bind
		_terrainEntityColorRenderer.bind();

		// Render LIGHT entities
		_terrainEntityColorRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render TERRAIN entity
		_terrainEntityColorRenderer.render(_entityBus->getTerrainEntity());

		// Unbind
		_terrainEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	// Validate existence
	if (_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		_waterEntityColorRenderer.bind();

		// Render LIGHT entities
		_waterEntityColorRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render WATER entity
		_waterEntityColorRenderer.render(_entityBus->getWaterEntity());

		// Unbind
		_waterEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderModelEntities()
{
	// Temporary values
	auto modelEntities = _entityBus->getModelEntities();

	// Validate existence
	if (!modelEntities.empty())
	{
		// Bind
		_modelEntityColorRenderer.bind();

		// Render lights
		_modelEntityColorRenderer.renderLightEntities(_entityBus->getLightEntities());

		// Render MODEL entities
		for (const auto& [keyID, modelEntity] : modelEntities)
		{
			// Check if LOD entity needs to be rendered
			if (modelEntity->isLevelOfDetailed())
			{
				// Try to find LOD entity
				auto foundPair = modelEntities.find(modelEntity->getLodEntityID());
				if (foundPair != modelEntities.end())
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
					_modelEntityColorRenderer.render(lodEntity);

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
				_modelEntityColorRenderer.render(modelEntity);
			}
		}

		// Unbind
		_modelEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderBillboardEntities()
{
	// Temporary values
	auto billboardEntities = _entityBus->getBillboardEntities();

	// Validate existence
	if (!billboardEntities.empty())
	{
		// Bind
		_billboardEntityColorRenderer.bind();

		// Render BILLBOARD entities
		for (const auto& [keyID, entity] : billboardEntities)
		{
			_billboardEntityColorRenderer.render(entity);
		}

		// Unbind
		_billboardEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if (_renderBus.isAabbFrameRenderingEnabled())
	{
		// Temporary values
		auto aabbEntities = _entityBus->getAabbEntities();

		// Validate existence
		if (!aabbEntities.empty())
		{
			// Bind
			_aabbEntityColorRenderer.bind();

			// Render AABB entities
			for (const auto& [keyID, entity] : aabbEntities)
			{
				_aabbEntityColorRenderer.render(entity);
			}

			// Unbind
			_aabbEntityColorRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalSceneImage()
{
	// Mirror
	_renderSurface->setMirroredVertically(true);

	// Update diffuse map
	_renderSurface->setDiffuseMap(_renderBus.getFinalSceneMap());

	// Render
	_imageEntityColorRenderer.bind();
	_imageEntityColorRenderer.render(_renderSurface);
	_imageEntityColorRenderer.unbind();

	// Mirror
	_renderSurface->setMirroredVertically(true);
}

void MasterRenderer::_renderGUI()
{
	if (!_entityBus->getImageEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		// Bind
		_imageEntityColorRenderer.bind();

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
				_imageEntityColorRenderer.render(entity);
			}
			else // TEXT entity
			{
				if (castedTextEntity->isDynamic()) // Dynamic text rendering
				{
					// Render every character individually
					for (const auto& characterEntity : castedTextEntity->getCharacterEntities())
					{
						_imageEntityColorRenderer.render(characterEntity);
					}
				}
				else // Static text rendering
				{
					_imageEntityColorRenderer.render(castedTextEntity);
				}
			}
		}

		// Unbind
		_imageEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderCustomCursor()
{
	for (const auto& [keyID, entity] : _entityBus->getImageEntities())
	{
		if (entity->getID() == _renderBus.getCursorEntityID())
		{
			_imageEntityColorRenderer.bind();
			_imageEntityColorRenderer.render(entity);
			_imageEntityColorRenderer.unbind();
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
	function<float(string)> calcTextWidth = [&](string text) { return (static_cast<float>(text.size()) * charWidth); };

	// Scene - surface
	shared_ptr<ImageEntity> sceneSurface = make_shared<ImageEntity>("sceneSurface");
	sceneSurface->setDiffuseMap(_renderBus.getPrimarySceneMap());
	sceneSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.666f, 0.666f, 0.666f, true));
	sceneSurface->setMirroredVertically(true);

	// Shadow - surface
	shared_ptr<ImageEntity> shadowSurface = make_shared<ImageEntity>("shadowSurface");
	shadowSurface->setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface->setColor(Vec3(static_cast<float>(_renderBus.getShadowMap() != 0)));
	shadowSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true));
	shadowSurface->setMirroredVertically(true);

	// Bloom - surface
	shared_ptr<ImageEntity> bloomSurface = make_shared<ImageEntity>("bloomSurface");
	bloomSurface->setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface->setColor(Vec3(static_cast<float>(_renderBus.getBloomMap() != 0)));
	bloomSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true));
	bloomSurface->setMirroredVertically(true);

	// Scene reflection - surface
	shared_ptr<ImageEntity> sceneReflectionSurface = make_shared<ImageEntity>("sceneReflectionSurface");
	sceneReflectionSurface->setDiffuseMap(_renderBus.getSceneReflectionMap());
	sceneReflectionSurface->setColor(Vec3(static_cast<float>(_renderBus.getSceneReflectionMap() != 0)));
	sceneReflectionSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true));
	sceneReflectionSurface->setMirroredVertically(true);

	// Water reflection - surface
	shared_ptr<ImageEntity> waterReflectionSurface = make_shared<ImageEntity>("waterReflectionSurface");
	waterReflectionSurface->setDiffuseMap(_renderBus.getWaterReflectionMap());
	waterReflectionSurface->setColor(Vec3(static_cast<float>(_renderBus.getWaterReflectionMap() != 0)));
	waterReflectionSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true));
	waterReflectionSurface->setMirroredVertically(true);

	// Water refraction - surface
	shared_ptr<ImageEntity> waterRefractionSurface = make_shared<ImageEntity>("waterRefractionSurface");
	waterRefractionSurface->setDiffuseMap(_renderBus.getWaterRefractionMap());
	waterRefractionSurface->setColor(Vec3(static_cast<float>(_renderBus.getWaterRefractionMap() != 0)));
	waterRefractionSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true));
	waterRefractionSurface->setMirroredVertically(true);

	// Depth - surface
	shared_ptr<ImageEntity> depthSurface = make_shared<ImageEntity>("depthSurface");
	depthSurface->setDiffuseMap(_renderBus.getDepthMap());
	depthSurface->setColor(Vec3(static_cast<float>(_renderBus.getDepthMap() != 0)));
	depthSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true));
	depthSurface->setMirroredVertically(true);
	depthSurface->setPerspectiveDepthEntity(true);

	// DOF - surface
	shared_ptr<ImageEntity> dofSurface = make_shared<ImageEntity>("dofSurface");
	dofSurface->setDiffuseMap(_renderBus.getDofMap());
	dofSurface->setColor(Vec3(static_cast<float>(_renderBus.getDofMap() != 0)));
	dofSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true));
	dofSurface->setMirroredVertically(true);

	// Motion blur - surface
	shared_ptr<ImageEntity> motionBlurSurface = make_shared<ImageEntity>("motionBlurSurface");
	motionBlurSurface->setDiffuseMap(_renderBus.getMotionBlurMap());
	motionBlurSurface->setColor(Vec3(static_cast<float>(_renderBus.getMotionBlurMap() != 0)));
	motionBlurSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true));
	motionBlurSurface->setMirroredVertically(true);

	// Scene - text
	shared_ptr<TextEntity> sceneText = make_shared<TextEntity>("sceneText");
	sceneText->setDiffuseMap(_textureLoader.getText("Scene Render", fontPath));
	sceneText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.4f, calcTextWidth("Scene Render"), charHeight, true));
	sceneText->setColor(textColor);

	// Shadow - text
	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setDiffuseMap(_textureLoader.getText("Shadow Render", fontPath));
	shadowText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true));
	shadowText->setColor(textColor);

	// Bloom - text
	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setDiffuseMap(_textureLoader.getText("Bloom Render", fontPath));
	bloomText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true));
	bloomText->setColor(textColor);
	
	// Scene reflection - text
	shared_ptr<TextEntity> sceneReflectionText = make_shared<TextEntity>("sceneReflectionText");
	sceneReflectionText->setDiffuseMap(_textureLoader.getText("Scene Reflection Render", fontPath));
	sceneReflectionText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.26f, calcTextWidth("Scene Reflection Render"), charHeight, true));
	sceneReflectionText->setColor(textColor);

	// Water reflection - text
	shared_ptr<TextEntity> waterReflectionText = make_shared<TextEntity>("waterReflectionText");
	waterReflectionText->setDiffuseMap(_textureLoader.getText("Water Reflection Render", fontPath));
	waterReflectionText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true));
	waterReflectionText->setColor(textColor);

	// Water refraction - text
	shared_ptr<TextEntity> waterRefractionText = make_shared<TextEntity>("waterRefractionText");
	waterRefractionText->setDiffuseMap(_textureLoader.getText("Water Refraction Render", fontPath));
	waterRefractionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true));
	waterRefractionText->setColor(textColor);

	// Depth - text
	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setDiffuseMap(_textureLoader.getText("Depth Render", fontPath));
	depthText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true));
	depthText->setColor(textColor);

	// DOF - text
	shared_ptr<TextEntity> dofText = make_shared<TextEntity>("dofText");
	dofText->setDiffuseMap(_textureLoader.getText("DOF Render", fontPath));
	dofText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true));
	dofText->setColor(textColor);

	// Motion blur - text
	shared_ptr<TextEntity> motionText = make_shared<TextEntity>("motionBlurText");
	motionText->setDiffuseMap(_textureLoader.getText("Motion Blur Render", fontPath));
	motionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true));
	motionText->setColor(textColor);
	
	// Bind
	_imageEntityColorRenderer.bind();

	// Render debug surfaces
	_imageEntityColorRenderer.render(sceneSurface);
	_imageEntityColorRenderer.render(shadowSurface);
	_imageEntityColorRenderer.render(bloomSurface);
	_imageEntityColorRenderer.render(sceneReflectionSurface);
	_imageEntityColorRenderer.render(waterReflectionSurface);
	_imageEntityColorRenderer.render(waterRefractionSurface);
	_imageEntityColorRenderer.render(depthSurface);
	_imageEntityColorRenderer.render(dofSurface);
	_imageEntityColorRenderer.render(motionBlurSurface);

	// Render debug text
	_imageEntityColorRenderer.render(sceneText);
	_imageEntityColorRenderer.render(shadowText);
	_imageEntityColorRenderer.render(bloomText);
	_imageEntityColorRenderer.render(sceneReflectionText);
	_imageEntityColorRenderer.render(waterReflectionText);
	_imageEntityColorRenderer.render(waterRefractionText);
	_imageEntityColorRenderer.render(depthText);
	_imageEntityColorRenderer.render(dofText);
	_imageEntityColorRenderer.render(motionText);

	// Unbind
	_imageEntityColorRenderer.unbind();
}