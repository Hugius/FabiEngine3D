#include "mesh_animation_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void MeshAnimationEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool MeshAnimationEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void MeshAnimationEditor::_deleteAnimation(const string& ID)
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

const bool MeshAnimationEditor::_hasReachedFloat(float first, float second, float speed) const
{
	return (first >= (second - fabsf(speed))) && (first <= (second + fabsf(speed)));
}

const bool MeshAnimationEditor::_comparePartIDs(vector<string> first, vector<string> second) const
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

shared_ptr<MeshAnimation> MeshAnimationEditor::_getAnimation(const string& ID) const
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

const vector<string> MeshAnimationEditor::getAllAnimationIDs() const
{
	vector<string> result;

	// Find all IDs
	for(const auto& animation : _animations)
	{
		result.push_back(animation->getID());
	}

	// Sort alphabetically
	sort(result.begin(), result.end());

	return result;
}

const vector<string> MeshAnimationEditor::getStartedAnimationIDs() const
{
	set<string> names;

	for(const auto& [idPair, animation] : _startedAnimations)
	{
		names.insert(idPair.first);
	}

	return vector<string>(names.begin(), names.end());
}

const vector<string> MeshAnimationEditor::getStartedAnimationIDs(const string& modelID) const
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