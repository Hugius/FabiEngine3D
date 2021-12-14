#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::_renderSkyEntity()
{
	// Validate existence
	if(_entityBus->getMainSkyEntity() != nullptr)
	{
		// Bind
		_skyEntityColorRenderer.bind();

		// Render sky entity
		_skyEntityColorRenderer.render(_entityBus->getMainSkyEntity(), _entityBus->getMixSkyEntity());

		// Unbind
		_skyEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	// Validate existence
	if(_entityBus->getTerrainEntity() != nullptr)
	{
		// Bind
		_terrainEntityColorRenderer.bind();

		// Process pointlight entities
		_terrainEntityColorRenderer.processPointlightEntities(_entityBus->getPointLightEntities());

		// Process spotlight entities
		_terrainEntityColorRenderer.processSpotlightEntities(_entityBus->getSpotlightEntities());

		// Render terrain entity
		_terrainEntityColorRenderer.render(_entityBus->getTerrainEntity());

		// Unbind
		_terrainEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	// Validate existence
	if(_entityBus->getWaterEntity() != nullptr)
	{
		// Bind
		_waterEntityColorRenderer.bind();

		// Process pointlight entities
		_waterEntityColorRenderer.processPointlightEntities(_entityBus->getPointLightEntities());

		// Process spotlight entities
		_waterEntityColorRenderer.processSpotlightEntities(_entityBus->getSpotlightEntities());

		// Render water entity
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
	if(!modelEntities.empty())
	{
		// Bind
		_modelEntityColorRenderer.bind();

		// Process pointlight entities
		_modelEntityColorRenderer.processPointlightEntities(_entityBus->getPointLightEntities());

		// Process spotlight entities
		_modelEntityColorRenderer.processSpotlightEntities(_entityBus->getSpotlightEntities());

		// Render model entities
		for(const auto& [keyID, modelEntity] : modelEntities)
		{
			// Check if level of detail entity needs to be rendered
			if(modelEntity->isLevelOfDetailed())
			{
				// Try to find level of detail entity
				auto levelOfDetailEntity = modelEntities.find(modelEntity->getLevelOfDetailEntityID())->second;

				// Save initial transformation
				fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
				fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
				fvec3 initialSize = levelOfDetailEntity->getBaseSize();
				bool initialVisibility = levelOfDetailEntity->isVisible();

				// Change transformation
				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformationMatrix();

				// Render level of detail entity
				_modelEntityColorRenderer.render(levelOfDetailEntity, _entityBus->getReflectionEntities());

				// Revert to initial transformation
				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else // Render high-quality entity
			{
				_modelEntityColorRenderer.render(modelEntity, _entityBus->getReflectionEntities());
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
	if(!billboardEntities.empty())
	{
		// Bind
		_billboardEntityColorRenderer.bind();

		// Render billboard entities
		for(const auto& [keyID, entity] : billboardEntities)
		{
			_billboardEntityColorRenderer.render(entity);
		}

		// Unbind
		_billboardEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(_renderBus.isAabbFrameRenderingEnabled())
	{
		// Temporary values
		auto aabbEntities = _entityBus->getAabbEntities();

		// Validate existence
		if(!aabbEntities.empty())
		{
			// Bind
			_aabbEntityColorRenderer.bind();

			// Render AABB entities
			for(const auto& [keyID, entity] : aabbEntities)
			{
				_aabbEntityColorRenderer.render(entity);
			}

			// Unbind
			_aabbEntityColorRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalWorldImage()
{
	// Mirror
	_renderSurface->setMirroredVertically(true);

	// Update diffuse map
	_renderSurface->setDiffuseMap(_renderBus.getFinalWorldMap());

	// Render
	_imageEntityColorRenderer.bind();
	_imageEntityColorRenderer.render(_renderSurface);
	_imageEntityColorRenderer.unbind();

	// Mirror
	_renderSurface->setMirroredVertically(true);
}

void MasterRenderer::_renderGUI()
{
	if(!_entityBus->getImageEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		// Bind
		_imageEntityColorRenderer.bind();

		// Sort rendering order
		map<unsigned int, shared_ptr<ImageEntity>> orderedEntityMap;
		for(const auto& [keyID, entity] : _entityBus->getImageEntities())
		{
			// Custom cursor entity must be rendered last
			if(entity->getID() != _renderBus.getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
			}
		}
		for(const auto& [keyID, entity] : _entityBus->getTextEntities())
		{
			orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
		}

		// Render entities
		for(const auto& [keyID, entity] : orderedEntityMap)
		{
			// Check if entity is a text entity
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if(castedTextEntity == nullptr) // Image entity
			{
				_imageEntityColorRenderer.render(entity);
			}
			else // Text entity
			{
				if(castedTextEntity->isDynamic()) // Dynamic text rendering
				{
					// Render every character individually
					for(const auto& characterEntity : castedTextEntity->getCharacterEntities())
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

void MasterRenderer::_renderCursor()
{
	for(const auto& [keyID, entity] : _entityBus->getImageEntities())
	{
		if(entity->getID() == _renderBus.getCursorEntityID())
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
	const string fontPath = "engine\\assets\\font\\font.ttf";
	const fvec3 textColor = fvec3(0.75f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	function<float(string)> calcTextWidth = [&](string text)
	{
		return (static_cast<float>(text.size()) * charWidth);
	};

	// World - surface
	shared_ptr<ImageEntity> worldSurface = make_shared<ImageEntity>("worldSurface");
	worldSurface->setDiffuseMap(_renderBus.getPrimaryWorldMap());
	worldSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.666f, 0.666f, 0.666f, true));
	worldSurface->setMirroredVertically(true);

	// Shadow - surface
	shared_ptr<ImageEntity> shadowSurface = make_shared<ImageEntity>("shadowSurface");
	shadowSurface->setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface->setColor(fvec3(static_cast<float>(_renderBus.getShadowMap() != 0)));
	shadowSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true));
	shadowSurface->setMirroredVertically(true);

	// Bloom - surface
	shared_ptr<ImageEntity> bloomSurface = make_shared<ImageEntity>("bloomSurface");
	bloomSurface->setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface->setColor(fvec3(static_cast<float>(_renderBus.getBloomMap() != 0)));
	bloomSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true));
	bloomSurface->setMirroredVertically(true);

	// Planar reflection - surface
	shared_ptr<ImageEntity> planarReflectionSurface = make_shared<ImageEntity>("planarReflectionSurface");
	planarReflectionSurface->setDiffuseMap(_renderBus.getPlanarReflectionMap());
	planarReflectionSurface->setColor(fvec3(static_cast<float>(_renderBus.getPlanarReflectionMap() != 0)));
	planarReflectionSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true));
	planarReflectionSurface->setMirroredVertically(true);

	// Water reflection - surface
	shared_ptr<ImageEntity> waterReflectionSurface = make_shared<ImageEntity>("waterReflectionSurface");
	waterReflectionSurface->setDiffuseMap(_renderBus.getWaterReflectionMap());
	waterReflectionSurface->setColor(fvec3(static_cast<float>(_renderBus.getWaterReflectionMap() != 0)));
	waterReflectionSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true));
	waterReflectionSurface->setMirroredVertically(true);

	// Water refraction - surface
	shared_ptr<ImageEntity> waterRefractionSurface = make_shared<ImageEntity>("waterRefractionSurface");
	waterRefractionSurface->setDiffuseMap(_renderBus.getWaterRefractionMap());
	waterRefractionSurface->setColor(fvec3(static_cast<float>(_renderBus.getWaterRefractionMap() != 0)));
	waterRefractionSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true));
	waterRefractionSurface->setMirroredVertically(true);

	// Depth - surface
	shared_ptr<ImageEntity> depthSurface = make_shared<ImageEntity>("depthSurface");
	depthSurface->setDiffuseMap(_renderBus.getDepthMap());
	depthSurface->setColor(fvec3(static_cast<float>(_renderBus.getDepthMap() != 0)));
	depthSurface->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true));
	depthSurface->setMirroredVertically(true);
	depthSurface->setPerspectiveDepthEntity(true);

	// DOF - surface
	shared_ptr<ImageEntity> dofSurface = make_shared<ImageEntity>("dofSurface");
	dofSurface->setDiffuseMap(_renderBus.getDofMap());
	dofSurface->setColor(fvec3(static_cast<float>(_renderBus.getDofMap() != 0)));
	dofSurface->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true));
	dofSurface->setMirroredVertically(true);

	// Motion blur - surface
	shared_ptr<ImageEntity> motionBlurSurface = make_shared<ImageEntity>("motionBlurSurface");
	motionBlurSurface->setDiffuseMap(_renderBus.getMotionBlurMap());
	motionBlurSurface->setColor(fvec3(static_cast<float>(_renderBus.getMotionBlurMap() != 0)));
	motionBlurSurface->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true));
	motionBlurSurface->setMirroredVertically(true);

	// World - text
	shared_ptr<TextEntity> worldText = make_shared<TextEntity>("worldText");
	worldText->setDiffuseMap(_textureLoader.load2dTexture("World Render", fontPath));
	worldText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.4f, calcTextWidth("World Render"), charHeight, true));
	worldText->setColor(textColor);

	// Shadow - text
	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setDiffuseMap(_textureLoader.load2dTexture("Shadow Render", fontPath));
	shadowText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true));
	shadowText->setColor(textColor);

	// Bloom - text
	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setDiffuseMap(_textureLoader.load2dTexture("Bloom Render", fontPath));
	bloomText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true));
	bloomText->setColor(textColor);

	// Planar reflection - text
	shared_ptr<TextEntity> planarReflectionText = make_shared<TextEntity>("planarReflectionText");
	planarReflectionText->setDiffuseMap(_textureLoader.load2dTexture("Planar Reflection Render", fontPath));
	planarReflectionText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.26f, calcTextWidth("Planar Reflection Render"), charHeight, true));
	planarReflectionText->setColor(textColor);

	// Water reflection - text
	shared_ptr<TextEntity> waterReflectionText = make_shared<TextEntity>("waterReflectionText");
	waterReflectionText->setDiffuseMap(_textureLoader.load2dTexture("Water Reflection Render", fontPath));
	waterReflectionText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true));
	waterReflectionText->setColor(textColor);

	// Water refraction - text
	shared_ptr<TextEntity> waterRefractionText = make_shared<TextEntity>("waterRefractionText");
	waterRefractionText->setDiffuseMap(_textureLoader.load2dTexture("Water Refraction Render", fontPath));
	waterRefractionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true));
	waterRefractionText->setColor(textColor);

	// Depth - text
	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setDiffuseMap(_textureLoader.load2dTexture("Depth Render", fontPath));
	depthText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true));
	depthText->setColor(textColor);

	// DOF - text
	shared_ptr<TextEntity> dofText = make_shared<TextEntity>("dofText");
	dofText->setDiffuseMap(_textureLoader.load2dTexture("DOF Render", fontPath));
	dofText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true));
	dofText->setColor(textColor);

	// Motion blur - text
	shared_ptr<TextEntity> motionText = make_shared<TextEntity>("motionBlurText");
	motionText->setDiffuseMap(_textureLoader.load2dTexture("Motion Blur Render", fontPath));
	motionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true));
	motionText->setColor(textColor);

	// Bind
	_imageEntityColorRenderer.bind();

	// Render debug surfaces
	_imageEntityColorRenderer.render(worldSurface);
	_imageEntityColorRenderer.render(shadowSurface);
	_imageEntityColorRenderer.render(bloomSurface);
	_imageEntityColorRenderer.render(planarReflectionSurface);
	_imageEntityColorRenderer.render(waterReflectionSurface);
	_imageEntityColorRenderer.render(waterRefractionSurface);
	_imageEntityColorRenderer.render(depthSurface);
	_imageEntityColorRenderer.render(dofSurface);
	_imageEntityColorRenderer.render(motionBlurSurface);

	// Render debug text
	_imageEntityColorRenderer.render(worldText);
	_imageEntityColorRenderer.render(shadowText);
	_imageEntityColorRenderer.render(bloomText);
	_imageEntityColorRenderer.render(planarReflectionText);
	_imageEntityColorRenderer.render(waterReflectionText);
	_imageEntityColorRenderer.render(waterRefractionText);
	_imageEntityColorRenderer.render(depthText);
	_imageEntityColorRenderer.render(dofText);
	_imageEntityColorRenderer.render(motionText);

	// Unbind
	_imageEntityColorRenderer.unbind();
}