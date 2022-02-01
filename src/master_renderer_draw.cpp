#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::renderLogo(shared_ptr<Quad2dEntity> logo, const ivec2& viewport)
{
	glViewport(0, 0, viewport.x, viewport.y);

	glClear(GL_COLOR_BUFFER_BIT);

	_quad2dEntityColorRenderer.bind();

	_quad2dEntityColorRenderer.render(logo);

	_quad2dEntityColorRenderer.unbind();
}

void MasterRenderer::renderApplication()
{
	_timer->startDeltaPart("depthPreRender");
	_captureWorldDepth();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("shadowPreRender");
	_captureShadows();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("reflectionPreRender");
	_captureCubeReflections();
	_capturePlanarReflections();
	_timer->stopDeltaPart();
	_timer->startDeltaPart("refractionPreRender");
	// insert capture cube/planar refractions here
	_timer->stopDeltaPart();
	_timer->startDeltaPart("waterPreRender");
	_captureWaterReflections();
	_captureWaterRefractions();
	_captureWaterEdges();
	_timer->stopDeltaPart();

	_timer->startDeltaPart("3dEntityRender");
	_worldColorCaptor->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_renderBus->setTriangleCountingEnabled(true);
	_renderSkyEntity();
	_renderTerrainEntity();
	_renderWaterEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderAabbEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();
	_renderBus->setTriangleCountingEnabled(false);
	_worldColorCaptor->unbind();
	_renderBus->setPrimarySceneMap(_worldColorCaptor->getTexture(0));
	_renderBus->setSecondarySceneMap(_worldColorCaptor->getTexture(1));
	_renderBus->setFinalSceneMap(_renderBus->getPrimarySceneMap());
	_timer->stopDeltaPart();

	_timer->startDeltaPart("postProcessing");
	_captureAntiAliasing();
	_captureBloom();
	_captureDOF();
	_captureLensFlare();
	_captureMotionBlur();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(Config::getInst().getViewportPosition().x, Config::getInst().getViewportPosition().y, Config::getInst().getViewportSize().x, Config::getInst().getViewportSize().y);
	_renderFinalSceneMap();
	glViewport(0, 0, Config::getInst().getWindowSize().x, Config::getInst().getWindowSize().y);
	_timer->stopDeltaPart();

	_timer->startDeltaPart("2dEntityRender");
	_renderBus->setTriangleCountingEnabled(true);
	_renderGUI();
	_renderBus->setTriangleCountingEnabled(false);
	_timer->stopDeltaPart();
}

void MasterRenderer::_renderSkyEntity()
{
	if(_skyEntityManager->getSelectedEntity() != nullptr)
	{
		_skyEntityColorRenderer.bind();

		_skyEntityColorRenderer.render(_skyEntityManager->getSelectedEntity());

		_skyEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(_terrainEntityManager->getSelectedEntity() != nullptr)
	{
		_terrainEntityColorRenderer.bind();

		_terrainEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_terrainEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		_terrainEntityColorRenderer.render(_terrainEntityManager->getSelectedEntity());

		_terrainEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(_waterEntityManager->getSelectedEntity() != nullptr)
	{
		_waterEntityColorRenderer.bind();

		_waterEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_waterEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		_waterEntityColorRenderer.render(_waterEntityManager->getSelectedEntity());

		_waterEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderOpaqueModelEntities()
{
	if(!_modelEntityManager->getEntities().empty())
	{
		_modelEntityColorRenderer.bind();

		_modelEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_modelEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		for(const auto& [key, modelEntity] : _modelEntityManager->getEntities())
		{
			bool isTransparent = false;

			for(const auto& partId : modelEntity->getPartIds())
			{
				if(modelEntity->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;
				}
			}

			if(isTransparent)
			{
				continue;
			}

			if(modelEntity->isLevelOfDetailed())
			{
				const auto levelOfDetailEntity = _modelEntityManager->getEntities().find(modelEntity->getLevelOfDetailEntityId())->second;
				const auto originalPosition = levelOfDetailEntity->getBasePosition();
				const auto originalRotation = levelOfDetailEntity->getBaseRotation();
				const auto originalSize = levelOfDetailEntity->getBaseSize();
				const auto originalVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformation();

				_modelEntityColorRenderer.render(levelOfDetailEntity, _reflectionEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(originalPosition);
				levelOfDetailEntity->setBaseRotation(originalRotation);
				levelOfDetailEntity->setBaseSize(originalSize);
				levelOfDetailEntity->setVisible(originalVisibility);
				levelOfDetailEntity->updateTransformation();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _reflectionEntityManager->getEntities());
			}
		}

		_modelEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTransparentModelEntities()
{
	if(!_modelEntityManager->getEntities().empty())
	{
		_modelEntityColorRenderer.bind();

		_modelEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_modelEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		for(const auto& [key, modelEntity] : _modelEntityManager->getEntities())
		{
			bool isTransparent = false;

			for(const auto& partId : modelEntity->getPartIds())
			{
				if(modelEntity->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;
					break;
				}
			}

			if(!isTransparent)
			{
				continue;
			}

			if(modelEntity->isLevelOfDetailed())
			{
				const auto levelOfDetailEntity = _modelEntityManager->getEntities().find(modelEntity->getLevelOfDetailEntityId())->second;
				const auto originalPosition = levelOfDetailEntity->getBasePosition();
				const auto originalRotation = levelOfDetailEntity->getBaseRotation();
				const auto originalSize = levelOfDetailEntity->getBaseSize();
				const auto originalVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * originalSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformation();

				_modelEntityColorRenderer.render(levelOfDetailEntity, _reflectionEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(originalPosition);
				levelOfDetailEntity->setBaseRotation(originalRotation);
				levelOfDetailEntity->setBaseSize(originalSize);
				levelOfDetailEntity->setVisible(originalVisibility);
				levelOfDetailEntity->updateTransformation();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _reflectionEntityManager->getEntities());
			}
		}

		_modelEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderOpaqueQuad3dEntities()
{
	if(!_quad3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer.bind();

		for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->getOpacity() < 1.0f)
			{
				continue;
			}

			_quad3dEntityColorRenderer.render(entity);
		}

		_quad3dEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTransparentQuad3dEntities()
{
	if(!_quad3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer.bind();

		for(const auto& [key, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->getOpacity() == 1.0f)
			{
				continue;
			}

			_quad3dEntityColorRenderer.render(entity);
		}

		_quad3dEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderOpaqueText3dEntities()
{
	if(!_text3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer.bind();

		for(const auto& [key, textEntity] : _text3dEntityManager->getEntities())
		{
			if(textEntity->getOpacity() < 1.0f)
			{
				continue;
			}

			for(const auto& characterEntity : textEntity->getCharacterEntities())
			{
				_quad3dEntityColorRenderer.render(characterEntity);
			}
		}

		_quad3dEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTransparentText3dEntities()
{
	if(!_text3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer.bind();

		for(const auto& [key, textEntity] : _text3dEntityManager->getEntities())
		{
			if(textEntity->getOpacity() == 1.0f)
			{
				continue;
			}

			for(const auto& characterEntity : textEntity->getCharacterEntities())
			{
				_quad3dEntityColorRenderer.render(characterEntity);
			}
		}

		_quad3dEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(!_aabbEntityManager->getEntities().empty())
	{
		_aabbEntityColorRenderer.bind();

		for(const auto& [key, entity] : _aabbEntityManager->getEntities())
		{
			_aabbEntityColorRenderer.render(entity);
		}

		_aabbEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderFinalSceneMap()
{
	_renderSurface->setDiffuseMap(_renderBus->getFinalSceneMap());

	_quad2dEntityColorRenderer.bind();
	_quad2dEntityColorRenderer.render(_renderSurface);
	_quad2dEntityColorRenderer.unbind();
}

void MasterRenderer::_renderGUI()
{
	if(!_quad2dEntityManager->getEntities().empty() || !_text2dEntityManager->getEntities().empty())
	{
		_quad2dEntityColorRenderer.bind();

		map<unsigned int, shared_ptr<BaseEntity>> orderedEntityMap;
		for(const auto& [key, entity] : _quad2dEntityManager->getEntities())
		{
			if(entity->getId() != _renderBus->getCursorEntityId())
			{
				orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
			}
		}
		for(const auto& [key, entity] : _text2dEntityManager->getEntities())
		{
			orderedEntityMap.insert(make_pair(entity->getDepth(), entity));
		}

		for(const auto& [key, entity] : orderedEntityMap)
		{
			auto castedQuad2dEntity = dynamic_pointer_cast<Quad2dEntity>(entity);
			auto castedText2dEntity = dynamic_pointer_cast<Text2dEntity>(entity);

			if(castedQuad2dEntity != nullptr)
			{
				_quad2dEntityColorRenderer.render(castedQuad2dEntity);
			}

			if(castedText2dEntity != nullptr)
			{
				for(const auto& characterEntity : castedText2dEntity->getCharacterEntities())
				{
					_quad2dEntityColorRenderer.render(characterEntity);
				}
			}
		}

		if(!_renderBus->getCursorEntityId().empty())
		{
			_quad2dEntityColorRenderer.render(_quad2dEntityManager->getEntities().at(_renderBus->getCursorEntityId()));
		}

		_quad2dEntityColorRenderer.unbind();
	}
}