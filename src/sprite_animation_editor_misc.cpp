#include "sprite_animation_editor.hpp"
#include "logger.hpp"

void SpriteAnimationEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}

const bool SpriteAnimationEditor::isLoaded() const
{
	return _isEditorLoaded;
}

const vector<string> SpriteAnimationEditor::getAllAnimationIDs()
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

void SpriteAnimationEditor::_deleteAnimation(const string& ID)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getID() == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	Logger::throwError("SpriteAnimationEditor::_deleteAnimation");
}

shared_ptr<SpriteAnimation> SpriteAnimationEditor::_getAnimation(const string& ID) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getID() == ID)
		{
			return animation;
		}
	}

	Logger::throwError("SpriteAnimationEditor::_getAnimation");
}