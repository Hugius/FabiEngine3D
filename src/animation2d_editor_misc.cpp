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

	for(const auto& animation : _animations)
	{
		result.push_back(animation->getID());
	}

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
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getRowCount();
}

const unsigned int Animation2dEditor::getBillboardAnimationColumnCount(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getColumnCount();
}

const unsigned int Animation2dEditor::getBillboardAnimationRowIndex(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getRowIndex();
}

const unsigned int Animation2dEditor::getBillboardAnimationColumnIndex(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getColumnIndex();
}

const int Animation2dEditor::getBillboardAnimationPlayCount(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getPlayCount();
}

const unsigned int Animation2dEditor::getBillboardAnimationFramestep(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).getFramestep();
}

const unsigned int Animation2dEditor::getImageAnimationRowCount(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedImageAnimations.at(make_pair(animationID, imageID)).getRowCount();
}

const unsigned int Animation2dEditor::getImageAnimationColumnCount(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedImageAnimations.at(make_pair(animationID, imageID)).getColumnCount();
}

const unsigned int Animation2dEditor::getImageAnimationRowIndex(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedImageAnimations.at(make_pair(animationID, imageID)).getRowIndex();
}

const unsigned int Animation2dEditor::getImageAnimationColumnIndex(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedImageAnimations.at(make_pair(animationID, imageID)).getColumnIndex();
}

const int Animation2dEditor::getImageAnimationPlayCount(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedImageAnimations.at(make_pair(animationID, imageID)).getPlayCount();
}

const unsigned int Animation2dEditor::getImageAnimationFramestep(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		Logger::throwWarning("animation not started!");
	}

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
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedBillboardAnimations.find(make_pair(animationID, billboardID)) != _startedBillboardAnimations.end());
}

const bool Animation2dEditor::isBillboardAnimationPlaying(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		return false;
	}

	return !isBillboardAnimationPaused(animationID, billboardID);
}

const bool Animation2dEditor::isBillboardAnimationPaused(const string& animationID, const string& billboardID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isBillboardAnimationStarted(animationID, billboardID))
	{
		return false;
	}

	return _startedBillboardAnimations.at(make_pair(animationID, billboardID)).isPaused();
}

const bool Animation2dEditor::isImageAnimationStarted(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedImageAnimations.find(make_pair(animationID, imageID)) != _startedImageAnimations.end());
}

const bool Animation2dEditor::isImageAnimationPlaying(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		return false;
	}

	return !isImageAnimationPaused(animationID, imageID);
}

const bool Animation2dEditor::isImageAnimationPaused(const string& animationID, const string& imageID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isImageAnimationStarted(animationID, imageID))
	{
		return false;
	}

	return _startedImageAnimations.at(make_pair(animationID, imageID)).isPaused();
}