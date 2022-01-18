#include "master_renderer.hpp"
#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::_renderSkyEntity()
{
	if(_skyEntityManager->getSelectedMainSky() != nullptr)
	{
		_skyEntityColorRenderer.bind();

		_skyEntityColorRenderer.render(_skyEntityManager->getSelectedMainSky(), _skyEntityManager->getSelectedMixSky());

		_skyEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(_terrainEntityManager->getSelectedTerrain() != nullptr)
	{
		_terrainEntityColorRenderer.bind();

		_terrainEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_terrainEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		_terrainEntityColorRenderer.render(_terrainEntityManager->getSelectedTerrain());

		_terrainEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(_waterEntityManager->getSelectedWater() != nullptr)
	{
		_waterEntityColorRenderer.bind();

		_waterEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_waterEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		_waterEntityColorRenderer.render(_waterEntityManager->getSelectedWater());

		_waterEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderModelEntities()
{
	auto modelEntities = _modelEntityManager->getEntities();

	if(!modelEntities.empty())
	{
		_modelEntityColorRenderer.bind();

		_modelEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_modelEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

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

				_modelEntityColorRenderer.render(levelOfDetailEntity, _reflectionEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _reflectionEntityManager->getEntities());
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

				_modelEntityColorRenderer.render(levelOfDetailEntity, _reflectionEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _reflectionEntityManager->getEntities());
			}
		}

		_modelEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderQuad3dEntities()
{
	auto quad3dEntities = _quad3dEntityManager->getEntities();

	if(!quad3dEntities.empty())
	{
		_quad3dEntityColorRenderer.bind();

		for(const auto& [key, entity] : quad3dEntities)
		{
			_quad3dEntityColorRenderer.render(entity);
		}

		_quad3dEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderText3dEntities()
{
	auto text3dEntities = _text3dEntityManager->getEntities();

	if(!text3dEntities.empty())
	{
		_quad3dEntityColorRenderer.bind();

		for(const auto& [key, textEntity] : text3dEntities)
		{
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
	if(_renderBus->isAabbFrameRenderingEnabled())
	{
		auto aabbEntities = _aabbEntityManager->getEntities();

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
			if(entity->getID() != _renderBus->getCursorEntityID())
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

		if(!_renderBus->getCursorEntityID().empty())
		{
			_quad2dEntityColorRenderer.render(_quad2dEntityManager->getEntities().at(_renderBus->getCursorEntityID()));
		}

		_quad2dEntityColorRenderer.unbind();
	}
}