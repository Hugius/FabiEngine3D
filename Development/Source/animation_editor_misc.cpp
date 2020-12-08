#include "animation_editor.hpp"

void AnimationEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool AnimationEditor::isLoaded()
{
	return _isEditorLoaded;
}

void AnimationEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
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

		// Set current frame's transformation of editor
		if (!_currentAnimationID.empty())
		{
			auto currentAnimation = _getAnimation(_currentAnimationID);

			// Check if animation is not currently playing
			if (!isAnimationPlaying(_currentAnimationID, currentAnimation->previewModelID))
			{
				// Check if animation has a preview model
				if (!currentAnimation->previewModelID.empty())
				{
					auto frame = currentAnimation->frames[_currentFrameIndex];

					// For every model part in this frame
					for (auto& partName : frame.partNames)
					{
						// Check if individual part differs from whole model
						if (frame.targetTransformations[partName] != frame.targetTransformations[""] || partName.empty())
						{
							// Determine type of transformation
							if (currentAnimation->transformationType == TransformationType::TRANSLATION)
							{
								_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation + frame.targetTransformations[partName], partName);
								_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation, partName);
								_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partName);
							}
							else if (currentAnimation->transformationType == TransformationType::ROTATION)
							{
								_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation, partName);
								_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation + frame.targetTransformations[partName], partName);
								_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partName);
							}
							else if (currentAnimation->transformationType == TransformationType::SCALING)
							{
								_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, currentAnimation->initialTranslation, partName);
								_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, currentAnimation->initialRotation, partName);
								_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling + frame.targetTransformations[partName], partName);
							}
						}
					}
				}
			}
		}
	}
}

void AnimationEditor::_deleteAnimation(const string& ID)
{
	for (unsigned int i = 0; i < _animations.size(); i++)
	{
		if (_animations[i]->ID == ID)
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
		if (animation->ID == ID)
		{
			return true;
		}
	}

	return false;
}

bool AnimationEditor::_hasReachedFloat(float first, float second, float speed)
{
	return (first >= second - fabsf(speed)) && (first <= second + fabsf(speed));
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
		if (animation->ID == ID)
		{
			return animation;
		}
	}

	_fe3d.logger_throwError("Cannot retrieve animation with ID \"" + ID + "\""); 
}
