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
	void startQuad3dAnimation2d(const string & animation2dId, const string & quad3dId, int playCount);
	void startQuad2dAnimation2d(const string & animation2dId, const string & quad2dId, int playCount);
	void pauseQuad3dAnimation2d(const string & animation2dId, const string & quad3dId);
	void pauseQuad2dAnimation2d(const string & animation2dId, const string & quad2dId);
	void autopauseQuad3dAnimation2d(const string & animation2dId, const string & quad3dId);
	void autopauseQuad2dAnimation2d(const string & animation2dId, const string & quad2dId);
	void resumeQuad3dAnimation2d(const string & animation2dId, const string & quad3dId);
	void resumeQuad2dAnimation2d(const string & animation2dId, const string & quad2dId);
	void stopQuad3dAnimation2d(const string & animation2dId, const string & quad3dId);
	void stopQuad2dAnimation2d(const string & animation2dId, const string & quad2dId);
	void setQuad3dAnimation2dRowIndex(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimation2dRowIndex(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimation2dColumnIndex(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimation2dColumnIndex(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimation2dIntervalDivider(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimation2dIntervalDivider(const string & animation2dId, const string & quad2dId, int value);
	void setQuad3dAnimation2dUpdateCount(const string & animation2dId, const string & quad3dId, int value);
	void setQuad2dAnimation2dUpdateCount(const string & animation2dId, const string & quad2dId, int value);

	const vector<pair<string, string>> getStartedQuad3dAnimation2dIds() const;
	const vector<pair<string, string>> getStartedQuad2dAnimation2dIds() const;

	const int getQuad3dAnimation2dRowIndex(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimation2dRowIndex(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimation2dColumnIndex(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimation2dColumnIndex(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimation2dIntervalMultiplier(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimation2dIntervalDivider(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimation2dIntervalDivider(const string & animation2dId, const string & quad2dId) const;
	const int getQuad3dAnimation2dUpdateCount(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimation2dUpdateCount(const string & animation2dId, const string & quad2dId) const;

	const int getQuad3dAnimation2dPlayCount(const string & animation2dId, const string & quad3dId) const;
	const int getQuad2dAnimation2dPlayCount(const string & animation2dId, const string & quad2dId) const;

	const bool isQuad3dAnimation2dStarted(const string & animation2dId, const string & quad3dId) const;
	const bool isQuad2dAnimation2dStarted(const string & animation2dId, const string & quad2dId) const;
	const bool isQuad3dAnimation2dPaused(const string & animation2dId, const string & quad3dId) const;
	const bool isQuad2dAnimation2dPaused(const string & animation2dId, const string & quad2dId) const;
	const bool isQuad3dAnimation2dAutopaused(const string & animation2dId, const string & quad3dId) const;
	const bool isQuad2dAnimation2dAutopaused(const string & animation2dId, const string & quad2dId) const;

private:
	void _updateQuad3dAnimation2dExecution();
	void _updateQuad2dAnimation2dExecution();

	static inline const char DELIMITER = '|';

	unordered_map<string, shared_ptr<StartedAnimation2d>> _startedQuad3dAnimation2ds = {};
	unordered_map<string, shared_ptr<StartedAnimation2d>> _startedQuad2dAnimation2ds = {};

	shared_ptr<Animation2dManager> _animation2dManager = nullptr;
	shared_ptr<Quad3dManager> _quad3dManager = nullptr;
	shared_ptr<Quad2dManager> _quad2dManager = nullptr;
};