#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::_renderSkyEntity()
{
	if(_entityBus->getMainSkyEntity() != nullptr)
	{
		_skyEntityColorRenderer.bind();

		_skyEntityColorRenderer.render(_entityBus->getMainSkyEntity(), _entityBus->getMixSkyEntity());

		_skyEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(_entityBus->getTerrainEntity() != nullptr)
	{
		_terrainEntityColorRenderer.bind();

		_terrainEntityColorRenderer.processPointlightEntities(_entityBus->getPointLightEntities());

		_terrainEntityColorRenderer.processSpotlightEntities(_entityBus->getSpotlightEntities());

		_terrainEntityColorRenderer.render(_entityBus->getTerrainEntity());

		_terrainEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(_entityBus->getWaterEntity() != nullptr)
	{
		_waterEntityColorRenderer.bind();

		_waterEntityColorRenderer.processPointlightEntities(_entityBus->getPointLightEntities());

		_waterEntityColorRenderer.processSpotlightEntities(_entityBus->getSpotlightEntities());

		_waterEntityColorRenderer.render(_entityBus->getWaterEntity());

		_waterEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderModelEntities()
{
	auto modelEntities = _entityBus->getModelEntities();

	if(!modelEntities.empty())
	{
		_modelEntityColorRenderer.bind();

		_modelEntityColorRenderer.processPointlightEntities(_entityBus->getPointLightEntities());

		_modelEntityColorRenderer.processSpotlightEntities(_entityBus->getSpotlightEntities());

		for(const auto& [keyID, modelEntity] : modelEntities)
		{
			for(const auto& partID : modelEntity->getPartIDs())
			{
				if(modelEntity->getTransparency(partID) != 1.0f)
				{
					goto CONTINUE;
				}
			}

			if(modelEntity->isLevelOfDetailed())
			{
				auto levelOfDetailEntity = modelEntities.find(modelEntity->getLevelOfDetailEntityID())->second;

				fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
				fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
				fvec3 initialSize = levelOfDetailEntity->getBaseSize();
				bool initialVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformationMatrix();

				_modelEntityColorRenderer.render(levelOfDetailEntity, _entityBus->getReflectionEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _entityBus->getReflectionEntities());
			}

			CONTINUE:;
		}

		for(const auto& [keyID, modelEntity] : modelEntities)
		{
			bool isSolid = true;
			for(const auto& partID : modelEntity->getPartIDs())
			{
				if(modelEntity->getTransparency(partID) != 1.0f)
				{
					isSolid = false;
					break;
				}
			}
			if(isSolid)
			{
				continue;
			}

			if(modelEntity->isLevelOfDetailed())
			{
				auto levelOfDetailEntity = modelEntities.find(modelEntity->getLevelOfDetailEntityID())->second;

				fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
				fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
				fvec3 initialSize = levelOfDetailEntity->getBaseSize();
				bool initialVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformationMatrix();

				_modelEntityColorRenderer.render(levelOfDetailEntity, _entityBus->getReflectionEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _entityBus->getReflectionEntities());
			}
		}

		_modelEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderBillboardEntities()
{
	auto billboardEntities = _entityBus->getBillboardEntities();

	if(!billboardEntities.empty())
	{
		_billboardEntityColorRenderer.bind();

		for(const auto& [keyID, entity] : billboardEntities)
		{
			_billboardEntityColorRenderer.render(entity);
		}

		_billboardEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(_renderBus.isAabbFrameRenderingEnabled())
	{
		auto aabbEntities = _entityBus->getAabbEntities();

		if(!aabbEntities.empty())
		{
			_aabbEntityColorRenderer.bind();

			for(const auto& [keyID, entity] : aabbEntities)
			{
				_aabbEntityColorRenderer.render(entity);
			}

			_aabbEntityColorRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalWorldImage()
{
	_renderSurface->setMirroredVertically(true);

	_renderSurface->setDiffuseMap(_renderBus.getFinalWorldMap());

	_imageEntityColorRenderer.bind();
	_imageEntityColorRenderer.render(_renderSurface);
	_imageEntityColorRenderer.unbind();

	_renderSurface->setMirroredVertically(true);
}

void MasterRenderer::_renderGUI()
{
	if(!_entityBus->getImageEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		_imageEntityColorRenderer.bind();

		map<unsigned int, shared_ptr<ImageEntity>> orderedEntityMap;
		for(const auto& [keyID, entity] : _entityBus->getImageEntities())
		{
			if(entity->getID() != _renderBus.getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
			}
		}
		for(const auto& [keyID, entity] : _entityBus->getTextEntities())
		{
			orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
		}

		for(const auto& [keyID, entity] : orderedEntityMap)
		{
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if(castedTextEntity == nullptr)
			{
				_imageEntityColorRenderer.render(entity);
			}
			else
			{
				_imageEntityColorRenderer.render(castedTextEntity);
			}
		}

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
	const string fontPath = "engine\\assets\\font\\font.ttf";
	const fvec3 textColor = fvec3(0.75f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	function<float(string)> calcTextWidth = [&](string text)
	{
		return (static_cast<float>(text.size()) * charWidth);
	};

	auto worldSurface = make_shared<ImageEntity>("worldSurface", true, make_shared<RenderBuffer>(-0.666f, 0.666f, 0.666f, 0.666f, true));
	worldSurface->setDiffuseMap(_renderBus.getPrimaryWorldMap());
	worldSurface->setMirroredVertically(true);

	auto shadowSurface = make_shared<ImageEntity>("shadowSurface", true, make_shared<RenderBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true));
	shadowSurface->setDiffuseMap(_renderBus.getShadowMap());
	shadowSurface->setColor(fvec3(static_cast<float>(_renderBus.getShadowMap() != 0)));
	shadowSurface->setMirroredVertically(true);

	auto bloomSurface = make_shared<ImageEntity>("bloomSurface", true, make_shared<RenderBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true));
	bloomSurface->setDiffuseMap(_renderBus.getBloomMap());
	bloomSurface->setColor(fvec3(static_cast<float>(_renderBus.getBloomMap() != 0)));
	bloomSurface->setMirroredVertically(true);

	auto planarReflectionSurface = make_shared<ImageEntity>("planarReflectionSurface", true, make_shared<RenderBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true));
	planarReflectionSurface->setDiffuseMap(_renderBus.getPlanarReflectionMap());
	planarReflectionSurface->setColor(fvec3(static_cast<float>(_renderBus.getPlanarReflectionMap() != 0)));
	planarReflectionSurface->setMirroredVertically(true);

	auto waterReflectionSurface = make_shared<ImageEntity>("waterReflectionSurface", true, make_shared<RenderBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true));
	waterReflectionSurface->setDiffuseMap(_renderBus.getWaterReflectionMap());
	waterReflectionSurface->setColor(fvec3(static_cast<float>(_renderBus.getWaterReflectionMap() != 0)));
	waterReflectionSurface->setMirroredVertically(true);

	auto waterRefractionSurface = make_shared<ImageEntity>("waterRefractionSurface", true, make_shared<RenderBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true));
	waterRefractionSurface->setDiffuseMap(_renderBus.getWaterRefractionMap());
	waterRefractionSurface->setColor(fvec3(static_cast<float>(_renderBus.getWaterRefractionMap() != 0)));
	waterRefractionSurface->setMirroredVertically(true);

	auto depthSurface = make_shared<ImageEntity>("depthSurface", true, make_shared<RenderBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true));
	depthSurface->setDiffuseMap(_renderBus.getDepthMap());
	depthSurface->setColor(fvec3(static_cast<float>(_renderBus.getDepthMap() != 0)));
	depthSurface->setMirroredVertically(true);
	depthSurface->setPerspectiveDepthEntity(true);

	auto dofSurface = make_shared<ImageEntity>("dofSurface", true, make_shared<RenderBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true));
	dofSurface->setDiffuseMap(_renderBus.getDofMap());
	dofSurface->setColor(fvec3(static_cast<float>(_renderBus.getDofMap() != 0)));
	dofSurface->setMirroredVertically(true);

	auto motionBlurSurface = make_shared<ImageEntity>("motionBlurSurface", true, make_shared<RenderBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true));
	motionBlurSurface->setDiffuseMap(_renderBus.getMotionBlurMap());
	motionBlurSurface->setColor(fvec3(static_cast<float>(_renderBus.getMotionBlurMap() != 0)));
	motionBlurSurface->setMirroredVertically(true);

	auto worldText = make_shared<TextEntity>("worldText", true, make_shared<RenderBuffer>(-0.666f, 0.4f, calcTextWidth("World Render"), charHeight, true));
	worldText->setDiffuseMap(_textureLoader.load2dTexture("World Render", fontPath));
	worldText->setColor(textColor);

	auto shadowText = make_shared<TextEntity>("shadowText", true, make_shared<RenderBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true));
	shadowText->setDiffuseMap(_textureLoader.load2dTexture("Shadow Render", fontPath));
	shadowText->setColor(textColor);

	auto bloomText = make_shared<TextEntity>("bloomText", true, make_shared<RenderBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true));
	bloomText->setDiffuseMap(_textureLoader.load2dTexture("Bloom Render", fontPath));
	bloomText->setColor(textColor);

	auto planarReflectionText = make_shared<TextEntity>("planarReflectionText", true, make_shared<RenderBuffer>(-0.666f, -0.26f, calcTextWidth("Planar Reflection Render"), charHeight, true));
	planarReflectionText->setDiffuseMap(_textureLoader.load2dTexture("Planar Reflection Render", fontPath));
	planarReflectionText->setColor(textColor);

	auto waterReflectionText = make_shared<TextEntity>("waterReflectionText", true, make_shared<RenderBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true));
	waterReflectionText->setDiffuseMap(_textureLoader.load2dTexture("Water Reflection Render", fontPath));
	waterReflectionText->setColor(textColor);

	auto waterRefractionText = make_shared<TextEntity>("waterRefractionText", true, make_shared<RenderBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true));
	waterRefractionText->setDiffuseMap(_textureLoader.load2dTexture("Water Refraction Render", fontPath));
	waterRefractionText->setColor(textColor);

	auto depthText = make_shared<TextEntity>("depthText", true, make_shared<RenderBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true));
	depthText->setDiffuseMap(_textureLoader.load2dTexture("Depth Render", fontPath));
	depthText->setColor(textColor);

	auto dofText = make_shared<TextEntity>("dofText", true, make_shared<RenderBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true));
	dofText->setDiffuseMap(_textureLoader.load2dTexture("DOF Render", fontPath));
	dofText->setColor(textColor);

	auto motionBlurText = make_shared<TextEntity>("motionBlurText", true, make_shared<RenderBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true));
	motionBlurText->setDiffuseMap(_textureLoader.load2dTexture("Motion Blur Render", fontPath));
	motionBlurText->setColor(textColor);

	_imageEntityColorRenderer.bind();
	_imageEntityColorRenderer.render(worldSurface);
	_imageEntityColorRenderer.render(shadowSurface);
	_imageEntityColorRenderer.render(bloomSurface);
	_imageEntityColorRenderer.render(planarReflectionSurface);
	_imageEntityColorRenderer.render(waterReflectionSurface);
	_imageEntityColorRenderer.render(waterRefractionSurface);
	_imageEntityColorRenderer.render(depthSurface);
	_imageEntityColorRenderer.render(dofSurface);
	_imageEntityColorRenderer.render(motionBlurSurface);
	_imageEntityColorRenderer.render(worldText);
	_imageEntityColorRenderer.render(shadowText);
	_imageEntityColorRenderer.render(bloomText);
	_imageEntityColorRenderer.render(planarReflectionText);
	_imageEntityColorRenderer.render(waterReflectionText);
	_imageEntityColorRenderer.render(waterRefractionText);
	_imageEntityColorRenderer.render(depthText);
	_imageEntityColorRenderer.render(dofText);
	_imageEntityColorRenderer.render(motionBlurText);
	_imageEntityColorRenderer.unbind();
}