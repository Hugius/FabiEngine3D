#pragma once

#include "pointlight_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class PointlightManager final
{
public:
	void update();
	void createPointlight(const string & pointlightId);
	void deletePointlight(const string & pointlightId);
	void deletePointlights();

	const unordered_map<string, shared_ptr<Pointlight>> & getPointlights() const;

	const shared_ptr<Pointlight> getPointlight(const string & pointlightId) const;

	const int getMaxPointlightCount() const;

	const bool isPointlightExisting(const string & pointlightId) const;
	const bool isPointlightsExisting() const;

private:
	static inline constexpr int MAX_POINTLIGHT_COUNT = 64;

	unordered_map<string, shared_ptr<Pointlight>> _pointlights = {};
};