#pragma once

#include "base_renderer.hpp"
#include "water.hpp"
#include "pointlight.hpp"
#include "spotlight.hpp"

#include <unordered_map>

using std::unordered_map;

class WaterColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & pointlights);
	void processSpotlights(const unordered_map<string, shared_ptr<Spotlight>> & spotlights);
	void render(shared_ptr<Water> water);
};