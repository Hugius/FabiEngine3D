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

void MasterRenderer::_renderFinalSceneMap()
{
	_renderQuad->setDiffuseMap(_renderBus.getFinalSceneMap());

	_quadEntityColorRenderer.bind();
	_quadEntityColorRenderer.render(_renderQuad);
	_quadEntityColorRenderer.unbind();
}

void MasterRenderer::_renderGUI()
{
	if(!_entityBus->getQuadEntities().empty() || !_entityBus->getTextEntities().empty())
	{
		_quadEntityColorRenderer.bind();

		map<unsigned int, shared_ptr<BaseEntity>> orderedEntityMap;
		for(const auto& [key, quadEntity] : _entityBus->getQuadEntities())
		{
			if(quadEntity->getID() != _renderBus.getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(quadEntity->getDepth(), quadEntity));
			}
		}
		for(const auto& [key, textEntity] : _entityBus->getTextEntities())
		{
			orderedEntityMap.insert(make_pair(textEntity->getDepth(), textEntity));
		}

		for(const auto& [key, entity] : orderedEntityMap)
		{
			auto castedQuadEntity = dynamic_pointer_cast<QuadEntity>(entity);
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if(castedQuadEntity != nullptr)
			{
				_quadEntityColorRenderer.render(castedQuadEntity);
			}

			if(castedTextEntity != nullptr)
			{
				for(const auto& characterEntity : castedTextEntity->getCharacterEntities())
				{
					_quadEntityColorRenderer.render(characterEntity);
				}
			}
		}

		_quadEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderCursor()
{
	for(const auto& [key, entity] : _entityBus->getQuadEntities())
	{
		if(entity->getID() == _renderBus.getCursorEntityID())
		{
			_quadEntityColorRenderer.bind();
			_quadEntityColorRenderer.render(entity);
			_quadEntityColorRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderDebugScreens()
{
	const string fontPath = "engine\\assets\\image\\font_map\\font.bmp";
	const fvec3 textColor = fvec3(0.75f);
	const float charWidth = 0.025f;
	const float charHeight = 0.1f;
	function<float(string)> calcTextWidth = [&](string text)
	{
		return (static_cast<float>(text.size()) * charWidth);
	};

	shared_ptr<QuadEntity> sceneQuad = make_shared<QuadEntity>("sceneQuad");
	sceneQuad->setMesh(make_shared<VertexBuffer>(-0.666f, 0.666f, 0.666f, 0.666f, true));
	sceneQuad->setDiffuseMap(_renderBus.getFinalSceneMap());
	sceneQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> shadowQuad = make_shared<QuadEntity>("shadowQuad");
	shadowQuad->setMesh(make_shared<VertexBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true));
	shadowQuad->setDiffuseMap(_renderBus.getShadowMap());
	shadowQuad->setColor(fvec3(static_cast<float>(_renderBus.getShadowMap() != nullptr)));
	shadowQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> bloomQuad = make_shared<QuadEntity>("bloomQuad");
	bloomQuad->setMesh(make_shared<VertexBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true));
	bloomQuad->setDiffuseMap(_renderBus.getBloomMap());
	bloomQuad->setColor(fvec3(static_cast<float>(_renderBus.getBloomMap() != nullptr)));
	bloomQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> planarReflectionQuad = make_shared<QuadEntity>("planarReflectionQuad");
	planarReflectionQuad->setMesh(make_shared<VertexBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true));
	planarReflectionQuad->setDiffuseMap(_renderBus.getPlanarReflectionMap());
	planarReflectionQuad->setColor(fvec3(static_cast<float>(_renderBus.getPlanarReflectionMap() != nullptr)));
	planarReflectionQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> waterReflectionQuad = make_shared<QuadEntity>("waterReflectionQuad");
	waterReflectionQuad->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true));
	waterReflectionQuad->setDiffuseMap(_renderBus.getWaterReflectionMap());
	waterReflectionQuad->setColor(fvec3(static_cast<float>(_renderBus.getWaterReflectionMap() != nullptr)));
	waterReflectionQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> waterRefractionQuad = make_shared<QuadEntity>("waterRefractionQuad");
	waterRefractionQuad->setMesh(make_shared<VertexBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true));
	waterRefractionQuad->setDiffuseMap(_renderBus.getWaterRefractionMap());
	waterRefractionQuad->setColor(fvec3(static_cast<float>(_renderBus.getWaterRefractionMap() != nullptr)));
	waterRefractionQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> depthQuad = make_shared<QuadEntity>("depthQuad");
	depthQuad->setMesh(make_shared<VertexBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true));
	depthQuad->setDiffuseMap(_renderBus.getDepthMap());
	depthQuad->setColor(fvec3(static_cast<float>(_renderBus.getDepthMap() != nullptr)));
	depthQuad->setMirroredVertically(true);
	depthQuad->setPerspectiveDepthEntity(true);

	shared_ptr<QuadEntity> dofQuad = make_shared<QuadEntity>("dofQuad");
	dofQuad->setMesh(make_shared<VertexBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true));
	dofQuad->setDiffuseMap(_renderBus.getDofMap());
	dofQuad->setColor(fvec3(static_cast<float>(_renderBus.getDofMap() != nullptr)));
	dofQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> motionBlurQuad = make_shared<QuadEntity>("motionBlurQuad");
	motionBlurQuad->setMesh(make_shared<VertexBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true));
	motionBlurQuad->setDiffuseMap(_renderBus.getMotionBlurMap());
	motionBlurQuad->setColor(fvec3(static_cast<float>(_renderBus.getMotionBlurMap() != nullptr)));
	motionBlurQuad->setMirroredVertically(true);

	/*shared_ptr<TextEntity> worldText = make_shared<TextEntity>("worldText");
	worldText->setMesh(make_shared<VertexBuffer>(-0.666f, 0.4f, calcTextWidth("World Render"), charHeight, true));
	worldText->setDiffuseMap(_imageLoader.load2dTexture("World Render", fontPath));
	worldText->setColor(textColor);

	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setMesh(make_shared<VertexBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true));
	shadowText->setDiffuseMap(_imageLoader.load2dTexture("Shadow Render", fontPath));
	shadowText->setColor(textColor);

	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setMesh(make_shared<VertexBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true));
	bloomText->setDiffuseMap(_imageLoader.load2dTexture("Bloom Render", fontPath));
	bloomText->setColor(textColor);

	shared_ptr<TextEntity> planarReflectionText = make_shared<TextEntity>("planarReflectionText");
	planarReflectionText->setMesh(make_shared<VertexBuffer>(-0.666f, -0.26f, calcTextWidth("Planar Reflection Render"), charHeight, true));
	planarReflectionText->setDiffuseMap(_imageLoader.load2dTexture("Planar Reflection Render", fontPath));
	planarReflectionText->setColor(textColor);

	shared_ptr<TextEntity> waterReflectionText = make_shared<TextEntity>("waterReflectionText");
	waterReflectionText->setMesh(make_shared<VertexBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true));
	waterReflectionText->setDiffuseMap(_imageLoader.load2dTexture("Water Reflection Render", fontPath));
	waterReflectionText->setColor(textColor);

	shared_ptr<TextEntity> waterRefractionText = make_shared<TextEntity>("waterRefractionText");
	waterRefractionText->setMesh(make_shared<VertexBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true));
	waterRefractionText->setDiffuseMap(_imageLoader.load2dTexture("Water Refraction Render", fontPath));
	waterRefractionText->setColor(textColor);

	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setMesh(make_shared<VertexBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true));
	depthText->setDiffuseMap(_imageLoader.load2dTexture("Depth Render", fontPath));
	depthText->setColor(textColor);

	shared_ptr<TextEntity> dofText = make_shared<TextEntity>("dofText");
	dofText->setMesh(make_shared<VertexBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true));
	dofText->setDiffuseMap(_imageLoader.load2dTexture("DOF Render", fontPath));
	dofText->setColor(textColor);

	shared_ptr<TextEntity> motionBlurText = make_shared<TextEntity>("motionBlurText");
	motionBlurText->setMesh(make_shared<VertexBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true));
	motionBlurText->setDiffuseMap(_imageLoader.load2dTexture("Motion Blur Render", fontPath));
	motionBlurText->setColor(textColor);*/

	_quadEntityColorRenderer.bind();
	_quadEntityColorRenderer.render(sceneQuad);
	_quadEntityColorRenderer.render(shadowQuad);
	_quadEntityColorRenderer.render(bloomQuad);
	_quadEntityColorRenderer.render(planarReflectionQuad);
	_quadEntityColorRenderer.render(waterReflectionQuad);
	_quadEntityColorRenderer.render(waterRefractionQuad);
	_quadEntityColorRenderer.render(depthQuad);
	_quadEntityColorRenderer.render(dofQuad);
	_quadEntityColorRenderer.render(motionBlurQuad);
	/*_quadEntityColorRenderer.render(worldText);
	_quadEntityColorRenderer.render(shadowText);
	_quadEntityColorRenderer.render(bloomText);
	_quadEntityColorRenderer.render(planarReflectionText);
	_quadEntityColorRenderer.render(waterReflectionText);
	_quadEntityColorRenderer.render(waterRefractionText);
	_quadEntityColorRenderer.render(depthText);
	_quadEntityColorRenderer.render(dofText);
	_quadEntityColorRenderer.render(motionBlurText);*/
	_quadEntityColorRenderer.unbind();
}