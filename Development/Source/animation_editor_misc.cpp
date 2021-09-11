#include "animation_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void AnimationEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

bool AnimationEditor::isLoaded()
{
	return _isEditorLoaded;
}

void AnimationEditor::_deleteAnimation(const string& ID)
{
	for (size_t i = 0; i < _animations.size(); i++)
	{
		if (_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("AnimationEditor::_deleteAnimation");
}

bool AnimationEditor::_hasReachedFloat(float first, float second, float speed)
{
	return (first >= second - fabsf(speed)) && (first <= second + fabsf(speed));
}

bool AnimationEditor::_comparePartIDs(vector<string> first, vector<string> second)
{
	// Check size
	if (first.size() != second.size())
	{
		return false;
	}

	// Check content
	for (size_t i = 0; i < first.size(); i++)
	{
		if (first[i] != second[i])
		{
			return false;
		}
	}

	// Vectors contents are the same
	return true;
}

shared_ptr<Animation> AnimationEditor::_getAnimation(const string& ID)
{
	for (const auto& animation : _animations)
	{
		if (animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("AnimationEditor::_getAnimation");
}

const vector<string> AnimationEditor::getAllAnimationIDs()
{
	vector<string> IDs;

	// Find all IDs
	for (const auto& animation : _animations)
	{
		IDs.push_back(animation->getID());
	}

	// Sort alphabetically
	sort(IDs.begin(), IDs.end());

	return IDs;
}

const vector<string> AnimationEditor::getStartedAnimationIDs()
{
	set<string> names;

	for (const auto& [idPair, animation] : _startedAnimations)
	{
		names.insert(idPair.first);
	}

	return vector<string>(names.begin(), names.end());
}

const vector<string> AnimationEditor::getStartedAnimationIDs(const string& modelID)
{
	set<string> names;

	for (const auto& [idPair, animation] : _startedAnimations)
	{
		if (modelID == idPair.second)
		{
			names.insert(idPair.first);
		}
	}

	return vector<string>(names.begin(), names.end());
}