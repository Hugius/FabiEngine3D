#include "animation3d_editor.hpp"
#include "logger.hpp"

void Animation3dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Animation3dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

void Animation3dEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("Animation3dEditor::_deleteAnimation");
}

const bool Animation3dEditor::_hasReachedFloat(float first, float second, float speed) const
{
	return (first >= (second - fabsf(speed))) && (first <= (second + fabsf(speed)));
}

const bool Animation3dEditor::_comparePartIDs(vector<string> first, vector<string> second) const
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

shared_ptr<Animation3d> Animation3dEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("Animation3dEditor::_getAnimation");
}

const vector<string> Animation3dEditor::getAnimationIDs() const
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

const vector<string> Animation3dEditor::getStartedAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedAnimations)
	{
		IDs.insert(idPair.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation3dEditor::getStartedAnimationIDs(const string& modelID) const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedAnimations)
	{
		if(modelID == idPair.second)
		{
			IDs.insert(idPair.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

Animation3d* Animation3dEditor::getAnimationData(const string& animationID, const string& modelID, string baseErrorMessage)
{
	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(baseErrorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(baseErrorMessage + "animation not started!");
	}
	else
	{
		return &_startedAnimations.at(make_pair(animationID, modelID));
	}

	return nullptr;
}

const bool Animation3dEditor::isAnimationExisting(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

const bool Animation3dEditor::isAnimationStarted(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation does not exist
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _startedAnimations.find(make_pair(animationID, modelID)) != _startedAnimations.end();
	}

	return false;
}

const bool Animation3dEditor::isAnimationPlaying(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_startedAnimations.at(make_pair(animationID, modelID)).isPaused();
	}

	return false;
}

const bool Animation3dEditor::isAnimationPaused(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _startedAnimations.at(make_pair(animationID, modelID)).isPaused();
	}

	return false;
}

const bool Animation3dEditor::isAnimationFading(const string& animationID, const string& modelID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation fading status with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, modelID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return (_startedAnimations.at(make_pair(animationID, modelID)).getFadeFramestep() != -1);
	}

	return false;
}