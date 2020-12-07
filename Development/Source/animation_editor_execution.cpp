#include "animation_editor.hpp"

void AnimationEditor::startAnimation(const string& animationID, const string& modelID, int count)
{
	// Temporary values
	string composedID = animationID + "_" + modelID;
	string errorMessage = "Trying to start animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is not already playing
	if (_playingAnimations.find(composedID) == _playingAnimations.end())
	{
		// Check if animation exists
		if (_isAnimationExisting(animationID))
		{
			// Check if model trying to animate exists
			if (_fe3d.gameEntity_isExisting(modelID))
			{
				// Check if animation count is valid
				if (count >= -1)
				{
					// Retrieve & prepare animation
					auto animation = _getAnimation(animationID);
					animation->animatedModelID = modelID;
					animation->timesToPlay = count;
					for (auto& frame : animation->frames)
					{
						frame.originalSpeed = frame.speed;
					}

					// Play animation
					_playingAnimations.insert(std::make_pair(composedID, *animation));
				}
				else
				{
					_fe3d.logger_throwWarning(errorMessage + "play count is invalid!");
				}
			}
			else
			{
				_fe3d.logger_throwWarning(errorMessage + "model not existing!");
			}
		}
		else
		{
			_fe3d.logger_throwWarning(errorMessage + "animation not existing!");
		}
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage + "is already playing!");
	}
}

bool AnimationEditor::isAnimationPlaying(const string& animationID, const string& modelID)
{
	string composedID = animationID + "_" + modelID;
	return _playingAnimations.find(composedID) != _playingAnimations.end();
}

void AnimationEditor::stopAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string composedID = animationID + "_" + modelID;
	string errorMessage = "Trying to stop animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is already playing
	if (_playingAnimations.find(composedID) != _playingAnimations.end())
	{
		_playingAnimations.erase(composedID);
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage +  "was not playing!");
	}
}

void AnimationEditor::_updateAnimationExecution()
{
	vector<string> animationsThatEnded;

	// Update all playing animations
	for (auto& [ID, animation] : _playingAnimations)
	{
		// Retrieve current frame
		auto& frame = animation.frames[animation.frameIndex];

		// Check if reached transformation of current frame
		if (_hasReachedFloat(animation.totalTransformation.x, frame.targetTransformation.x, frame.speed) &&
			_hasReachedFloat(animation.totalTransformation.y, frame.targetTransformation.y, frame.speed) &&
			_hasReachedFloat(animation.totalTransformation.z, frame.targetTransformation.z, frame.speed))
		{
			// Next frame or reset animation
			if (animation.frameIndex >= animation.frames.size() - 1)
			{
				// Playing endlessly
				if (animation.timesToPlay == -1)
				{
					// Reset animation values
					animation.totalTransformation = Vec3(0.0f);
					animation.frameIndex = 0;
					for (auto& frame : animation.frames)
					{
						frame.speed = frame.originalSpeed;
					}
					continue;
				}

				// Played animation once
				animation.timesToPlay--;

				// Check if animation has ended
				if (animation.timesToPlay == 0)
				{
					animationsThatEnded.push_back(ID);
				}
				else
				{
					animation.frameIndex = 0;
				}
			}
			else
			{
				animation.frameIndex++;
			}
		}
		else
		{
			// X transformation
			if (!_hasReachedFloat(animation.totalTransformation.x, frame.targetTransformation.x, frame.speed))
			{
				// Determine speed type
				if (frame.speedType == AnimationSpeedType::LINEAR)
				{
					animation.totalTransformation.x += frame.speed;
				}
				else
				{
					animation.totalTransformation.x += frame.speed;
					frame.speed += (frame.speed / 100.0f);
				}

				// Determine transformation type
				if (animation.transformationType == TransformationType::TRANSLATION)
				{
					_fe3d.gameEntity_move(animation.animatedModelID, Vec3(frame.speed, 0.0f, 0.0f));
				}
				else if (animation.transformationType == TransformationType::ROTATION)
				{
					_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(frame.speed, 0.0f, 0.0f));
				}
				else if (animation.transformationType == TransformationType::SCALING)
				{
					_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(frame.speed, 0.0f, 0.0f));
				}
			}

			// Y transformation
			if (!_hasReachedFloat(animation.totalTransformation.y, frame.targetTransformation.y, frame.speed))
			{
				// Determine speed type
				if (frame.speedType == AnimationSpeedType::LINEAR)
				{
					animation.totalTransformation.y += frame.speed;
				}
				else
				{
					animation.totalTransformation.y += frame.speed;
					frame.speed += (frame.speed / 100.0f);
				}

				// Determine transformation type
				if (animation.transformationType == TransformationType::TRANSLATION)
				{
					_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, frame.speed, 0.0f));
				}
				else if (animation.transformationType == TransformationType::ROTATION)
				{
					_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, frame.speed, 0.0f));
				}
				else if (animation.transformationType == TransformationType::SCALING)
				{
					_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, frame.speed, 0.0f));
				}
			}

			// Z transformation
			if (!_hasReachedFloat(animation.totalTransformation.z, frame.targetTransformation.z, frame.speed))
			{
				// Determine speed type
				if (frame.speedType == AnimationSpeedType::LINEAR)
				{
					animation.totalTransformation.z += frame.speed;
				}
				else
				{
					animation.totalTransformation.z += frame.speed;
					frame.speed += (frame.speed / 100.0f);
				}

				// Determine transformation type
				if (animation.transformationType == TransformationType::TRANSLATION)
				{
					_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speed));
				}
				else if (animation.transformationType == TransformationType::ROTATION)
				{
					_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speed));
				}
				else if (animation.transformationType == TransformationType::SCALING)
				{
					_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speed));
				}
			}
		}
	}

	// Remove all animations that ended
	for (auto& ID : animationsThatEnded)
	{
		_playingAnimations.erase(ID);
	}
}