#pragma once

#include "animation3d_manager.hpp"
#include "model_entity_manager.hpp"
#include "started_animation3d.hpp"

class Animation3dPlayer final
{
public:
	void inject(shared_ptr<Animation3dManager> animation3dManager);
	void inject(shared_ptr<ModelEntityManager> modelEntityManager);
	void update();
	void startModelAnimation(const string & animationId, const string & modelId, int playCount);
	void pauseModelAnimation(const string & animationId, const string & modelId);
	void autopauseModelAnimation(const string & animationId, const string & modelId);
	void resumeModelAnimation(const string & animationId, const string & modelId);
	void stopModelAnimation(const string & animationId, const string & modelId);
	void setModelAnimationSpeedMultiplier(const string & animationId, const string & modelId, float value);
	void setModelAnimationFrameIndex(const string & animationId, const string & modelId, int value);

	const vector<pair<string, string>> getStartedModelAnimationIds() const;

	const float getModelAnimationSpeedMultiplier(const string & animationId, const string & modelId) const;

	const int getModelAnimationFrameIndex(const string & animationId, const string & modelId) const;

	const int getModelAnimationPlayCount(const string & animationId, const string & modelId) const;

	const bool isModelAnimationStarted(const string & animationId, const string & modelId) const;
	const bool isModelAnimationPaused(const string & animationId, const string & modelId) const;
	const bool isModelAnimationAutopaused(const string & animationId, const string & modelId) const;

private:
	void _updateModelAnimationExecution();

	const bool _hasReachedTarget(float total, float target, float speed) const;

	static inline const char DELIMITER = '|';

	unordered_map<string, shared_ptr<StartedAnimation3d>> _startedModelAnimations;

	shared_ptr<Animation3dManager> _animation3dManager = nullptr;
	shared_ptr<ModelEntityManager> _modelEntityManager = nullptr;
};