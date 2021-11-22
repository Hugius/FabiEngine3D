#include "animation_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void AnimationEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool AnimationEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void AnimationEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("AnimationEditor::_deleteAnimation");
}

const bool AnimationEditor::_hasReachedFloat(float first, float second, float speed) const
{
	return (first >= (second - fabsf(speed))) && (first <= (second + fabsf(speed)));
}

const bool AnimationEditor::_comparePartIDs(vector<string> first, vector<string> second) const
{
	// Check size
	if(first.size() != second.size())
	{
		return false;
	}

	// Check content
	for(size_t i = 0; i < first.size(); i++)
	{
		if(first[i] != second[i])
		{
			return false;
		}
	}

	// Contents are the same
	return true;
}

shared_ptr<Animation> AnimationEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("AnimationEditor::_getAnimation");
}

const vector<string> AnimationEditor::getAllAnimationIDs() const
{
	vector<string> IDs;

	// Find all IDs
	for(const auto& animation : _animations)
	{
		IDs.push_back(animation->getID());
	}

	// Sort alphabetically
	sort(IDs.begin(), IDs.end());

	return IDs;
}

const vector<string> AnimationEditor::getStartedAnimationIDs() const
{
	set<string> names;

	for(const auto& [idPair, animation] : _startedAnimations)
	{
		names.insert(idPair.first);
	}

	return vector<string>(names.begin(), names.end());
}

const vector<string> AnimationEditor::getStartedAnimationIDs(const string& modelID) const
{
	set<string> names;

	for(const auto& [idPair, animation] : _startedAnimations)
	{
		if(modelID == idPair.second)
		{
			names.insert(idPair.first);
		}
	}

	return vector<string>(names.begin(), names.end());
}