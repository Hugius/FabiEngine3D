#include "animation_editor.hpp"

void AnimationEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool AnimationEditor::isLoaded()
{
	return _isLoaded;
}

void AnimationEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		// Lock toggling if GUI focused or cursor not in 3D viewport
		_fe3d.input_setKeyTogglingLocked(_gui.getGlobalScreen()->isFocused() || !_fe3d.misc_isCursorInsideViewport());

		// Debug rendering
		if (_fe3d.input_getKeyToggled(InputType::KEY_H))
		{
			_fe3d.misc_enableDebugRendering();
		}
		else
		{
			_fe3d.misc_disableDebugRendering();
		}
	}
}

void AnimationEditor::_deleteAnimation(const string& ID)
{
	for (unsigned int i = 0; i < _animations.size(); i++)
	{
		if (ID == _animations[i]->ID)
		{
			_animations.erase(_animations.begin() + i);
		}
	}

	_fe3d.logger_throwError("Cannot delete animation with ID \"" + ID + "\"");
}

bool AnimationEditor::_isAnimationExisting(const string& ID)
{
	for (auto& animation : _animations)
	{
		if (ID == animation->ID)
		{
			return true;
		}
	}

	return false;
}

vector<string> AnimationEditor::_getAnimationIDs()
{
	vector<string> names;

	for (auto& animation : _animations)
	{
		names.push_back(animation->ID);
	}

	return names;
}

shared_ptr<Animation> AnimationEditor::_getAnimation(const string& ID)
{
	for (auto& animation : _animations)
	{
		if (animation->ID == _currentAnimationID)
		{
			return animation;
		}
	}

	_fe3d.logger_throwError("Cannot retrieve animation with ID \"" + ID + "\""); 
}
