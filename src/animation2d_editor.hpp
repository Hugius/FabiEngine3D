#pragma once

#include "base_editor.hpp"
#include "animation2d.hpp"

class Animation2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void setCurrentProjectId(const string& projectId);
	void load();
	void unload();
	void update();
	void startQuad3dAnimation(const string& animationId, const string& quadId, int playCount);
	void pauseQuad3dAnimation(const string& animationId, const string& quadId);
	void autopauseQuad3dAnimation(const string& animationId, const string& quadId);
	void resumeQuad3dAnimation(const string& animationId, const string& quadId);
	void stopQuad3dAnimation(const string& animationId, const string& quadId);
	void pauseQuad3dAnimations();
	void autopauseQuad3dAnimations();
	void resumeQuad3dAnimations();
	void stopQuad3dAnimations();
	void setQuad3dAnimationInterval(const string& animationId, const string& quadId, unsigned int value);
	void startQuad2dAnimation(const string& animationId, const string& quadId, int playCount);
	void pauseQuad2dAnimation(const string& animationId, const string& quadId);
	void autopauseQuad2dAnimation(const string& animationId, const string& quadId);
	void resumeQuad2dAnimation(const string& animationId, const string& quadId);
	void stopQuad2dAnimation(const string& animationId, const string& quadId);
	void pauseQuad2dAnimations();
	void autopauseQuad2dAnimations();
	void resumeQuad2dAnimations();
	void stopQuad2dAnimations();
	void setQuad2dAnimationInterval(const string& animationId, const string& quadId, unsigned int value);

	const vector<string> getAnimationIds();
	const vector<string> getStartedQuad3dAnimationIds() const;
	const vector<string> getStartedQuad2dAnimationIds() const;
	const vector<string> getStartedQuad3dAnimationIds(const string& quadId) const;
	const vector<string> getStartedQuad2dAnimationIds(const string& quadId) const;

	const int getQuad3dAnimationPlayCount(const string& animationId, const string& quadId) const;
	const int getQuad2dAnimationPlayCount(const string& animationId, const string& quadId) const;

	const unsigned int getQuad3dAnimationRowCount(const string& animationId, const string& quadId) const;
	const unsigned int getQuad3dAnimationColumnCount(const string& animationId, const string& quadId) const;
	const unsigned int getQuad3dAnimationRowIndex(const string& animationId, const string& quadId) const;
	const unsigned int getQuad3dAnimationColumnIndex(const string& animationId, const string& quadId) const;
	const unsigned int getQuad3dAnimationInterval(const string& animationId, const string& quadId) const;
	const unsigned int getQuad2dAnimationRowCount(const string& animationId, const string& quadId) const;
	const unsigned int getQuad2dAnimationColumnCount(const string& animationId, const string& quadId) const;
	const unsigned int getQuad2dAnimationRowIndex(const string& animationId, const string& quadId) const;
	const unsigned int getQuad2dAnimationColumnIndex(const string& animationId, const string& quadId) const;
	const unsigned int getQuad2dAnimationInterval(const string& animationId, const string& quadId) const;

	const bool isLoaded() const;
	const bool isAnimationExisting(const string& id) const;
	const bool isQuad3dAnimationStarted(const string& animationId, const string& quadId) const;
	const bool isQuad3dAnimationPlaying(const string& animationId, const string& quadId) const;
	const bool isQuad3dAnimationPaused(const string& animationId, const string& quadId) const;
	const bool isQuad3dAnimationAutopaused(const string& animationId, const string& quadId) const;
	const bool isQuad2dAnimationStarted(const string& animationId, const string& quadId) const;
	const bool isQuad2dAnimationPlaying(const string& animationId, const string& quadId) const;
	const bool isQuad2dAnimationPaused(const string& animationId, const string& quadId) const;
	const bool isQuad2dAnimationAutopaused(const string& animationId, const string& quadId) const;
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
	void _deleteAnimation(const string& id);

	shared_ptr<Animation2d> _getAnimation(const string& id) const;

	static inline const string PREVIEW_QUAD_ID = "@@preview_quad3d";
	set<pair<string, string>> _quad3dAnimationsToStop;
	set<pair<string, string>> _quad3dAnimationsToStart;
	set<pair<string, string>> _quad2dAnimationsToStop;
	set<pair<string, string>> _quad2dAnimationsToStart;
	string _hoveredAnimationId = "";
	string _currentAnimationId = "";

	static inline const fvec3 PREVIEW_QUAD_POSITION = fvec3(0.0f, 0.0f, -0.75f);

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;

	bool _isCreatingAnimation = false;
	bool _isChoosingAnimation = false;
	bool _isDeletingAnimation = false;

	map<pair<string, string>, Animation2d> _startedQuad3dAnimations;
	map<pair<string, string>, Animation2d> _startedQuad2dAnimations;
	vector<shared_ptr<Animation2d>> _animations;
};