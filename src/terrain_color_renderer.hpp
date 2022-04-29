#pragma once

#include "base_renderer.hpp"
#include "terrain.hpp"
#include "pointlight.hpp"
#include "spotlight.hpp"

#include <unordered_map>

using std::unordered_map;

class TerrainColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & entities);
	void processSpotlights(const unordered_map<string, shared_ptr<Spotlight>> & entities);
	void render(const shared_ptr<Terrain> entity);
};