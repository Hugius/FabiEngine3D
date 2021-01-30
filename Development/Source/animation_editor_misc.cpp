#include "animation_editor.hpp"

void AnimationEditor::setCurrentProjectID(const string& projectName)
{
	_currentProjectID = projectName;
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

		// Wireframed model rendering
		if (!_currentAnimationID.empty())
		{
			string modelID = _getAnimation(_currentAnimationID)->previewModelID;

			if (!modelID.empty() && _fe3d.gameEntity_isExisting(modelID))
			{
				if (_fe3d.input_getKeyToggled(InputType::KEY_F))
				{
					_fe3d.gameEntity_setWireframed(modelID, true);
				}
				else
				{
					_fe3d.gameEntity_setWireframed(modelID, false);
				}
			}
		}

		// Check if animation loaded in editor
		if (!_currentAnimationID.empty())
		{
			// Retrieve current animation
			auto currentAnimation = _getAnimation(_currentAnimationID);

			// Check if animation is not currently playing
			if (!isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID))
			{
				// Check if animation has a preview model
				if (!currentAnimation->previewModelID.empty())
				{
					// Default transformation
					for (auto partName : currentAnimation->partNames)
					{
						_fe3d.gameEntity_setPosition(currentAnimation->previewModelID, Vec3(0.0f), partName);
						_fe3d.gameEntity_setRotationOrigin(currentAnimation->previewModelID, Vec3(0.0f), partName);
						_fe3d.gameEntity_setRotation(currentAnimation->previewModelID, Vec3(0.0f), partName);

						// Only whole model size must be original
						if (partName.empty())
						{
							_fe3d.gameEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partName);
						}
						else
						{
							_fe3d.gameEntity_setSize(currentAnimation->previewModelID, Vec3(1.0f), partName);
						}
					}

					// Set transformation of current frame
					if (_currentFrameIndex > 0)
					{
						// For every frame until current frame
						for (unsigned int frameIndex = 1; frameIndex <= _currentFrameIndex; frameIndex++)
						{
							// Retrieve frame
							auto frame = currentAnimation->frames[frameIndex];

							// For every part of frame
							for (auto partName : currentAnimation->partNames)
							{
								// Check if model has part
								if (_fe3d.gameEntity_hasPart(currentAnimation->previewModelID, partName) || partName.empty())
								{
									// Determine type of transformation
									if (frame.transformationTypes[partName] == TransformationType::TRANSLATION)
									{
										// Translation
										_fe3d.gameEntity_setPosition(currentAnimation->previewModelID,
											(currentAnimation->initialScaling * frame.targetTransformations[partName]), partName);
									}
									else if (frame.transformationTypes[partName] == TransformationType::ROTATION)
									{
										// Retrieve current model size
										const auto& currentModelSize = _fe3d.gameEntity_getSize(currentAnimation->previewModelID);

										// Origin
										_fe3d.gameEntity_setRotationOrigin(currentAnimation->previewModelID,
											(currentModelSize * frame.rotationOrigins[partName]), partName);

										// Rotation
										_fe3d.gameEntity_setRotation(currentAnimation->previewModelID,
											frame.targetTransformations[partName], partName);
									}
									else if (frame.transformationTypes[partName] == TransformationType::SCALING)
									{
										// Retrieve model size (or part default size)
										const auto& modelSize = partName.empty() ? currentAnimation->initialScaling : Vec3(1.0f);

										// Scaling
										_fe3d.gameEntity_setSize(currentAnimation->previewModelID,
											modelSize + (modelSize * frame.targetTransformations[partName]), partName);
									}
								}
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
			return;
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

bool AnimationEditor::_comparePartNames(vector<string> first, vector<string> second)
{
	// Check size
	if (first.size() != second.size())
	{
		return false;
	}

	// Check content
	for (unsigned int i = 0; i < first.size(); i++)
	{
		if (first[i] != second[i])
		{
			return false;
		}
	}

	// Vectors contents are the same
	return true;
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

const vector<string> AnimationEditor::getAllAnimationNames()
{
	vector<string> names;

	for (auto& animation : _animations)
	{
		names.push_back(animation->ID);
	}

	return names;
}

const vector<string> AnimationEditor::getPlayingAnimationNames()
{
	set<string> names;

	for (const auto& [idPair, animation] : _playingAnimations)
	{
		names.insert(idPair.first);
	}

	return vector<string>(names.begin(), names.end());
}

const vector<string> AnimationEditor::getPlayingAnimationNames(const string& modelID)
{
	set<string> names;

	for (const auto& [idPair, animation] : _playingAnimations)
	{
		if (modelID == idPair.second)
		{
			names.insert(idPair.first);
		}
	}

	return vector<string>(names.begin(), names.end());
}