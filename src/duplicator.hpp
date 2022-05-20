#pragma once

#include "engine_interface.hpp"

class Duplicator final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void copyTemplateSky(const string & newId, const string & templateId);
	void copyTemplateTerrain(const string & newId, const string & templateId);
	void copyTemplateWater(const string & newId, const string & templateId);
	void copyTemplateModel(const string & newId, const string & templateId);
	void copyTemplateQuad3d(const string & newId, const string & templateId);
	void copyTemplateQuad2d(const string & newId, const string & templateId);
	void copyTemplateText3d(const string & newId, const string & templateId);
	void copyTemplateText2d(const string & newId, const string & templateId);
	void copyTemplateAabb(const string & newId, const string & templateId);
	void copyTemplatePointlight(const string & newId, const string & templateId);
	void copyTemplateSpotlight(const string & newId, const string & templateId);
	void copyTemplateSound3d(const string & newId, const string & templateId);
	void copyTemplateSound2d(const string & newId, const string & templateId);

	const string & getTemplateSkyId(const string & skyId);
	const string & getTemplateTerrainId(const string & trrainId);
	const string & getTemplateWaterId(const string & waterId);
	const string & getTemplateModelId(const string & modelId);
	const string & getTemplateQuad3dId(const string & quad3dId);
	const string & getTemplateQuad2dId(const string & quad2dId);
	const string & getTemplateText3dId(const string & text3dId);
	const string & getTemplateText2dId(const string & text2dId);
	const string & getTemplateAabbId(const string & aabbId);
	const string & getTemplatePointlightId(const string & pointlightId);
	const string & getTemplateSpotlightId(const string & spotlightId);
	const string & getTemplateSound3dId(const string & sound3dId);
	const string & getTemplateSound2dId(const string & sound2dId);

private:
	unordered_map<string, string> _copiedSkyIds = {};
	unordered_map<string, string> _copiedTerrainIds = {};
	unordered_map<string, string> _copiedWaterIds = {};
	unordered_map<string, string> _copiedModelIds = {};
	unordered_map<string, string> _copiedQuad3dIds = {};
	unordered_map<string, string> _copiedQuad2dIds = {};
	unordered_map<string, string> _copiedText3dIds = {};
	unordered_map<string, string> _copiedText2dIds = {};
	unordered_map<string, string> _copiedAabbIds = {};
	unordered_map<string, string> _copiedPointlightIds = {};
	unordered_map<string, string> _copiedSpotlightIds = {};
	unordered_map<string, string> _copiedSound3dIds = {};
	unordered_map<string, string> _copiedSound2dIds = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;
};