#include "model_manager.hpp"

#include <map>

using std::make_shared;
using std::map;

const shared_ptr<Model> ModelManager::getModel(const string & modelId) const
{
	const auto iterator = _models.find(modelId);

	if(iterator == _models.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Model>> & ModelManager::getModels() const
{
	return _models;
}

void ModelManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void ModelManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void ModelManager::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void ModelManager::inject(shared_ptr<CaptorManager> captorManager)
{
	_captorManager = captorManager;
}

void ModelManager::inject(shared_ptr<MeshLoader> meshLoader)
{
	_meshLoader = meshLoader;
}

void ModelManager::inject(shared_ptr<VertexBufferCache> vertexBufferCache)
{
	_vertexBufferCache = vertexBufferCache;
}

void ModelManager::createModel(const string & modelId, const string & meshPath)
{
	if(isModelExisting(modelId))
	{
		abort();
	}

	const auto mesh = _meshLoader->loadMesh(meshPath);

	if(mesh == nullptr)
	{
		return;
	}

	const auto model = make_shared<Model>(modelId);

	for(const auto & part : mesh->getParts())
	{
		vector<float> bufferData = {};

		for(int index = 0; index < static_cast<int>(part->getPositions().size()); index++)
		{
			bufferData.push_back(part->getPositions()[index].x);
			bufferData.push_back(part->getPositions()[index].y);
			bufferData.push_back(part->getPositions()[index].z);

			bufferData.push_back(part->getUvs()[index].x);
			bufferData.push_back(part->getUvs()[index].y);

			bufferData.push_back(part->getNormals()[index].x);
			bufferData.push_back(part->getNormals()[index].y);
			bufferData.push_back(part->getNormals()[index].z);

			bufferData.push_back(part->getTangents()[index].x);
			bufferData.push_back(part->getTangents()[index].y);
			bufferData.push_back(part->getTangents()[index].z);
		}

		model->createPart(part->getId());

		auto vertexBuffer = _vertexBufferCache->getBuffer(meshPath, part->getId());

		if(vertexBuffer == nullptr)
		{
			vertexBuffer = make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], static_cast<int>(bufferData.size()));

			_vertexBufferCache->storeBuffer(meshPath, part->getId(), vertexBuffer);
		}

		model->setVertexBuffer(part->getId(), vertexBuffer);
	}

	model->setMeshPath(meshPath);

	_models.insert({modelId, model});
}

void ModelManager::deleteModel(const string & modelId)
{
	if(!isModelExisting(modelId))
	{
		abort();
	}

	_models.erase(modelId);
}

void ModelManager::deleteModels()
{
	_models.clear();
}

const bool ModelManager::isModelExisting(const string & modelId) const
{
	return (_models.find(modelId) != _models.end());
}

const bool ModelManager::isModelsExisting() const
{
	return !_models.empty();
}

void ModelManager::update()
{
	for(const auto & [modelId, model] : _models)
	{
		model->updateTarget();

		if(model->getLevelOfDetailId().empty())
		{
			model->setLevelOfDetailed(false);
		}
		else
		{
			if(getModels().find(model->getLevelOfDetailId()) == getModels().end())
			{
				abort();
			}

			const auto cameraPosition = _camera->getPosition();
			const auto modelPosition = model->getBasePosition();
			const auto levelOfDetailDistance = model->getLevelOfDetailDistance();
			const auto totalDistance = Mathematics::calculateDistance(cameraPosition, modelPosition);

			model->setLevelOfDetailed(totalDistance > levelOfDetailDistance);
		}

		if(_captorManager->getCaptors().find(model->getPreviousCaptorId()) == _captorManager->getCaptors().end())
		{
			model->setPreviousCaptorId("");
			model->setCubeReflectionMixValue(1.0f);
			model->setCubeRefractionMixValue(1.0f);
		}

		if(_captorManager->getCaptors().find(model->getCurrentCaptorId()) == _captorManager->getCaptors().end())
		{
			model->setCurrentCaptorId("");
			model->setCubeReflectionMixValue(1.0f);
			model->setCubeRefractionMixValue(1.0f);
		}

		if(model->getPreviousCaptorId() == model->getCurrentCaptorId())
		{
			model->setPreviousCaptorId("");
			model->setCubeReflectionMixValue(1.0f);
			model->setCubeRefractionMixValue(1.0f);
		}

		if((_timer->getPassedUpdateCount() % CAPTOR_OVERLAP_INTERVAL) == 0)
		{
			map<float, shared_ptr<Captor>> orderedCaptors = {};

			for(const auto & [captorId, captor] : _captorManager->getCaptors())
			{
				const auto distance = Mathematics::calculateDistance(model->getBasePosition(), captor->getPosition());

				orderedCaptors.insert({distance, captor});
			}

			if(!orderedCaptors.empty())
			{
				const auto closestCaptorId = orderedCaptors.begin()->second->getId();

				if(model->getCurrentCaptorId() != closestCaptorId)
				{
					model->setPreviousCaptorId(model->getCurrentCaptorId());
					model->setCurrentCaptorId(closestCaptorId);

					if(!model->getPreviousCaptorId().empty())
					{
						model->setCubeReflectionMixValue(0.0f);
						model->setCubeRefractionMixValue(0.0f);
					}
				}
			}

			model->setCubeReflectionMixValue(model->getCubeReflectionMixValue() + CAPTOR_OVERLAP_SPEED);
			model->setCubeRefractionMixValue(model->getCubeRefractionMixValue() + CAPTOR_OVERLAP_SPEED);
		}

		if(model->isVisible())
		{
			model->updateTransformation();
		}
	}
}