#include "animation2d_editor.hpp"
#include "logger.hpp"

void Animation2dEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool Animation2dEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string> Animation2dEditor::getAllAnimationIDs()
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

void Animation2dEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("Animation2dEditor::_deleteAnimation");
}

shared_ptr<Animation2d> Animation2dEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("Animation2dEditor::_getAnimation");
}

const bool Animation2dEditor::isAnimationExisting(const string& ID) const
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

const bool Animation2dEditor::isAnimationStarted(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation started status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation does not exist
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else
	{
		return _startedAnimations.find(make_pair(animationID, billboardID)) != _startedAnimations.end();
	}

	return false;
}

const bool Animation2dEditor::isAnimationPlaying(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation playing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return !_startedAnimations.at(make_pair(animationID, billboardID)).isPaused();
	}

	return false;
}

const bool Animation2dEditor::isAnimationPaused(const string& animationID, const string& billboardID) const
{
	// Temporary values
	string errorMessage = "Tried to retrieve animation pausing status with ID \"" + animationID + "\" on billboard with ID \"" + billboardID + "\": ";

	// Check if animation is able to be retrieved
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning(errorMessage + "animation not existing!");
	}
	else if(!isAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning(errorMessage + "animation not started!");
	}
	else
	{
		return _startedAnimations.at(make_pair(animationID, billboardID)).isPaused();
	}

	return false;
}