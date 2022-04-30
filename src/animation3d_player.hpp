#pragma once

#include "animation3d_manager.hpp"
#include "model_manager.hpp"
#include "started_animation3d.hpp"

class Animation3dPlayer final
{
public:
	void inject(shared_ptr<Animation3dManager> animation3dManager);
	void inject(shared_ptr<ModelManager> modelManager);
	void update();
	void startModelAnimation3d(const string & animation3dId, const string & modelId, int playCount);
	void pauseModelAnimation3d(const string & animation3dId, const string & modelId);
	void autopauseModelAnimation3d(const string & animation3dId, const string & modelId);
	void resumeModelAnimation3d(const string & animation3dId, const string & modelId);
	void stopModelAnimation3d(const string & animation3dId, const string & modelId);
	void setModelAnimation3dSpeedMultiplier(const string & animation3dId, const string & modelId, float value);
	void setModelAnimation3dFrameIndex(const string & animation3dId, const string & modelId, int value);

	const vector<pair<string, string>> getStartedModelAnimation3dIds() const;

	const float getModelAnimation3dSpeedMultiplier(const string & animation3dId, const string & modelId) const;

	const int getModelAnimation3dFrameIndex(const string & animation3dId, const string & modelId) const;

	const int getModelAnimation3dPlayCount(const string & animation3dId, const string & modelId) const;

	const bool isModelAnimation3dStarted(const string & animation3dId, const string & modelId) const;
	const bool isModelAnimation3dPaused(const string & animation3dId, const string & modelId) const;
	const bool isModelAnimation3dAutopaused(const string & animation3dId, const string & modelId) const;

private:
	void _updateModelAnimation3dExecution();

	const bool _hasReachedTarget(float total, float target, float speed) const;

	static inline const char DELIMITER = '|';

	unordered_map<string, shared_ptr<StartedAnimation3d>> _startedModelAnimation3ds;

	shared_ptr<Animation3dManager> _animation3dManager = nullptr;
	shared_ptr<ModelManager> _modelManager = nullptr;
};