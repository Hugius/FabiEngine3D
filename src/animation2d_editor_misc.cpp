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

const vector<string> Animation2dEditor::getStartedQuadAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedQuadAnimations)
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

const vector<string> Animation2dEditor::getStartedQuadAnimationIDs(const string& quadID) const
{
	set<string> IDs;

	for(const auto& [idPair, animation] : _startedQuadAnimations)
	{
		if(quadID == idPair.second)
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

const unsigned int Animation2dEditor::getQuadAnimationRowCount(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).getRowCount();
}

const unsigned int Animation2dEditor::getQuadAnimationColumnCount(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).getColumnCount();
}

const unsigned int Animation2dEditor::getQuadAnimationRowIndex(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).getRowIndex();
}

const unsigned int Animation2dEditor::getQuadAnimationColumnIndex(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).getColumnIndex();
}

const int Animation2dEditor::getQuadAnimationPlayCount(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).getPlayCount();
}

const unsigned int Animation2dEditor::getQuadAnimationFramestep(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).getFramestep();
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

const bool Animation2dEditor::isQuadAnimationStarted(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedQuadAnimations.find(make_pair(animationID, quadID)) != _startedQuadAnimations.end());
}

const bool Animation2dEditor::isQuadAnimationPlaying(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		return false;
	}

	return !isQuadAnimationPaused(animationID, quadID);
}

const bool Animation2dEditor::isQuadAnimationPaused(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isQuadAnimationStarted(animationID, quadID))
	{
		return false;
	}

	return _startedQuadAnimations.at(make_pair(animationID, quadID)).isPaused();
}