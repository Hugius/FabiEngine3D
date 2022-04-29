#pragma once

#include "base_renderer.hpp"
#include "model_entity.hpp"
#include "pointlight_entity.hpp"
#include "spotlight_entity.hpp"
#include "captor_entity.hpp"

#include <unordered_map>

using std::unordered_map;

class ModelEntityColorRenderer final : public BaseRenderer
{
public:
	void bind();
	void unbind();
	void processPointlights(const unordered_map<string, shared_ptr<Pointlight>> & entities);
	void processSpotlights(const unordered_map<string, shared_ptr<Spotlight>> & entities);
	void render(const shared_ptr<Model> entity, const unordered_map<string, shared_ptr<Captor>> & captorEntities);
};