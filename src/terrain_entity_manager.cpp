#include "terrain_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;
using std::min;

const shared_ptr<TerrainEntity> TerrainEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<TerrainEntity> TerrainEntityManager::getSelectedEntity() const
{
	if(_entities.empty() || _selectedEntityId.empty())
	{
		return nullptr;
	}

	return getEntity(_selectedEntityId);
}

const unordered_map<string, shared_ptr<TerrainEntity>> & TerrainEntityManager::getEntities() const
{
	return _entities;
}

void TerrainEntityManager::createEntity(const string & id, const string & heightMapPath)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto image = _imageLoader->loadImage(heightMapPath);

	if(image == nullptr)
	{
		return;
	}

	auto entity = make_shared<TerrainEntity>(id);

	const auto size = min(min(image->getWidth(), image->getHeight()), static_cast<unsigned int>(MAX_SIZE));
	const auto bitsPerPixel = ((image->getPixelFormat() == PixelFormat::RGB) ? 3 : 4);

	vector<float> pixels;
	for(unsigned int index = 0; index < (size * size * bitsPerPixel); index += bitsPerPixel)
	{
		const auto r = (static_cast<float>(image->getPixels()[index + 0]) / 255.0f);
		const auto g = (static_cast<float>(image->getPixels()[index + 1]) / 255.0f);
		const auto b = (static_cast<float>(image->getPixels()[index + 2]) / 255.0f);

		const auto intensity = ((r + g + b) / 3.0f);

		pixels.push_back(intensity);
	}

	entity->setHeightMapPath(heightMapPath);
	entity->setPixels(pixels);
	entity->setSize(static_cast<float>(size));

	_entities.insert({id, entity});

	loadVertexBuffer(id);
}

void TerrainEntityManager::selectEntity(const string & id)
{
	if(!isEntityExisting(id) && !id.empty())
	{
		abort();
	}

	_selectedEntityId = id;
}

void TerrainEntityManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void TerrainEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);

	if(id == _selectedEntityId)
	{
		selectEntity("");
	}
}

void TerrainEntityManager::deleteEntities()
{
	_entities.clear();

	selectEntity("");
}

const bool TerrainEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool TerrainEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void TerrainEntityManager::loadVertexBuffer(const string & id)
{
	_loadVertexBuffer(getEntity(id), getEntity(id)->getSize(), getEntity(id)->getMaxHeight(), getEntity(id)->getPixels());
}

void TerrainEntityManager::_loadVertexBuffer(shared_ptr<TerrainEntity> entity, float size, float maxHeight, const vector<float> & pixels)
{
	const auto halfSize = (size * 0.5f);
	const auto uSize = static_cast<unsigned int>(size);

	vector<fvec3> tempPositions;
	vector<fvec2> tempUvs;
	vector<fvec3> tempNormals;
	for(float z = 0.0f; z < size; z += 1.0f)
	{
		for(float x = 0.0f; x < size; x += 1.0f)
		{
			const auto flippedZ = (size - z);

			const auto height = _getPixelHeight(x, flippedZ, size, maxHeight, pixels);
			const auto leftHeight = _getPixelHeight((x - 1), flippedZ, size, maxHeight, pixels);
			const auto rightHeight = _getPixelHeight((x + 1), flippedZ, size, maxHeight, pixels);
			const auto upHeight = _getPixelHeight(x, (flippedZ + 1), size, maxHeight, pixels);
			const auto downHeight = _getPixelHeight(x, (flippedZ - 1), size, maxHeight, pixels);

			const auto position = fvec3((x - halfSize), height, (z - halfSize));
			const auto uv = fvec2((x / size), (flippedZ / size));
			const auto normal = Mathematics::normalize(fvec3((leftHeight - rightHeight), 3.0f, (downHeight - upHeight)));

			tempPositions.push_back(position);
			tempUvs.push_back(uv);
			tempNormals.push_back(normal);
		}
	}

	vector<fvec3> positions;
	vector<fvec2> uvs;
	vector<fvec3> normals;
	for(unsigned int z = 0; z < (uSize - 1); z++)
	{
		for(unsigned int x = 0; x < (uSize - 1); x++)
		{
			auto topLeftIndex = ((z * uSize) + x);
			auto topRightIndex = (topLeftIndex + 1);
			auto bottomLeftIndex = (((z + 1) * uSize) + x);
			auto bottomRightIndex = (bottomLeftIndex + 1);

			positions.push_back(tempPositions[topLeftIndex]);
			uvs.push_back(tempUvs[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);

			positions.push_back(tempPositions[bottomLeftIndex]);
			uvs.push_back(tempUvs[bottomLeftIndex]);
			normals.push_back(tempNormals[bottomLeftIndex]);

			positions.push_back(tempPositions[bottomRightIndex]);
			uvs.push_back(tempUvs[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			positions.push_back(tempPositions[bottomRightIndex]);
			uvs.push_back(tempUvs[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);

			positions.push_back(tempPositions[topRightIndex]);
			uvs.push_back(tempUvs[topRightIndex]);
			normals.push_back(tempNormals[topRightIndex]);

			positions.push_back(tempPositions[topLeftIndex]);
			uvs.push_back(tempUvs[topLeftIndex]);
			normals.push_back(tempNormals[topLeftIndex]);
		}
	}

	vector<fvec3> tangents;
	for(unsigned int index = 0; index < static_cast<unsigned int>(positions.size()); index += 3)
	{
		const auto pos1 = positions[index + 0];
		const auto pos2 = positions[index + 1];
		const auto pos3 = positions[index + 2];

		const auto deltaPos1 = (pos2 - pos1);
		const auto deltaPos2 = (pos3 - pos1);

		const auto uv1 = uvs[index + 0];
		const auto uv2 = uvs[index + 1];
		const auto uv3 = uvs[index + 2];

		const auto deltaUv1 = (uv2 - uv1);
		const auto deltaUv2 = (uv3 - uv1);

		const auto r = (1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x));

		const auto tangent = ((deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * r);

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
	}

	vector<float> bufferData;
	for(unsigned int index = 0; index < static_cast<unsigned int>(positions.size()); index++)
	{
		bufferData.push_back(positions[index].x);
		bufferData.push_back(positions[index].y);
		bufferData.push_back(positions[index].z);

		bufferData.push_back(uvs[index].x);
		bufferData.push_back(uvs[index].y);

		bufferData.push_back(normals[index].x);
		bufferData.push_back(normals[index].y);
		bufferData.push_back(normals[index].z);

		bufferData.push_back(tangents[index].x);
		bufferData.push_back(tangents[index].y);
		bufferData.push_back(tangents[index].z);
	}

	auto bufferDataCount = static_cast<unsigned int>(bufferData.size());

	entity->setVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], bufferDataCount));
}

const float TerrainEntityManager::getPixelHeight(const string & id, float x, float z)
{
	const auto flippedZ = (getEntity(id)->getSize() - z);

	return _getPixelHeight(x, flippedZ, getEntity(id)->getSize(), getEntity(id)->getMaxHeight(), getEntity(id)->getPixels());
}

const bool TerrainEntityManager::isInside(const string & id, float x, float z)
{
	if((x > 0) && (z > 0) && (x < getEntity(id)->getSize()) && (z < getEntity(id)->getSize()))
	{
		return true;
	}

	return false;
}

float TerrainEntityManager::_getPixelHeight(float x, float z, float size, float maxHeight, const vector<float> & pixels)
{
	if(x == size)
	{
		x -= 1.0f;
	}

	if(z == size)
	{
		z -= 1.0f;
	}

	if((x < 0) || (x > size) || (z < 0) || (z > size))
	{
		return 0.0f;
	}

	const auto index = (static_cast<unsigned int>(z) * static_cast<unsigned int>(size)) + static_cast<unsigned int>(x);

	return (pixels[index] * maxHeight);
}