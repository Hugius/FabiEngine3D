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

const vector<string> Animation2dEditor::getStartedQuad3dAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [key, animation] : _startedQuad3dAnimations)
	{
		IDs.insert(key.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedQuad2dAnimationIDs() const
{
	set<string> IDs;

	for(const auto& [key, animation] : _startedQuad2dAnimations)
	{
		IDs.insert(key.first);
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedQuad3dAnimationIDs(const string& quad3dID) const
{
	set<string> IDs;

	for(const auto& [key, animation] : _startedQuad3dAnimations)
	{
		if(quad3dID == key.second)
		{
			IDs.insert(key.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const vector<string> Animation2dEditor::getStartedQuad2dAnimationIDs(const string& quadID) const
{
	set<string> IDs;

	for(const auto& [key, animation] : _startedQuad2dAnimations)
	{
		if(quadID == key.second)
		{
			IDs.insert(key.first);
		}
	}

	return vector<string>(IDs.begin(), IDs.end());
}

const unsigned int Animation2dEditor::getQuad3dAnimationRowCount(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).getRowCount();
}

const unsigned int Animation2dEditor::getQuad3dAnimationColumnCount(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).getColumnCount();
}

const unsigned int Animation2dEditor::getQuad3dAnimationRowIndex(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).getRowIndex();
}

const unsigned int Animation2dEditor::getQuad3dAnimationColumnIndex(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).getColumnIndex();
}

const int Animation2dEditor::getQuad3dAnimationPlayCount(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).getPlayCount();
}

const unsigned int Animation2dEditor::getQuad3dAnimationFramestep(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).getFramestep();
}

const unsigned int Animation2dEditor::getQuad2dAnimationRowCount(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).getRowCount();
}

const unsigned int Animation2dEditor::getQuad2dAnimationColumnCount(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).getColumnCount();
}

const unsigned int Animation2dEditor::getQuad2dAnimationRowIndex(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).getRowIndex();
}

const unsigned int Animation2dEditor::getQuad2dAnimationColumnIndex(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).getColumnIndex();
}

const int Animation2dEditor::getQuad2dAnimationPlayCount(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).getPlayCount();
}

const unsigned int Animation2dEditor::getQuad2dAnimationFramestep(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		Logger::throwWarning("animation not started!");
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).getFramestep();
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

const bool Animation2dEditor::isQuad3dAnimationStarted(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedQuad3dAnimations.find(make_pair(animationID, quad3dID)) != _startedQuad3dAnimations.end());
}

const bool Animation2dEditor::isQuad3dAnimationPlaying(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		return false;
	}

	return !isQuad3dAnimationPaused(animationID, quad3dID);
}

const bool Animation2dEditor::isQuad3dAnimationPaused(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		return false;
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).isPaused();
}

const bool Animation2dEditor::isQuad3dAnimationAutopaused(const string& animationID, const string& quad3dID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isQuad3dAnimationStarted(animationID, quad3dID))
	{
		return false;
	}

	return _startedQuad3dAnimations.at(make_pair(animationID, quad3dID)).isAutopaused();
}

const bool Animation2dEditor::isQuad2dAnimationStarted(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	return (_startedQuad2dAnimations.find(make_pair(animationID, quadID)) != _startedQuad2dAnimations.end());
}

const bool Animation2dEditor::isQuad2dAnimationPlaying(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		return false;
	}

	return !isQuad2dAnimationPaused(animationID, quadID);
}

const bool Animation2dEditor::isQuad2dAnimationPaused(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		return false;
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).isPaused();
}

const bool Animation2dEditor::isQuad2dAnimationAutopaused(const string& animationID, const string& quadID) const
{
	if(!isAnimationExisting(animationID))
	{
		Logger::throwWarning("animation not existing!");
		return false;
	}

	if(!isQuad2dAnimationStarted(animationID, quadID))
	{
		return false;
	}

	return _startedQuad2dAnimations.at(make_pair(animationID, quadID)).isAutopaused();
}