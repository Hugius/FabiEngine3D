#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::inject(shared_ptr<ModelEditor> modelEditor)
{
	_modelEditor = modelEditor;
}

void Animation3dEditor::_deleteAnimation(const string& id)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getId() == id)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	abort();
}

const bool Animation3dEditor::_hasReachedFloat(float first, float second, float speed) const
{
	return (first >= (second - fabsf(speed))) && (first <= (second + fabsf(speed)));
}

const bool Animation3dEditor::_comparePartIds(vector<string> first, vector<string> second) const
{
	if(first.size() != second.size())
	{
		return false;
	}

	for(size_t i = 0; i < first.size(); i++)
	{
		if(first[i] != second[i])
		{
			return false;
		}
	}

	return true;
}

shared_ptr<Animation3d> Animation3dEditor::_getAnimation(const string& id) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getId() == id)
		{
			return animation;
		}
	}

	abort();
}

const vector<string> Animation3dEditor::getAnimationIds() const
{
	vector<string> result;

	for(const auto& animation : _animations)
	{
		result.push_back(animation->getId());
	}

	sort(result.begin(), result.end());

	return result;
}

const vector<string> Animation3dEditor::getStartedModelAnimationIds() const
{
	set<string> Ids;

	for(const auto& [key, animation] : _startedModelAnimations)
	{
		Ids.insert(key.first);
	}

	return vector<string>(Ids.begin(), Ids.end());
}

const vector<string> Animation3dEditor::getStartedModelAnimationIds(const string& modelId) const
{
	set<string> Ids;

	for(const auto& [key, animation] : _startedModelAnimations)
	{
		if(modelId == key.second)
		{
			Ids.insert(key.first);
		}
	}

	return vector<string>(Ids.begin(), Ids.end());
}

const float Animation3dEditor::getModelAnimationSpeed(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationId, modelId))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationId, modelId)).getSpeed();
}

const int Animation3dEditor::getModelAnimationPlayCount(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationId, modelId))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationId, modelId)).getPlayCount();
}

const unsigned int Animation3dEditor::getModelAnimationFrameIndex(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationId, modelId))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationId, modelId)).getFrameIndex();
}

const bool Animation3dEditor::isAnimationExisting(const string& id) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getId() == id)
		{
			return true;
		}
	}

	return false;
}

const bool Animation3dEditor::isModelAnimationStarted(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedModelAnimations.find(make_pair(animationId, modelId)) != _startedModelAnimations.end());
}

const bool Animation3dEditor::isModelAnimationPlaying(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationId, modelId))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return !isModelAnimationPaused(animationId, modelId);
}

const bool Animation3dEditor::isModelAnimationAutopaused(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationId, modelId))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationId, modelId)).isAutopaused();
}

const bool Animation3dEditor::isModelAnimationPaused(const string& animationId, const string& modelId) const
{
	if(!isAnimationExisting(animationId))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isModelAnimationStarted(animationId, modelId))
	{
		Logger::throwWarning("animation not started!");
		return false;
	}

	return _startedModelAnimations.at(make_pair(animationId, modelId)).isPaused();
}