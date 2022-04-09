#pragma once

#include "animation2d_manager.hpp"
#include "quad3d_entity_manager.hpp"
#include "quad2d_entity_manager.hpp"
#include "started_animation2d.hpp"

#include <vector>

using std::vector;
using std::pair;

class Animation2dPlayer final
{
public:
	void inject(shared_ptr<Animation2dManager> animation2dManager);
	void inject(shared_ptr<Quad3dEntityManager> quad3dEntityManager);
	void inject(shared_ptr<Quad2dEntityManager> quad2dEntityManager);
	void update();
	void startQuad3dAnimation(const string & animationId, const string & quadId, int playCount);
	void startQuad2dAnimation(const string & animationId, const string & quadId, int playCount);
	void pauseQuad3dAnimation(const string & animationId, const string & quadId);
	void pauseQuad2dAnimation(const string & animationId, const string & quadId);
	void autopauseQuad3dAnimation(const string & animationId, const string & quadId);
	void autopauseQuad2dAnimation(const string & animationId, const string & quadId);
	void resumeQuad3dAnimation(const string & animationId, const string & quadId);
	void resumeQuad2dAnimation(const string & animationId, const string & quadId);
	void stopQuad3dAnimation(const string & animationId, const string & quadId);
	void stopQuad2dAnimation(const string & animationId, const string & quadId);
	void setQuad3dAnimationRowIndex(const string & animationId, const string & quadId, unsigned int value);
	void setQuad2dAnimationRowIndex(const string & animationId, const string & quadId, unsigned int value);
	void setQuad3dAnimationColumnIndex(const string & animationId, const string & quadId, unsigned int value);
	void setQuad2dAnimationColumnIndex(const string & animationId, const string & quadId, unsigned int value);
	void setQuad3dAnimationIntervalMultiplier(const string & animationId, const string & quadId, unsigned int value);
	void setQuad2dAnimationIntervalMultiplier(const string & animationId, const string & quadId, unsigned int value);
	void setQuad3dAnimationIntervalDivider(const string & animationId, const string & quadId, unsigned int value);
	void setQuad2dAnimationIntervalDivider(const string & animationId, const string & quadId, unsigned int value);

	const vector<pair<string, string>> getStartedQuad3dAnimationIds() const;
	const vector<pair<string, string>> getStartedQuad2dAnimationIds() const;

	const unsigned int getQuad3dAnimationRowIndex(const string & animationId, const string & quadId) const;
	const unsigned int getQuad2dAnimationRowIndex(const string & animationId, const string & quadId) const;
	const unsigned int getQuad3dAnimationColumnIndex(const string & animationId, const string & quadId) const;
	const unsigned int getQuad2dAnimationColumnIndex(const string & animationId, const string & quadId) const;
	const unsigned int getQuad3dAnimationIntervalMultiplier(const string & animationId, const string & quadId) const;
	const unsigned int getQuad2dAnimationIntervalMultiplier(const string & animationId, const string & quadId) const;
	const unsigned int getQuad3dAnimationIntervalDivider(const string & animationId, const string & quadId) const;
	const unsigned int getQuad2dAnimationIntervalDivider(const string & animationId, const string & quadId) const;

	const int getQuad3dAnimationPlayCount(const string & animationId, const string & quadId) const;
	const int getQuad2dAnimationPlayCount(const string & animationId, const string & quadId) const;

	const bool isQuad3dAnimationStarted(const string & animationId, const string & quadId) const;
	const bool isQuad2dAnimationStarted(const string & animationId, const string & quadId) const;
	const bool isQuad3dAnimationPaused(const string & animationId, const string & quadId) const;
	const bool isQuad2dAnimationPaused(const string & animationId, const string & quadId) const;
	const bool isQuad3dAnimationAutopaused(const string & animationId, const string & quadId) const;
	const bool isQuad2dAnimationAutopaused(const string & animationId, const string & quadId) const;

private:
	void _updateQuad3dAnimationExecution();
	void _updateQuad2dAnimationExecution();

	static inline const char DELIMITER = '|';

	unordered_map<string, shared_ptr<StartedAnimation2d>> _startedQuad3dAnimations = {};
	unordered_map<string, shared_ptr<StartedAnimation2d>> _startedQuad2dAnimations = {};

	shared_ptr<Animation2dManager> _animation2dManager = nullptr;
	shared_ptr<Quad3dEntityManager> _quad3dEntityManager = nullptr;
	shared_ptr<Quad2dEntityManager> _quad2dEntityManager = nullptr;
};