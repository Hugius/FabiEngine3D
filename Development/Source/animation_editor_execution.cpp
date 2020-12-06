#include "animation_editor.hpp"

void AnimationEditor::startAnimation(const string& animationID, const string& modelID)
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
				auto animation = _getAnimation(animationID);
				animation->animatedModelID = modelID;
				_playingAnimations.insert(std::make_pair(composedID, *animation));
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
		const auto& frame = animation.frames[animation.frameIndex];

		// Determine transformation type
		if (animation.transformationType == TransformationType::TRANSLATION)
		{
			
		}
		else if (animation.transformationType == TransformationType::ROTATION)
		{
			if (animation.totalTransformation == frame.targetTransformation)
			{
				if (animation.frameIndex >= animation.frames.size() - 1)
				{
					animationsThatEnded.push_back(ID);
				}
				else
				{
					animation.frameIndex++;
				}
			}
			else
			{
				if (animation.totalTransformation.x != frame.targetTransformation.x)
				{
					animation.totalTransformation.x += frame.speed;
					_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(frame.speed, 0.0f, 0.0f));
				}
				if (animation.totalTransformation.y != frame.targetTransformation.y)
				{
					animation.totalTransformation.y += frame.speed;
					_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, frame.speed, 0.0f));
				}
				if (animation.totalTransformation.z != frame.targetTransformation.z)
				{
					animation.totalTransformation.z += frame.speed;
					_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speed));
				}
			}
		}
		else if(animation.transformationType == TransformationType::SCALING)
		{
			
		}
	}

	// Remove all animations that ended
	for (auto& ID : animationsThatEnded)
	{
		_playingAnimations.erase(ID);
	}
}