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
	void copyTemplateCaptor(const string & newId, const string & templateId);
	void copyTemplateSound3d(const string & newId, const string & templateId);
	void copyTemplateSound2d(const string & newId, const string & templateId);
	void deleteCopiedSky(const string & skyId);
	void deleteCopiedTerrain(const string & terrainId);
	void deleteCopiedWater(const string & waterId);
	void deleteCopiedModel(const string & modelId);
	void deleteCopiedQuad3d(const string & quad3dId);
	void deleteCopiedQuad2d(const string & quad2dId);
	void deleteCopiedText3d(const string & text3dId);
	void deleteCopiedText2d(const string & text2dId);
	void deleteCopiedAabb(const string & aabbId);
	void deleteCopiedPointlight(const string & pointlightId);
	void deleteCopiedSpotlight(const string & spotlightId);
	void deleteCopiedCaptor(const string & captorId);
	void deleteCopiedSound3d(const string & sound3dId);
	void deleteCopiedSound2d(const string & sound2dId);

	const string & getTemplateSkyId(const string & skyId) const;
	const string & getTemplateTerrainId(const string & terrainId) const;
	const string & getTemplateWaterId(const string & waterId) const;
	const string & getTemplateModelId(const string & modelId) const;
	const string & getTemplateQuad3dId(const string & quad3dId) const;
	const string & getTemplateQuad2dId(const string & quad2dId) const;
	const string & getTemplateText3dId(const string & text3dId) const;
	const string & getTemplateText2dId(const string & text2dId) const;
	const string & getTemplateAabbId(const string & aabbId) const;
	const string & getTemplatePointlightId(const string & pointlightId) const;
	const string & getTemplateSpotlightId(const string & spotlightId) const;
	const string & getTemplateCaptorId(const string & captorId) const;
	const string & getTemplateSound3dId(const string & sound3dId) const;
	const string & getTemplateSound2dId(const string & sound2dId) const;

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
	unordered_map<string, string> _copiedCaptorIds = {};
	unordered_map<string, string> _copiedSound3dIds = {};
	unordered_map<string, string> _copiedSound2dIds = {};

	shared_ptr<EngineInterface> _fe3d = nullptr;
};