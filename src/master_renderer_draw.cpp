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

		for(const auto& [key, modelEntity] : modelEntities)
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

		for(const auto& [key, modelEntity] : modelEntities)
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

		for(const auto& [key, entity] : billboardEntities)
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

			for(const auto& [key, entity] : aabbEntities)
			{
				_aabbEntityColorRenderer.render(entity);
			}

			_aabbEntityColorRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalWorldImage()
{
	_renderImage->setDiffuseMap(_renderBus.getFinalWorldMap());

	_imageEntityColorRenderer.bind();
	_imageEntityColorRenderer.render(_renderImage);
	_imageEntityColorRenderer.unbind();
}

void MasterRenderer::_renderGUI()
{
	if(!_entityBus->getImageEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		_imageEntityColorRenderer.bind();

		map<unsigned int, shared_ptr<BaseEntity>> orderedEntityMap;
		for(const auto& [key, imageEntity] : _entityBus->getImageEntities())
		{
			if(imageEntity->getID() != _renderBus.getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(imageEntity->getDepth(), imageEntity));
			}
		}
		for(const auto& [key, textEntity] : _entityBus->getTextEntities())
		{
			orderedEntityMap.insert(make_pair(textEntity->getDepth(), textEntity));
		}

		for(const auto& [key, entity] : orderedEntityMap)
		{
			auto castedImageEntity = dynamic_pointer_cast<ImageEntity>(entity);
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if(castedImageEntity != nullptr)
			{
				_imageEntityColorRenderer.render(castedImageEntity);
			}

			if(castedTextEntity != nullptr)
			{
				for(const auto& characterEntity : castedTextEntity->getCharacterEntities())
				{
					_imageEntityColorRenderer.render(characterEntity);
				}
			}
		}

		_imageEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderCursor()
{
	for(const auto& [key, entity] : _entityBus->getImageEntities())
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
	const string fontPath = "engine\\assets\\image\\font_map\\font.png";
	const fvec3 textColor = fvec3(0.75f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	function<float(string)> calcTextWidth = [&](string text)
	{
		return (static_cast<float>(text.size()) * charWidth);
	};

	shared_ptr<ImageEntity> worldImage = make_shared<ImageEntity>("worldImage");
	worldImage->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.666f, 0.666f, 0.666f, true));
	worldImage->setDiffuseMap(_renderBus.getPrimaryWorldMap());
	worldImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> shadowImage = make_shared<ImageEntity>("shadowImage");
	shadowImage->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true));
	shadowImage->setDiffuseMap(_renderBus.getShadowMap());
	shadowImage->setColor(fvec3(static_cast<float>(_renderBus.getShadowMap() != 0)));
	shadowImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> bloomImage = make_shared<ImageEntity>("bloomImage");
	bloomImage->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true));
	bloomImage->setDiffuseMap(_renderBus.getBloomMap());
	bloomImage->setColor(fvec3(static_cast<float>(_renderBus.getBloomMap() != 0)));
	bloomImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> planarReflectionImage = make_shared<ImageEntity>("planarReflectionImage");
	planarReflectionImage->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true));
	planarReflectionImage->setDiffuseMap(_renderBus.getPlanarReflectionMap());
	planarReflectionImage->setColor(fvec3(static_cast<float>(_renderBus.getPlanarReflectionMap() != 0)));
	planarReflectionImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> waterReflectionImage = make_shared<ImageEntity>("waterReflectionImage");
	waterReflectionImage->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true));
	waterReflectionImage->setDiffuseMap(_renderBus.getWaterReflectionMap());
	waterReflectionImage->setColor(fvec3(static_cast<float>(_renderBus.getWaterReflectionMap() != 0)));
	waterReflectionImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> waterRefractionImage = make_shared<ImageEntity>("waterRefractionImage");
	waterRefractionImage->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true));
	waterRefractionImage->setDiffuseMap(_renderBus.getWaterRefractionMap());
	waterRefractionImage->setColor(fvec3(static_cast<float>(_renderBus.getWaterRefractionMap() != 0)));
	waterRefractionImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> depthImage = make_shared<ImageEntity>("depthImage");
	depthImage->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true));
	depthImage->setDiffuseMap(_renderBus.getDepthMap());
	depthImage->setColor(fvec3(static_cast<float>(_renderBus.getDepthMap() != 0)));
	depthImage->setMirroredVertically(true);
	depthImage->setPerspectiveDepthEntity(true);

	shared_ptr<ImageEntity> dofImage = make_shared<ImageEntity>("dofImage");
	dofImage->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true));
	dofImage->setDiffuseMap(_renderBus.getDofMap());
	dofImage->setColor(fvec3(static_cast<float>(_renderBus.getDofMap() != 0)));
	dofImage->setMirroredVertically(true);

	shared_ptr<ImageEntity> motionBlurImage = make_shared<ImageEntity>("motionBlurImage");
	motionBlurImage->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true));
	motionBlurImage->setDiffuseMap(_renderBus.getMotionBlurMap());
	motionBlurImage->setColor(fvec3(static_cast<float>(_renderBus.getMotionBlurMap() != 0)));
	motionBlurImage->setMirroredVertically(true);

	/*shared_ptr<TextEntity> worldText = make_shared<TextEntity>("worldText");
	worldText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, 0.4f, calcTextWidth("World Render"), charHeight, true));
	worldText->setDiffuseMap(_textureLoader.load2dTexture("World Render", fontPath));
	worldText->setColor(textColor);

	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true));
	shadowText->setDiffuseMap(_textureLoader.load2dTexture("Shadow Render", fontPath));
	shadowText->setColor(textColor);

	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true));
	bloomText->setDiffuseMap(_textureLoader.load2dTexture("Bloom Render", fontPath));
	bloomText->setColor(textColor);

	shared_ptr<TextEntity> planarReflectionText = make_shared<TextEntity>("planarReflectionText");
	planarReflectionText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.26f, calcTextWidth("Planar Reflection Render"), charHeight, true));
	planarReflectionText->setDiffuseMap(_textureLoader.load2dTexture("Planar Reflection Render", fontPath));
	planarReflectionText->setColor(textColor);

	shared_ptr<TextEntity> waterReflectionText = make_shared<TextEntity>("waterReflectionText");
	waterReflectionText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true));
	waterReflectionText->setDiffuseMap(_textureLoader.load2dTexture("Water Reflection Render", fontPath));
	waterReflectionText->setColor(textColor);

	shared_ptr<TextEntity> waterRefractionText = make_shared<TextEntity>("waterRefractionText");
	waterRefractionText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true));
	waterRefractionText->setDiffuseMap(_textureLoader.load2dTexture("Water Refraction Render", fontPath));
	waterRefractionText->setColor(textColor);

	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setRenderBuffer(make_shared<RenderBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true));
	depthText->setDiffuseMap(_textureLoader.load2dTexture("Depth Render", fontPath));
	depthText->setColor(textColor);

	shared_ptr<TextEntity> dofText = make_shared<TextEntity>("dofText");
	dofText->setRenderBuffer(make_shared<RenderBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true));
	dofText->setDiffuseMap(_textureLoader.load2dTexture("DOF Render", fontPath));
	dofText->setColor(textColor);

	shared_ptr<TextEntity> motionBlurText = make_shared<TextEntity>("motionBlurText");
	motionBlurText->setRenderBuffer(make_shared<RenderBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true));
	motionBlurText->setDiffuseMap(_textureLoader.load2dTexture("Motion Blur Render", fontPath));
	motionBlurText->setColor(textColor);*/

	_imageEntityColorRenderer.bind();
	_imageEntityColorRenderer.render(worldImage);
	_imageEntityColorRenderer.render(shadowImage);
	_imageEntityColorRenderer.render(bloomImage);
	_imageEntityColorRenderer.render(planarReflectionImage);
	_imageEntityColorRenderer.render(waterReflectionImage);
	_imageEntityColorRenderer.render(waterRefractionImage);
	_imageEntityColorRenderer.render(depthImage);
	_imageEntityColorRenderer.render(dofImage);
	_imageEntityColorRenderer.render(motionBlurImage);
	/*_imageEntityColorRenderer.render(worldText);
	_imageEntityColorRenderer.render(shadowText);
	_imageEntityColorRenderer.render(bloomText);
	_imageEntityColorRenderer.render(planarReflectionText);
	_imageEntityColorRenderer.render(waterReflectionText);
	_imageEntityColorRenderer.render(waterRefractionText);
	_imageEntityColorRenderer.render(depthText);
	_imageEntityColorRenderer.render(dofText);
	_imageEntityColorRenderer.render(motionBlurText);*/
	_imageEntityColorRenderer.unbind();
}