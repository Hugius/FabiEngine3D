#include "water_entity_manager.hpp"
#include "render_storage.hpp"

using std::make_shared;

const shared_ptr<WaterEntity> WaterManager::getWater(const string & waterId) const
{
	auto iterator = _waters.find(waterId);

	if(iterator == _waters.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<WaterEntity> WaterManager::getSelectedWater() const
{
	if(_waters.empty() || _selectedWaterId.empty())
	{
		return nullptr;
	}

	return getWater(_selectedWaterId);
}

const unordered_map<string, shared_ptr<WaterEntity>> & WaterManager::getWaters() const
{
	return _waters;
}

void WaterManager::selectWater(const string & waterId)
{
	if(!isWaterExisting(waterId) && !waterId.empty())
	{
		abort();
	}

	_selectedWaterId = waterId;
}

void WaterManager::createWater(const string & waterId)
{
	if(isWaterExisting(waterId))
	{
		abort();
	}

	auto entity = make_shared<WaterEntity>(waterId);

	_waters.insert({waterId, entity});

	loadWaterVertexBuffer(waterId);
}

void WaterManager::deleteWater(const string & waterId)
{
	if(!isWaterExisting(waterId))
	{
		abort();
	}

	_waters.erase(waterId);

	if(waterId == _selectedWaterId)
	{
		selectWater("");
	}
}

void WaterManager::deleteWaters()
{
	_waters.clear();

	selectWater("");
}

void WaterManager::loadWaterVertexBuffer(const string & waterId)
{
	_loadWaterVertexBuffer(getWater(waterId), getWater(waterId)->getSize());
}

const bool WaterManager::isWaterExisting(const string & waterId) const
{
	return (_waters.find(waterId) != _waters.end());
}

const bool WaterManager::isWatersExisting() const
{
	return !_waters.empty();
}

void WaterManager::_loadWaterVertexBuffer(shared_ptr<WaterEntity> entity, float size)
{
	const float halfSize = (size * 0.5f);

	const float lowQualityBufferData[] =
	{
		-halfSize, 0.0f, halfSize, 0.0f, 1.0f,
		-halfSize, 0.0f, -halfSize, 0.0f, 0.0f,
		halfSize, 0.0f, -halfSize, 1.0f, 0.0f,
		halfSize, 0.0f, -halfSize, 1.0f, 0.0f,
		halfSize, 0.0f, halfSize, 1.0f, 1.0f,
		-halfSize, 0.0f, halfSize, 0.0f, 1.0f
	};

	vector<float> highQualityBufferData;
	for(float x = -halfSize; x < halfSize; x++)
	{
		for(float z = -halfSize; z < halfSize; z++)
		{
			const float firstPositionX = x;
			const float firstPositionY = 0.0f;
			const float firstPositionZ = (z + 1);
			const float firstUvX = ((x + halfSize) / size);
			const float firstUvY = (((z + halfSize) / size) + (1.0f / size));

			const float secondPositionX = (x + 1.0f);
			const float secondPositionY = 0.0f;
			const float secondPositionZ = (z + 1.0f);
			const float secondUvX = (((x + halfSize) / size) + (1.0f / size));
			const float secondUvY = (((z + halfSize) / size) + (1.0f / size));

			const float thirdPositionX = (x + 1.0f);
			const float thirdPositionY = 0.0f;
			const float thirdPositionZ = z;
			const float thirdUvX = (((x + halfSize) / size) + (1.0f / size));
			const float thirdUvY = ((z + halfSize) / size);

			const float fourthPositionX = x;
			const float fourthPositionY = 0.0f;
			const float fourthPositionZ = z;
			const float fourthUvX = ((x + halfSize) / size);
			const float fourthUvY = ((z + halfSize) / size);

			highQualityBufferData.push_back(firstPositionX);
			highQualityBufferData.push_back(firstPositionY);
			highQualityBufferData.push_back(firstPositionZ);
			highQualityBufferData.push_back(firstUvX);
			highQualityBufferData.push_back(firstUvY);

			highQualityBufferData.push_back(secondPositionX);
			highQualityBufferData.push_back(secondPositionY);
			highQualityBufferData.push_back(secondPositionZ);
			highQualityBufferData.push_back(secondUvX);
			highQualityBufferData.push_back(secondUvY);

			highQualityBufferData.push_back(thirdPositionX);
			highQualityBufferData.push_back(thirdPositionY);
			highQualityBufferData.push_back(thirdPositionZ);
			highQualityBufferData.push_back(thirdUvX);
			highQualityBufferData.push_back(thirdUvY);

			highQualityBufferData.push_back(thirdPositionX);
			highQualityBufferData.push_back(thirdPositionY);
			highQualityBufferData.push_back(thirdPositionZ);
			highQualityBufferData.push_back(thirdUvX);
			highQualityBufferData.push_back(thirdUvY);

			highQualityBufferData.push_back(fourthPositionX);
			highQualityBufferData.push_back(fourthPositionY);
			highQualityBufferData.push_back(fourthPositionZ);
			highQualityBufferData.push_back(fourthUvX);
			highQualityBufferData.push_back(fourthUvY);

			highQualityBufferData.push_back(firstPositionX);
			highQualityBufferData.push_back(firstPositionY);
			highQualityBufferData.push_back(firstPositionZ);
			highQualityBufferData.push_back(firstUvX);
			highQualityBufferData.push_back(firstUvY);
		}
	}

	const auto lowQualityBufferDataCount = static_cast<int>(sizeof(lowQualityBufferData) / sizeof(float));
	const auto highQualityBufferDataCount = static_cast<int>(highQualityBufferData.size());

	entity->setLowQualityVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, &lowQualityBufferData[0], lowQualityBufferDataCount));
	entity->setHighQualityVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, &highQualityBufferData[0], highQualityBufferDataCount));
}

void WaterManager::update()
{
	auto entity = getSelectedWater();

	if(entity == nullptr)
	{
		return;
	}

	if(!entity->isVisible())
	{
		return;
	}

	entity->setRippleOffset(fvec2(fmodf((entity->getRippleOffset().x + entity->getRippleSpeed().x), 1.0f), fmodf((entity->getRippleOffset().y - entity->getRippleSpeed().y), 1.0f)));

	entity->setWaveOffset(entity->getWaveOffset() + (entity->getWaveSpeed()));
}