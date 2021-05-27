#include "animation_editor.hpp"

#include <algorithm>

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

			if (!modelID.empty() && _fe3d.modelEntity_isExisting(modelID))
			{
				if (_fe3d.input_getKeyToggled(InputType::KEY_F))
				{
					_fe3d.modelEntity_setWireframed(modelID, true);
				}
				else
				{
					_fe3d.modelEntity_setWireframed(modelID, false);
				}
			}
		}

		// Check if animation loaded in editor
		if (!_currentAnimationID.empty())
		{
			// Retrieve current animation
			auto currentAnimation = _getAnimation(_currentAnimationID);

			// Check if animation is not started
			if (!isAnimationStarted(_currentAnimationID, currentAnimation->previewModelID))
			{
				// Check if animation has a preview model
				if (!currentAnimation->previewModelID.empty())
				{
					// Default transformation
					for (auto partID : currentAnimation->partIDs)
					{
						_fe3d.modelEntity_setPosition(currentAnimation->previewModelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID, Vec3(0.0f), partID);
						_fe3d.modelEntity_setRotation(currentAnimation->previewModelID, Vec3(0.0f), partID);

						// Only whole model size must be original
						if (partID.empty())
						{
							_fe3d.modelEntity_setSize(currentAnimation->previewModelID, currentAnimation->initialScaling, partID);
						}
						else
						{
							_fe3d.modelEntity_setSize(currentAnimation->previewModelID, Vec3(1.0f), partID);
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
							for (auto partID : currentAnimation->partIDs)
							{
								// Check if model has part
								if (_fe3d.modelEntity_hasPart(currentAnimation->previewModelID, partID) || partID.empty())
								{
									// Determine type of transformation
									if (frame.transformationTypes[partID] == TransformationType::TRANSLATION)
									{
										// Translation
										_fe3d.modelEntity_setPosition(currentAnimation->previewModelID,
											(currentAnimation->initialScaling * frame.targetTransformations[partID]), partID);
									}
									else if (frame.transformationTypes[partID] == TransformationType::ROTATION)
									{
										// Retrieve current model size
										const auto& currentModelSize = _fe3d.modelEntity_getSize(currentAnimation->previewModelID);

										// Origin
										_fe3d.modelEntity_setRotationOrigin(currentAnimation->previewModelID,
											(currentModelSize * frame.rotationOrigins[partID]), partID);

										// Rotation
										_fe3d.modelEntity_setRotation(currentAnimation->previewModelID,
											frame.targetTransformations[partID], partID);
									}
									else if (frame.transformationTypes[partID] == TransformationType::SCALING)
									{
										// Retrieve model size (or part default size)
										const auto& modelSize = partID.empty() ? currentAnimation->initialScaling : Vec3(1.0f);

										// Scaling
										_fe3d.modelEntity_setSize(currentAnimation->previewModelID,
											modelSize + (modelSize * frame.targetTransformations[partID]), partID);
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
	for (size_t i = 0; i < _animations.size(); i++)
	{
		if (_animations[i]->ID == ID)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	_fe3d.logger_throwError("Cannot delete animation with ID \"" + ID + "\"");
}

bool AnimationEditor::_hasReachedFloat(float first, float second, float speed)
{
	return (first >= second - fabsf(speed)) && (first <= second + fabsf(speed));
}

bool AnimationEditor::_comparePartIDs(vector<string> first, vector<string> second)
{
	// Check size
	if (first.size() != second.size())
	{
		return false;
	}

	// Check content
	for (size_t i = 0; i < first.size(); i++)
	{
		if (first[i] != second[i])
		{
			return false;
		}
	}

	// Vectors contents are the same
	return true;
}

shared_ptr<Animation> AnimationEditor::_getAnimation(const string& ID)
{
	for (const auto& animation : _animations)
	{
		if (animation->ID == ID)
		{
			return animation;
		}
	}

	_fe3d.logger_throwError("Cannot retrieve animation with ID \"" + ID + "\""); 
}

const vector<string> AnimationEditor::getAllAnimationIDs()
{
	vector<string> IDs;

	// Find all IDs
	for (const auto& animation : _animations)
	{
		IDs.push_back(animation->ID);
	}

	// Sort alphabetically
	std::sort(IDs.begin(), IDs.end());

	return IDs;
}

const vector<string> AnimationEditor::getStartedAnimationIDs()
{
	set<string> names;

	for (const auto& [idPair, animation] : _startedAnimations)
	{
		names.insert(idPair.first);
	}

	return vector<string>(names.begin(), names.end());
}

const vector<string> AnimationEditor::getStartedAnimationIDs(const string& modelID)
{
	set<string> names;

	for (const auto& [idPair, animation] : _startedAnimations)
	{
		if (modelID == idPair.second)
		{
			names.insert(idPair.first);
		}
	}

	return vector<string>(names.begin(), names.end());
}