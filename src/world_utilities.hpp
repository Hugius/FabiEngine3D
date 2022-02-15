#pragma once

#include "engine_interface.hpp"

class WorldUtilities final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);

	const bool copyTemplateSky(const string& newId, const string& templateId);
	const bool copyTemplateTerrain(const string& newId, const string& templateId);
	const bool copyTemplateWater(const string& newId, const string& templateId);
	const bool copyTemplateModel(const string& newId, const string& templateId);
	const bool copyTemplateQuad3d(const string& newId, const string& templateId);
	const bool copyTemplateText3d(const string& newId, const string& templateId);
	const bool copyTemplateSound3d(const string& newId, const string& templateId);

private:
	shared_ptr<EngineInterface> _fe3d = nullptr;
};