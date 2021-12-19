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

const vector<string> Animation2dEditor::getAnimationIDs()
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

const vector<string> Animation2dEditor::getStartedBillboardAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedBillboardAnimations)
	{
		IDs.insert(idPair.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedImageAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedImageAnimations)
	{
		IDs.insert(idPair.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedBillboardAnimationIDs(const string& billboardID) const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedBillboardAnimations)
	{
		if(billboardID == idPair.second)
		{
			IDs.insert(idPair.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedImageAnimationIDs(const string& imageID) const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedImageAnimations)
	{
		if(imageID == idPair.second)
		{
			IDs.insert(idPair.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const unsigned int Animation2dEditor::getBillboardAnimationRowCount(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return row count
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getRowCount();
}

const unsigned int Animation2dEditor::getBillboardAnimationColumnCount(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return column count
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getColumnCount();
}

const unsigned int Animation2dEditor::getBillboardAnimationRowIndex(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return row index
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getRowIndex();
}

const unsigned int Animation2dEditor::getBillboardAnimationColumnIndex(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return column index
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getColumnIndex();
}

const int Animation2dEditor::getBillboardAnimationTimesToPlay(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getTimesToPlay();
}

const unsigned int Animation2dEditor::getBillboardAnimationFramestep(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getFramestep();
}

const unsigned int Animation2dEditor::getImageAnimationRowCount(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).getRowCount();
}

const unsigned int Animation2dEditor::getImageAnimationColumnCount(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).getColumnCount();
}

const unsigned int Animation2dEditor::getImageAnimationRowIndex(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).getRowIndex();
}

const unsigned int Animation2dEditor::getImageAnimationColumnIndex(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).getColumnIndex();
}

const int Animation2dEditor::getImageAnimationTimesToPlay(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).getTimesToPlay();
}

const unsigned int Animation2dEditor::getImageAnimationFramestep(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).getFramestep();
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

const bool Animation2dEditor::isBillboardAnimationStarted(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Return
	return (_startedBillboardAnimations.find(make_pair(animationID, billboardID)) != _startedBillboardAnimations.end());
}

const bool Animation2dEditor::isBillboardAnimationPlaying(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		return false;
	}

	// Return
	return !isBillboardAnimationPaused(animationID, billboardID);
}

const bool Animation2dEditor::isBillboardAnimationPaused(const string& animationID, const string& billboardID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	// Check if animation not started
	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		return false;
	}

	// Return
	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).isPaused();
}

const bool Animation2dEditor::isImageAnimationStarted(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Return
	return (_startedImageAnimations.find(make_pair(animationID, imageID)) != _startedImageAnimations.end());
}

const bool Animation2dEditor::isImageAnimationPlaying(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		return false;
	}

	// Return
	return !isImageAnimationPaused(animationID, imageID);
}

const bool Animation2dEditor::isImageAnimationPaused(const string& animationID, const string& imageID) const
{
	// Check if animation not existing
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	// Check if animation not started
	if(!isImageAnimationStarted(animationID, imageID))
	{
		return false;
	}

	// Return
	return _startedImageAnimations.at(make_pair(animationID, imageID)).isPaused();
}