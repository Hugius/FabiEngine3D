#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"
#include "animation2d.hpp"

class Animation2dEditor final
{
public:
	Animation2dEditor(EngineInterface& fe3d, GuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startBillboardAnimation(const string& animationID, const string& billboardID, int playCount);
	void pauseBillboardAnimation(const string& animationID, const string& billboardID);
	void resumeBillboardAnimation(const string& animationID, const string& billboardID);
	void stopBillboardAnimation(const string& animationID, const string& billboardID);
	void pauseBillboardAnimations();
	void resumeBillboardAnimations();
	void stopBillboardAnimations();
	void setBillboardAnimationFramestep(const string& animationID, const string& billboardID, unsigned int value);
	void startQuadAnimation(const string& animationID, const string& quadID, int playCount);
	void pauseQuadAnimation(const string& animationID, const string& quadID);
	void resumeQuadAnimation(const string& animationID, const string& quadID);
	void stopQuadAnimation(const string& animationID, const string& quadID);
	void pauseQuadAnimations();
	void resumeQuadAnimations();
	void stopQuadAnimations();
	void setQuadAnimationFramestep(const string& animationID, const string& quadID, unsigned int value);

	const vector<string> getAnimationIDs();
	const vector<string> getStartedBillboardAnimationIDs() const;
	const vector<string> getStartedQuadAnimationIDs() const;
	const vector<string> getStartedBillboardAnimationIDs(const string& billboardID) const;
	const vector<string> getStartedQuadAnimationIDs(const string& billboardID) const;

	const int getBillboardAnimationPlayCount(const string& animationID, const string& billboardID) const;
	const int getQuadAnimationPlayCount(const string& animationID, const string& quadID) const;

	const unsigned int getBillboardAnimationRowCount(const string& animationID, const string& billboardID) const;
	const unsigned int getBillboardAnimationColumnCount(const string& animationID, const string& billboardID) const;
	const unsigned int getBillboardAnimationRowIndex(const string& animationID, const string& billboardID) const;
	const unsigned int getBillboardAnimationColumnIndex(const string& animationID, const string& billboardID) const;
	const unsigned int getBillboardAnimationFramestep(const string& animationID, const string& billboardID) const;
	const unsigned int getQuadAnimationRowCount(const string& animationID, const string& quadID) const;
	const unsigned int getQuadAnimationColumnCount(const string& animationID, const string& quadID) const;
	const unsigned int getQuadAnimationRowIndex(const string& animationID, const string& quadID) const;
	const unsigned int getQuadAnimationColumnIndex(const string& animationID, const string& quadID) const;
	const unsigned int getQuadAnimationFramestep(const string& animationID, const string& quadID) const;

	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isBillboardAnimationStarted(const string& animationID, const string& billboardID) const;
	const bool isBillboardAnimationPlaying(const string& animationID, const string& billboardID) const;
	const bool isBillboardAnimationPaused(const string& animationID, const string& billboardID) const;
	const bool isQuadAnimationStarted(const string& animationID, const string& quadID) const;
	const bool isQuadAnimationPlaying(const string& animationID, const string& quadID) const;
	const bool isQuadAnimationPaused(const string& animationID, const string& quadID) const;
	const bool loadFromFile(bool mustCheckPreviewTexture);
	const bool saveToFile() const;

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateAnimationCreating();
	void _updateAnimationChoosing();
	void _updateAnimationDeleting();
	void _updateBillboardAnimationExecution();
	void _updateQuadAnimationExecution();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);

	shared_ptr<Animation2d> _getAnimation(const string& ID) const;

	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_billboard";
	set<pair<string, string>> _billboardAnimationsToStop;
	set<pair<string, string>> _billboardAnimationsToStart;
	set<pair<string, string>> _quadAnimationsToStop;
	set<pair<string, string>> _quadAnimationsToStart;
	string _hoveredAnimationID = "";
	string _currentAnimationID = "";
	string _currentProjectID = "";

	static inline const fvec3 PREVIEW_BILLBOARD_POSITION = fvec3(0.0f, 0.0f, -0.75f);

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;
	bool _isEditorLoaded = false;

	map<pair<string, string>, Animation2d> _startedBillboardAnimations;
	map<pair<string, string>, Animation2d> _startedQuadAnimations;
	vector<shared_ptr<Animation2d>> _animations;
	EngineInterface& _fe3d;
	GuiManager& _gui;
};