#pragma once

#include "water.hpp"

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

	const unordered_map<string, shared_ptr<Water>> & getWaters() const;

	const shared_ptr<Water> getWater(const string & waterId) const;
	const shared_ptr<Water> getSelectedWater() const;

	const bool isWaterExisting(const string & waterId) const;
	const bool isWatersExisting() const;

private:
	void _loadWaterVertexBuffer(shared_ptr<Water> entity, float size);

	unordered_map<string, shared_ptr<Water>> _waters = {};

	string _selectedWaterId = "";
};