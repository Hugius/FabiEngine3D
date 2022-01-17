#pragma once

#include "base_editor.hpp"
#include "animation2d.hpp"

class Animation2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void startQuad3dAnimation(const string& animationID, const string& quad3dID, int playCount);
	void pauseQuad3dAnimation(const string& animationID, const string& quad3dID);
	void autopauseQuad3dAnimation(const string& animationID, const string& quad3dID);
	void resumeQuad3dAnimation(const string& animationID, const string& quad3dID);
	void stopQuad3dAnimation(const string& animationID, const string& quad3dID);
	void pauseQuad3dAnimations();
	void autopauseQuad3dAnimations();
	void resumeQuad3dAnimations();
	void stopQuad3dAnimations();
	void setQuad3dAnimationFramestep(const string& animationID, const string& quad3dID, unsigned int value);
	void startQuad2dAnimation(const string& animationID, const string& quadID, int playCount);
	void pauseQuad2dAnimation(const string& animationID, const string& quadID);
	void autopauseQuad2dAnimation(const string& animationID, const string& quadID);
	void resumeQuad2dAnimation(const string& animationID, const string& quadID);
	void stopQuad2dAnimation(const string& animationID, const string& quadID);
	void pauseQuad2dAnimations();
	void autopauseQuad2dAnimations();
	void resumeQuad2dAnimations();
	void stopQuad2dAnimations();
	void setQuad2dAnimationFramestep(const string& animationID, const string& quadID, unsigned int value);

	const vector<string> getAnimationIDs();
	const vector<string> getStartedQuad3dAnimationIDs() const;
	const vector<string> getStartedQuad2dAnimationIDs() const;
	const vector<string> getStartedQuad3dAnimationIDs(const string& quad3dID) const;
	const vector<string> getStartedQuad2dAnimationIDs(const string& quad3dID) const;

	const int getQuad3dAnimationPlayCount(const string& animationID, const string& quad3dID) const;
	const int getQuad2dAnimationPlayCount(const string& animationID, const string& quadID) const;

	const unsigned int getQuad3dAnimationRowCount(const string& animationID, const string& quad3dID) const;
	const unsigned int getQuad3dAnimationColumnCount(const string& animationID, const string& quad3dID) const;
	const unsigned int getQuad3dAnimationRowIndex(const string& animationID, const string& quad3dID) const;
	const unsigned int getQuad3dAnimationColumnIndex(const string& animationID, const string& quad3dID) const;
	const unsigned int getQuad3dAnimationFramestep(const string& animationID, const string& quad3dID) const;
	const unsigned int getQuad2dAnimationRowCount(const string& animationID, const string& quadID) const;
	const unsigned int getQuad2dAnimationColumnCount(const string& animationID, const string& quadID) const;
	const unsigned int getQuad2dAnimationRowIndex(const string& animationID, const string& quadID) const;
	const unsigned int getQuad2dAnimationColumnIndex(const string& animationID, const string& quadID) const;
	const unsigned int getQuad2dAnimationFramestep(const string& animationID, const string& quadID) const;

	const bool isLoaded() const;
	const bool isAnimationExisting(const string& ID) const;
	const bool isQuad3dAnimationStarted(const string& animationID, const string& quad3dID) const;
	const bool isQuad3dAnimationPlaying(const string& animationID, const string& quad3dID) const;
	const bool isQuad3dAnimationPaused(const string& animationID, const string& quad3dID) const;
	const bool isQuad3dAnimationAutopaused(const string& animationID, const string& quad3dID) const;
	const bool isQuad2dAnimationStarted(const string& animationID, const string& quadID) const;
	const bool isQuad2dAnimationPlaying(const string& animationID, const string& quadID) const;
	const bool isQuad2dAnimationPaused(const string& animationID, const string& quadID) const;
	const bool isQuad2dAnimationAutopaused(const string& animationID, const string& quadID) const;
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
	void _updateQuad3dAnimationExecution();
	void _updateQuad2dAnimationExecution();
	void _updateMiscellaneous();
	void _deleteAnimation(const string& ID);

	shared_ptr<Animation2d> _getAnimation(const string& ID) const;

	static inline const string PREVIEW_BILLBOARD_ID = "@@preview_billboard";
	set<pair<string, string>> _quad3dAnimationsToStop;
	set<pair<string, string>> _quad3dAnimationsToStart;
	set<pair<string, string>> _quad2dAnimationsToStop;
	set<pair<string, string>> _quad2dAnimationsToStart;
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

	map<pair<string, string>, Animation2d> _startedQuad3dAnimations;
	map<pair<string, string>, Animation2d> _startedQuad2dAnimations;
	vector<shared_ptr<Animation2d>> _animations;
};