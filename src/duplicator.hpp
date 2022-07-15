#pragma once

#include "engine_interface.hpp"

class Duplicator final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void copyEditorSky(const string & newId, const string & editorId);
	void copyEditorTerrain(const string & newId, const string & editorId);
	void copyEditorWater(const string & newId, const string & editorId);
	void copyEditorModel(const string & newId, const string & editorId);
	void copyEditorQuad3d(const string & newId, const string & editorId);
	void copyEditorQuad2d(const string & newId, const string & editorId);
	void copyEditorText3d(const string & newId, const string & editorId);
	void copyEditorText2d(const string & newId, const string & editorId);
	void copyEditorAabb(const string & newId, const string & editorId);
	void copyEditorPointlight(const string & newId, const string & editorId);
	void copyEditorSpotlight(const string & newId, const string & editorId);
	void copyEditorCaptor(const string & newId, const string & editorId);
	void copyEditorSound3d(const string & newId, const string & editorId);
	void copyEditorSound2d(const string & newId, const string & editorId);
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

	const string & getEditorSkyId(const string & skyId) const;
	const string & getEditorTerrainId(const string & terrainId) const;
	const string & getEditorWaterId(const string & waterId) const;
	const string & getEditorModelId(const string & modelId) const;
	const string & getEditorQuad3dId(const string & quad3dId) const;
	const string & getEditorQuad2dId(const string & quad2dId) const;
	const string & getEditorText3dId(const string & text3dId) const;
	const string & getEditorText2dId(const string & text2dId) const;
	const string & getEditorAabbId(const string & aabbId) const;
	const string & getEditorPointlightId(const string & pointlightId) const;
	const string & getEditorSpotlightId(const string & spotlightId) const;
	const string & getEditorCaptorId(const string & captorId) const;
	const string & getEditorSound3dId(const string & sound3dId) const;
	const string & getEditorSound2dId(const string & sound2dId) const;

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