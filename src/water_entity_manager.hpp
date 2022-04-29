#pragma once

#include "water_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterManager final
{
public:
	void update();
	void createWater(const string & waterId);
	void deleteWater(const string & waterId);
	void deleteWaters();
	void loadWaterVertexBuffer(const string & waterId);
	void selectWater(const string & waterId);

	const unordered_map<string, shared_ptr<WaterEntity>> & getWaters() const;

	const shared_ptr<WaterEntity> getWater(const string & waterId) const;
	const shared_ptr<WaterEntity> getSelectedWater() const;

	const bool isWaterExisting(const string & waterId) const;
	const bool isWatersExisting() const;

private:
	void _loadWaterVertexBuffer(shared_ptr<WaterEntity> entity, float size);

	unordered_map<string, shared_ptr<WaterEntity>> _waters = {};

	string _selectedWaterId = "";
};