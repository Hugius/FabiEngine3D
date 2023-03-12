#include "terrain_manager.hpp"

using std::make_shared;
using std::min;

const shared_ptr<Terrain> TerrainManager::getTerrain(const string & terrainId) const
{
	const auto iterator = _terrains.find(terrainId);

	if(iterator == _terrains.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<Terrain> TerrainManager::getSelectedTerrain() const
{
	if(_terrains.empty() || _selectedTerrainId.empty())
	{
		return nullptr;
	}

	return getTerrain(_selectedTerrainId);
}

const unordered_map<string, shared_ptr<Terrain>> & TerrainManager::getTerrains() const
{
	return _terrains;
}

void TerrainManager::createTerrain(const string & terrainId, const string & heightMapPath)
{
	if(isTerrainExisting(terrainId))
	{
		abort();
	}

	const auto image = _imageLoader->getImage(heightMapPath);

	if(image == nullptr)
	{
		return;
	}

	const auto terrain = make_shared<Terrain>(terrainId);
	const auto size = min(min(image->getWidth(), image->getHeight()), static_cast<int>(MAX_TERRAIN_SIZE));
	const auto bytesPerPixel = (image->getBitsPerPixel() / 8);

	vector<float> pixels = {};

	for(int index = 0; index < (size * size * bytesPerPixel); index += bytesPerPixel)
	{
		const auto red = (static_cast<float>(image->getPixels()[index + 0]) / 255.0f);
		const auto green = (static_cast<float>(image->getPixels()[index + 1]) / 255.0f);
		const auto blue = (static_cast<float>(image->getPixels()[index + 2]) / 255.0f);
		const auto intensity = ((red + green + blue) / 3.0f);

		pixels.push_back(intensity);
	}

	terrain->setHeightMapPath(heightMapPath);
	terrain->setPixels(pixels);
	terrain->setSize(static_cast<float>(size));

	_terrains.insert({terrainId, terrain});

	loadTerrainVertexBuffer(terrainId);
}

void TerrainManager::selectTerrain(const string & terrainId)
{
	if(!isTerrainExisting(terrainId) && !terrainId.empty())
	{
		abort();
	}

	_selectedTerrainId = terrainId;
}

void TerrainManager::inject(shared_ptr<ImageLoader> imageLoader)
{
	_imageLoader = imageLoader;
}

void TerrainManager::deleteTerrain(const string & terrainId)
{
	if(!isTerrainExisting(terrainId))
	{
		abort();
	}

	_terrains.erase(terrainId);

	if(terrainId == _selectedTerrainId)
	{
		selectTerrain("");
	}
}

void TerrainManager::deleteTerrains()
{
	_terrains.clear();

	selectTerrain("");
}

const bool TerrainManager::isTerrainExisting(const string & terrainId) const
{
	return (_terrains.find(terrainId) != _terrains.end());
}

const bool TerrainManager::isTerrainsExisting() const
{
	return !_terrains.empty();
}

void TerrainManager::loadTerrainVertexBuffer(const string & terrainId)
{
	_loadTerrainVertexBuffer(getTerrain(terrainId), getTerrain(terrainId)->getSize(), getTerrain(terrainId)->getMaxHeight(), getTerrain(terrainId)->getPixels());
}

void TerrainManager::_loadTerrainVertexBuffer(shared_ptr<Terrain> terrain, float size, float maxHeight, const vector<float> & pixels)
{
	const auto halfSize = (size * 0.5f);

	vector<fvec3> tempPositions = {};
	vector<fvec2> tempUvs = {};
	vector<fvec3> tempNormals = {};

	for(float z = 0.0f; z < size; z += 1.0f)
	{
		for(float x = 0.0f; x < size; x += 1.0f)
		{
			const auto flippedZ = (size - z);
			const auto height = _getTerrainPixelHeight(x, flippedZ, size, maxHeight, pixels);
			const auto leftHeight = _getTerrainPixelHeight((x - 1), flippedZ, size, maxHeight, pixels);
			const auto rightHeight = _getTerrainPixelHeight((x + 1), flippedZ, size, maxHeight, pixels);
			const auto upHeight = _getTerrainPixelHeight(x, (flippedZ + 1), size, maxHeight, pixels);
			const auto downHeight = _getTerrainPixelHeight(x, (flippedZ - 1), size, maxHeight, pixels);
			const auto position = fvec3((x - halfSize), height, (z - halfSize));
			const auto uv = fvec2((x / size), (flippedZ / size));
			const auto normal = Mathematics::normalize(fvec3((leftHeight - rightHeight), 3.0f, (downHeight - upHeight)));

			tempPositions.push_back(position);
			tempUvs.push_back(uv);
			tempNormals.push_back(normal);
		}
	}

	vector<fvec3> positions = {};
	vector<fvec2> uvs = {};
	vector<fvec3> normals = {};

	for(int z = 0; z < (static_cast<int>(size) - 1); z++)
	{
		for(int x = 0; x < (static_cast<int>(size) - 1); x++)
		{
			const auto topLeftIndex = ((z * static_cast<int>(size)) + x);
			const auto topRightIndex = (topLeftIndex + 1);
			const auto bottomLeftIndex = (((z + 1) * static_cast<int>(size)) + x);
			const auto bottomRightIndex = (bottomLeftIndex + 1);

			positions.push_back(tempPositions[topLeftIndex]);
			positions.push_back(tempPositions[bottomLeftIndex]);
			positions.push_back(tempPositions[bottomRightIndex]);
			positions.push_back(tempPositions[bottomRightIndex]);
			positions.push_back(tempPositions[topRightIndex]);
			positions.push_back(tempPositions[topLeftIndex]);

			uvs.push_back(tempUvs[topLeftIndex]);
			uvs.push_back(tempUvs[bottomLeftIndex]);
			uvs.push_back(tempUvs[bottomRightIndex]);
			uvs.push_back(tempUvs[bottomRightIndex]);
			uvs.push_back(tempUvs[topRightIndex]);
			uvs.push_back(tempUvs[topLeftIndex]);

			normals.push_back(tempNormals[topLeftIndex]);
			normals.push_back(tempNormals[bottomLeftIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);
			normals.push_back(tempNormals[bottomRightIndex]);
			normals.push_back(tempNormals[topRightIndex]);
			normals.push_back(tempNormals[topLeftIndex]);
		}
	}

	vector<fvec3> tangents = {};

	for(int index = 0; index < static_cast<int>(positions.size()); index += 3)
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

	vector<float> bufferData = {};

	for(int index = 0; index < static_cast<int>(positions.size()); index++)
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

	const auto bufferDataCount = static_cast<int>(bufferData.size());

	terrain->setVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], bufferDataCount));
}

const float TerrainManager::getTerrainPixelHeight(const string & terrainId, float x, float z)
{
	const auto flippedZ = (getTerrain(terrainId)->getSize() - z);

	return _getTerrainPixelHeight(x, flippedZ, getTerrain(terrainId)->getSize(), getTerrain(terrainId)->getMaxHeight(), getTerrain(terrainId)->getPixels());
}

const bool TerrainManager::isInside(const string & terrainId, float x, float z)
{
	if((x > 0) && (z > 0) && (x < getTerrain(terrainId)->getSize()) && (z < getTerrain(terrainId)->getSize()))
	{
		return true;
	}

	return false;
}

float TerrainManager::_getTerrainPixelHeight(float x, float z, float size, float maxHeight, const vector<float> & pixels)
{
	auto xInt = static_cast<int>(x);
	auto zInt = static_cast<int>(z);
	auto sizeInt = static_cast<int>(size);

	if(xInt < 0)
	{
		xInt = 0;
	}
	else if(xInt >= sizeInt)
	{
		xInt = (sizeInt - 1);
	}

	if(zInt < 0)
	{
		zInt = 0;
	}
	else if(zInt >= sizeInt)
	{
		zInt = (sizeInt - 1);
	}

	const auto index = ((zInt * sizeInt) + xInt);

	return (pixels[index] * maxHeight);
}