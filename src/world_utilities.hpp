#pragma once

#include "engine_interface.hpp"

class WorldUtilities final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void copyTemplateSky(const string& newId, const string& templateId);
	void copyTemplateTerrain(const string& newId, const string& templateId);
	void copyTemplateWater(const string& newId, const string& templateId);
	void copyTemplateModel(const string& newId, const string& templateId);
	void copyTemplateQuad3d(const string& newId, const string& templateId);
	void copyTemplateText3d(const string& newId, const string& templateId);
	void copyTemplateSound3d(const string& newId, const string& templateId);

private:
	shared_ptr<EngineInterface> _fe3d = nullptr;
};