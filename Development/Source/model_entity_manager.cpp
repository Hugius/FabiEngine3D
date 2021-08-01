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
		Logger::throwError("Non-existing model entity with ID \"" + ID + "\" requested!");
	}

	return result;
}

const unordered_map<string, shared_ptr<ModelEntity>>& ModelEntityManager::getEntities()
{
	return _getModelEntities();
}

void ModelEntityManager::createEntity(const string& ID, const string& meshPath, Vec3 T, Vec3 R, Vec3 S)
{
	// Create entity
	_createEntity(ID);
	
	// Load mesh
	loadMesh(ID, meshPath);

	// Set properties
	auto entity = getEntity(ID);
	entity->setPosition(T);
	entity->setRotation(R);
	entity->setSize(S);
	entity->setLevelOfDetailSize(S);
}

void ModelEntityManager::loadMesh(const string& ID, const string& meshPath)
{
	// Temporary values
	auto entity = getEntity(ID);

	// Load mesh file
	auto partsPointer = _meshLoader.loadMesh(meshPath);
	entity->setMeshPath(meshPath);
	entity->clearParts();

	// Check if model loading failed
	if (partsPointer == nullptr)
	{
		// Add empty part so the entity does not crash the engine
		entity->addPart("");
		return;
	}
	
	// Dereference parts pointer
	auto parts = *partsPointer;

	// Check if multiparted model actually has multiple parts
	if (parts.size() == 1 && !parts[0].ID.empty())
	{
		// Add empty part so the entity does not crash the engine
		parts[0].ID = "";

		// Warning
		Logger::throwWarning("Multiparted model with ID \"" + ID + "\" only has 1 part!");
	}

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
		entity->addPart(part.ID);

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

			// Check if entity has LOD
			if (!entity->getLodEntityID().empty())
			{
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