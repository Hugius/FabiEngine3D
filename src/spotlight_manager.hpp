#pragma once

#include "spotlight.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class SpotlightManager final
{
public:
	void update();
	void createSpotlight(const string & spotlightId);
	void deleteSpotlight(const string & spotlightId);
	void deleteSpotlights();

	const unordered_map<string, shared_ptr<Spotlight>> & getSpotlights() const;

	const shared_ptr<Spotlight> getSpotlight(const string & spotlightId) const;

	const int getMaxSpotlightCount() const;

	const bool isSpotlightExisting(const string & spotlightId) const;
	const bool isSpotlightsExisting() const;

private:
	static inline constexpr int MAX_COUNT = 64;

	unordered_map<string, shared_ptr<Spotlight>> _spotlights = {};
};