#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::_renderSkyEntity()
{
	if(entityBus.getMainSkyEntity() != nullptr)
	{
		_skyEntityColorRenderer.bind(_skyEntityColorShader, renderBus);

		_skyEntityColorRenderer.render(_skyEntityColorShader, renderBus, entityBus.getMainSkyEntity(), entityBus.getMixSkyEntity());

		_skyEntityColorRenderer.unbind(_skyEntityColorShader);
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(entityBus.getTerrainEntity() != nullptr)
	{
		_terrainEntityColorRenderer.bind(_terrainEntityColorShader, renderBus);

		_terrainEntityColorRenderer.processPointlightEntities(_terrainEntityColorShader, entityBus.getPointLightEntities());

		_terrainEntityColorRenderer.processSpotlightEntities(_terrainEntityColorShader, entityBus.getSpotlightEntities());

		_terrainEntityColorRenderer.render(_terrainEntityColorShader, renderBus, entityBus.getTerrainEntity());

		_terrainEntityColorRenderer.unbind(_terrainEntityColorShader);
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(entityBus.getWaterEntity() != nullptr)
	{
		_waterEntityColorRenderer.bind(_waterEntityColorShader, renderBus);

		_waterEntityColorRenderer.processPointlightEntities(_waterEntityColorShader, entityBus.getPointLightEntities());

		_waterEntityColorRenderer.processSpotlightEntities(_waterEntityColorShader, entityBus.getSpotlightEntities());

		_waterEntityColorRenderer.render(_waterEntityColorShader, renderBus, entityBus.getWaterEntity());

		_waterEntityColorRenderer.unbind(_waterEntityColorShader);
	}
}

void MasterRenderer::_renderModelEntities()
{
	auto modelEntities = entityBus.getModelEntities();

	if(!modelEntities.empty())
	{
		_modelEntityColorRenderer.bind(_modelEntityColorShader, renderBus);

		_modelEntityColorRenderer.processPointlightEntities(_modelEntityColorShader, entityBus.getPointLightEntities());

		_modelEntityColorRenderer.processSpotlightEntities(_modelEntityColorShader, entityBus.getSpotlightEntities());

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

				_modelEntityColorRenderer.render(_modelEntityColorShader, renderBus, levelOfDetailEntity, entityBus.getReflectionEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(_modelEntityColorShader, renderBus, modelEntity, entityBus.getReflectionEntities());
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

				_modelEntityColorRenderer.render(_modelEntityColorShader, renderBus, levelOfDetailEntity, entityBus.getReflectionEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(_modelEntityColorShader, renderBus, modelEntity, entityBus.getReflectionEntities());
			}
		}

		_modelEntityColorRenderer.unbind(_modelEntityColorShader);
	}
}

void MasterRenderer::_renderBillboardEntities()
{
	auto billboardEntities = entityBus.getBillboardEntities();

	if(!billboardEntities.empty())
	{
		_billboardEntityColorRenderer.bind(_billboardEntityColorShader, renderBus);

		for(const auto& [key, entity] : billboardEntities)
		{
			_billboardEntityColorRenderer.render(_billboardEntityColorShader, renderBus, entity);
		}

		_billboardEntityColorRenderer.unbind(_billboardEntityColorShader);
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(renderBus->isAabbFrameRenderingEnabled())
	{
		auto aabbEntities = entityBus.getAabbEntities();

		if(!aabbEntities.empty())
		{
			_aabbEntityColorRenderer.bind(_aabbEntityColorShader, renderBus);

			for(const auto& [key, entity] : aabbEntities)
			{
				_aabbEntityColorRenderer.render(_aabbEntityColorShader, renderBus, entity);
			}

			_aabbEntityColorRenderer.unbind(_aabbEntityColorShader);
		}
	}
}

void MasterRenderer::_renderFinalSceneMap(RenderBus& renderBus)
{
	_renderQuad->setDiffuseMap(renderBus->getFinalSceneMap());

	_quadEntityColorRenderer.bind(_quadEntityColorShader, renderBus);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, _renderQuad);
	_quadEntityColorRenderer.unbind(_quadEntityColorShader);
}

void MasterRenderer::_renderGUI()
{
	if(!entityBus.getQuadEntities().empty() || !entityBus.getTextEntities().empty())
	{
		_quadEntityColorRenderer.bind(_quadEntityColorShader, renderBus);

		map<unsigned int, shared_ptr<BaseEntity>> orderedEntityMap;
		for(const auto& [key, quadEntity] : entityBus.getQuadEntities())
		{
			if(quadEntity->getID() != renderBus->getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(quadEntity->getDepth(), quadEntity));
			}
		}
		for(const auto& [key, textEntity] : entityBus.getTextEntities())
		{
			orderedEntityMap.insert(make_pair(textEntity->getDepth(), textEntity));
		}

		for(const auto& [key, entity] : orderedEntityMap)
		{
			auto castedQuadEntity = dynamic_pointer_cast<QuadEntity>(entity);
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if(castedQuadEntity != nullptr)
			{
				_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, castedQuadEntity);
			}

			if(castedTextEntity != nullptr)
			{
				for(const auto& characterEntity : castedTextEntity->getCharacterEntities())
				{
					_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, characterEntity);
				}
			}
		}

		_quadEntityColorRenderer.unbind(_quadEntityColorShader);
	}
}

void MasterRenderer::_renderCursor()
{
	for(const auto& [key, entity] : entityBus.getQuadEntities())
	{
		if(entity->getID() == renderBus->getCursorEntityID())
		{
			_quadEntityColorRenderer.bind(_quadEntityColorShader, renderBus);
			_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, entity);
			_quadEntityColorRenderer.unbind(_quadEntityColorShader);
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
	sceneQuad->setDiffuseMap(renderBus->getFinalSceneMap());
	sceneQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> shadowQuad = make_shared<QuadEntity>("shadowQuad");
	shadowQuad->setMesh(make_shared<VertexBuffer>(0.0f, 0.666f, 0.666f, 0.666f, true));
	shadowQuad->setDiffuseMap(renderBus->getShadowMap());
	shadowQuad->setColor(fvec3(static_cast<float>(renderBus->getShadowMap() != nullptr)));
	shadowQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> bloomQuad = make_shared<QuadEntity>("bloomQuad");
	bloomQuad->setMesh(make_shared<VertexBuffer>(0.666f, 0.666f, 0.666f, 0.666f, true));
	bloomQuad->setDiffuseMap(renderBus->getBloomMap());
	bloomQuad->setColor(fvec3(static_cast<float>(renderBus->getBloomMap() != nullptr)));
	bloomQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> planarReflectionQuad = make_shared<QuadEntity>("planarReflectionQuad");
	planarReflectionQuad->setMesh(make_shared<VertexBuffer>(-0.666f, 0.0f, 0.666f, 0.666f, true));
	planarReflectionQuad->setDiffuseMap(renderBus->getPlanarReflectionMap());
	planarReflectionQuad->setColor(fvec3(static_cast<float>(renderBus->getPlanarReflectionMap() != nullptr)));
	planarReflectionQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> waterReflectionQuad = make_shared<QuadEntity>("waterReflectionQuad");
	waterReflectionQuad->setMesh(make_shared<VertexBuffer>(0.0f, 0.0f, 0.666f, 0.666f, true));
	waterReflectionQuad->setDiffuseMap(renderBus->getWaterReflectionMap());
	waterReflectionQuad->setColor(fvec3(static_cast<float>(renderBus->getWaterReflectionMap() != nullptr)));
	waterReflectionQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> waterRefractionQuad = make_shared<QuadEntity>("waterRefractionQuad");
	waterRefractionQuad->setMesh(make_shared<VertexBuffer>(0.666f, 0.0f, 0.666f, 0.666f, true));
	waterRefractionQuad->setDiffuseMap(renderBus->getWaterRefractionMap());
	waterRefractionQuad->setColor(fvec3(static_cast<float>(renderBus->getWaterRefractionMap() != nullptr)));
	waterRefractionQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> depthQuad = make_shared<QuadEntity>("depthQuad");
	depthQuad->setMesh(make_shared<VertexBuffer>(-0.666f, -0.666f, 0.666f, 0.666f, true));
	depthQuad->setDiffuseMap(renderBus->getDepthMap());
	depthQuad->setColor(fvec3(static_cast<float>(renderBus->getDepthMap() != nullptr)));
	depthQuad->setMirroredVertically(true);
	depthQuad->setPerspectiveDepthEntity(true);

	shared_ptr<QuadEntity> dofQuad = make_shared<QuadEntity>("dofQuad");
	dofQuad->setMesh(make_shared<VertexBuffer>(0.0f, -0.666f, 0.666f, 0.666f, true));
	dofQuad->setDiffuseMap(renderBus->getDofMap());
	dofQuad->setColor(fvec3(static_cast<float>(renderBus->getDofMap() != nullptr)));
	dofQuad->setMirroredVertically(true);

	shared_ptr<QuadEntity> motionBlurQuad = make_shared<QuadEntity>("motionBlurQuad");
	motionBlurQuad->setMesh(make_shared<VertexBuffer>(0.666f, -0.666f, 0.666f, 0.666f, true));
	motionBlurQuad->setDiffuseMap(renderBus->getMotionBlurMap());
	motionBlurQuad->setColor(fvec3(static_cast<float>(renderBus->getMotionBlurMap() != nullptr)));
	motionBlurQuad->setMirroredVertically(true);

	/*shared_ptr<TextEntity> worldText = make_shared<TextEntity>("worldText");
	worldText->setMesh(make_shared<VertexBuffer>(-0.666f, 0.4f, calcTextWidth("World Render"), charHeight, true));
	worldText->setDiffuseMap(_imageLoader->load2dTexture("World Render", fontPath));
	worldText->setColor(textColor);

	shared_ptr<TextEntity> shadowText = make_shared<TextEntity>("shadowText");
	shadowText->setMesh(make_shared<VertexBuffer>(0.0f, 0.4f, calcTextWidth("Shadow Render"), charHeight, true));
	shadowText->setDiffuseMap(_imageLoader->load2dTexture("Shadow Render", fontPath));
	shadowText->setColor(textColor);

	shared_ptr<TextEntity> bloomText = make_shared<TextEntity>("bloomText");
	bloomText->setMesh(make_shared<VertexBuffer>(0.666f, 0.4f, calcTextWidth("Bloom Render"), charHeight, true));
	bloomText->setDiffuseMap(_imageLoader->load2dTexture("Bloom Render", fontPath));
	bloomText->setColor(textColor);

	shared_ptr<TextEntity> planarReflectionText = make_shared<TextEntity>("planarReflectionText");
	planarReflectionText->setMesh(make_shared<VertexBuffer>(-0.666f, -0.26f, calcTextWidth("Planar Reflection Render"), charHeight, true));
	planarReflectionText->setDiffuseMap(_imageLoader->load2dTexture("Planar Reflection Render", fontPath));
	planarReflectionText->setColor(textColor);

	shared_ptr<TextEntity> waterReflectionText = make_shared<TextEntity>("waterReflectionText");
	waterReflectionText->setMesh(make_shared<VertexBuffer>(0.0f, -0.26f, calcTextWidth("Water Reflection Render"), charHeight, true));
	waterReflectionText->setDiffuseMap(_imageLoader->load2dTexture("Water Reflection Render", fontPath));
	waterReflectionText->setColor(textColor);

	shared_ptr<TextEntity> waterRefractionText = make_shared<TextEntity>("waterRefractionText");
	waterRefractionText->setMesh(make_shared<VertexBuffer>(0.666f, -0.26f, calcTextWidth("Water Refraction Render"), charHeight, true));
	waterRefractionText->setDiffuseMap(_imageLoader->load2dTexture("Water Refraction Render", fontPath));
	waterRefractionText->setColor(textColor);

	shared_ptr<TextEntity> depthText = make_shared<TextEntity>("depthText");
	depthText->setMesh(make_shared<VertexBuffer>(-0.666f, -0.92f, calcTextWidth("Depth Render"), charHeight, true));
	depthText->setDiffuseMap(_imageLoader->load2dTexture("Depth Render", fontPath));
	depthText->setColor(textColor);

	shared_ptr<TextEntity> dofText = make_shared<TextEntity>("dofText");
	dofText->setMesh(make_shared<VertexBuffer>(0.0f, -0.92f, calcTextWidth("DOF Render"), charHeight, true));
	dofText->setDiffuseMap(_imageLoader->load2dTexture("DOF Render", fontPath));
	dofText->setColor(textColor);

	shared_ptr<TextEntity> motionBlurText = make_shared<TextEntity>("motionBlurText");
	motionBlurText->setMesh(make_shared<VertexBuffer>(0.666f, -0.92f, calcTextWidth("Motion Blur Render"), charHeight, true));
	motionBlurText->setDiffuseMap(_imageLoader->load2dTexture("Motion Blur Render", fontPath));
	motionBlurText->setColor(textColor);*/

	_quadEntityColorRenderer.bind(_quadEntityColorShader, renderBus);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, sceneQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, shadowQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, bloomQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, planarReflectionQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, waterReflectionQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, waterRefractionQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, depthQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, dofQuad);
	_quadEntityColorRenderer.render(_quadEntityColorShader, renderBus, motionBlurQuad);
	/*_quadEntityColorRenderer.render(worldText);
	_quadEntityColorRenderer.render(shadowText);
	_quadEntityColorRenderer.render(bloomText);
	_quadEntityColorRenderer.render(planarReflectionText);
	_quadEntityColorRenderer.render(waterReflectionText);
	_quadEntityColorRenderer.render(waterRefractionText);
	_quadEntityColorRenderer.render(depthText);
	_quadEntityColorRenderer.render(dofText);
	_quadEntityColorRenderer.render(motionBlurText);*/
	_quadEntityColorRenderer.unbind(_quadEntityColorShader);
}