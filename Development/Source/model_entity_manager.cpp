
#include "model_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

ModelEntityManager::ModelEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus)
	:
	BaseEntityManager(EntityType::MODEL, meshLoader, texLoader, renderBus)
{

}

shared_ptr<ModelEntity> ModelEntityManager::getEntity(const string& ID)
{
	auto result = _getModelEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("ModelEntityManager::getEntity");
	}

	return result;
}

const unordered_map<string, shared_ptr<ModelEntity>>& ModelEntityManager::getEntities()
{
	return _getModelEntities();
}

void ModelEntityManager::createEntity(const string& ID, const string& meshPath)
{
	// Create entity
	_createEntity(ID);

	// Load mesh file
	auto partsPointer = _meshLoader.loadMesh(meshPath);

	// Check if model loading failed
	if (partsPointer == nullptr)
	{
		deleteEntity(ID);
		return;
	}

	// Check if multiparted model only has 1 part
	auto parts = *partsPointer;
	if ((parts.size() == 1) && !parts[0].ID.empty())
	{
		Logger::throwWarning("Multiparted model with ID \"" + ID + "\" only has 1 part!");
		deleteEntity(ID);
		return;
	}

	// Temporary values
	auto entity = getEntity(ID);

	// Set mesh path
	entity->setMeshPath(meshPath);

	// Process parts
	for (const auto& part : parts)
	{
		// Temporary values
		vector<float> bufferData;

		// For every triangle vertex point
		for (size_t i = 0; i < part.vertices.size(); i++)
		{
			// Vertex coordinate
			bufferData.push_back(part.vertices[i].x);
			bufferData.push_back(part.vertices[i].y);
			bufferData.push_back(part.vertices[i].z);

			// UV coordinate
			bufferData.push_back(part.uvCoords[i].x);
			bufferData.push_back(part.uvCoords[i].y);

			// Normal vector
			bufferData.push_back(part.normals[i].x);
			bufferData.push_back(part.normals[i].y);
			bufferData.push_back(part.normals[i].z);

			// Tangent vector
			bufferData.push_back(part.tangents[i].x);
			bufferData.push_back(part.tangents[i].y);
			bufferData.push_back(part.tangents[i].z);
		}

		// New model part
		entity->createPart(part.ID);

		// Render buffer
		entity->setRenderBuffer(make_shared<RenderBuffer>(BufferType::VERTEX_UV_NORMAL_TANGENT, &bufferData[0], static_cast<unsigned int>(bufferData.size())), part.ID);

		// Diffuse map
		if (part.diffuseMapPath != "")
		{
			entity->setDiffuseMap(_textureLoader.getTexture2D(part.diffuseMapPath, true, true), part.ID);
			entity->setDiffuseMapPath(part.diffuseMapPath, part.ID);
		}

		// Emission map
		if (part.emissionMapPath != "")
		{
			entity->setEmissionMap(_textureLoader.getTexture2D(part.emissionMapPath, true, true), part.ID);
			entity->setEmissionMapPath(part.emissionMapPath, part.ID);
		}

		// Reflection map
		if (part.reflectionMapPath != "")
		{
			entity->setReflectionMap(_textureLoader.getTexture2D(part.reflectionMapPath, true, true), part.ID);
			entity->setReflectionMapPath(part.reflectionMapPath, part.ID);
		}

		// Normal map
		if (part.normalMapPath != "")
		{
			entity->setNormalMap(_textureLoader.getTexture2D(part.normalMapPath, true, true), part.ID);
			entity->setNormalMapPath(part.normalMapPath, part.ID);
		}
	}
}

void ModelEntityManager::update()
{
	for (const auto& [keyID, entity] : _getModelEntities())
	{
		if (entity->isVisible())
		{
			// Update model matrix
			entity->updateModelMatrix();

			// Check if entity has a LOD entity
			if (!entity->getLodEntityID().empty())
			{
				// Check if LOD entity still exists
				auto lodEntityPair = getEntities().find(entity->getID());
				if (lodEntityPair == getEntities().end())
				{
					Logger::throwError("ModelEntityManager::update");
				}

				// Calculate absolute distance between camera and entity
				Vec3 camPos = _renderBus.getCameraPosition();
				Vec3 entityPos = entity->getPosition();
				float xDistance = fabsf(camPos.x - entityPos.x);
				float yDistance = fabsf(camPos.y - entityPos.y);
				float zDistance = fabsf(camPos.z - entityPos.z);
				float absolsuteDistance = sqrtf((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));

				// Check if farther than LOD distance
				bool isFarEnough = (absolsuteDistance > _lodDistance) && (!entity->getLodEntityID().empty());
				entity->setLevelOfDetailed(isFarEnough);
			}
		}
	}
}

void ModelEntityManager::setLodDistance(float distance)
{
	_lodDistance = distance;
}

float ModelEntityManager::getLodDistance()
{
	return _lodDistance;
}