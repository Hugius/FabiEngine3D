#pragma once

#include "animation2d_manager.hpp"
#include "quad3d_manager.hpp"
#include "quad2d_manager.hpp"
#include "started_animation2d.hpp"

#include <vector>

using std::vector;
using std::pair;

class Animation2dPlayer final
{
public:
	void inject(shared_ptr<Animation2dManager> animation2dManager);
	void inject(shared_ptr<Quad3dManager> quad3dManager);
	void inject(shared_ptr<Quad2dManager> quad2dManager);
	void update();
	void startQuad3dAnimation(const string & animation2dId, const string & quad3dId, int playCount);
	void startQuad2dAnimation(const string & animation2dId, const string & quad2dId, int playCount);
	void pauseQuad3dAnimation(const string & animation2dId, const string & quad3dId);
	void pauseQuad2dAnimation(const string & animation2dId, const string & quad2dId);
	void autopauseQuad3dAnimation(const string & animation2dId, const string & quad3dId);
	void autopauseQuad2dAnimation(const string & animation2dId, const string & quad2dId);
	void resumeQuad3dAnimation(const string & animation2dId, const string & quad3dId);
	void resumeQuad2dAnimation(const string & animation2dId, const string & quad2dId);
	void stopQuad3dAnimation(const string & animation2dId, const string & quad3dId);
	void stopQuad2dAnimation(const string & animation2dId, const string & quad2dId);
	void setQuad3dAnimationRowIndex(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimationRowIndex(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimationColumnIndex(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimationColumnIndex(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimationIntervalMultiplier(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimationIntervalMultiplier(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimationIntervalDivider(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimationIntervalDivider(const string & animation2dId, const string & quad2dId, int value);

	const vector<pair<string, string>> getStartedQuad3dAnimationIds() const;
	const vector<pair<string, string>> getStartedQuad2dAnimationIds() const;

	const int getQuad3dAnimationRowIndex(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimationRowIndex(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimationColumnIndex(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimationColumnIndex(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimationIntervalMultiplier(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimationIntervalMultiplier(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimationIntervalDivider(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimationIntervalDivider(const string & animation2dId, const string & quad2dId) const;

	const int getQuad3dAnimationPlayCount(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimationPlayCount(const string & animation2dId, const string & quad2dId) const;

	const bool isQuad3dAnimationStarted(const string & animation2dId, const string & quad3dId) const;
	const bool isQuad2dAnimationStarted(const string & animation2dId, const string & quad2dId) const;
	const bool isQuad3dAnimationPaused(const string & animation2dId, const string & quad3dId) const;
	const bool isQuad2dAnimationPaused(const string & animation2dId, const string & quad2dId) const;
	const bool isQuad3dAnimationAutopaused(const string & animation2dId, const string & quad3dId) const;
	const bool isQuad2dAnimationAutopaused(const string & animation2dId, const string & quad2dId) const;

private:
	void _updateQuad3dAnimationExecution();
	void _updateQuad2dAnimationExecution();

	static inline const char DELIMITER = '|';

	unordered_map<string, shared_ptr<StartedAnimation2d>> _startedQuad3dAnimations = {};
	unordered_map<string, shared_ptr<StartedAnimation2d>> _startedQuad2dAnimations = {};

	shared_ptr<Animation2dManager> _animation2dManager = nullptr;
	shared_ptr<Quad3dManager> _quad3dManager = nullptr;
	shared_ptr<Quad2dManager> _quad2dManager = nullptr;
};