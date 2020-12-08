#include "animation_editor.hpp"

void AnimationEditor::startAnimation(const string& animationID, const string& modelID, int count)
{
	// Temporary values
	string errorMessage = "Trying to start animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is not already playing
	if (_playingAnimations.find(make_pair(animationID, modelID)) == _playingAnimations.end())
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
					// Retrieve animation
					auto animation = _getAnimation(animationID);
					animation->animatedModelID = modelID;
					animation->timesToPlay = count;

					// Synchronize frame speeds
					for (auto& frame : animation->frames)
					{
						frame.originalSpeeds.clear();
						for (auto& partName : frame.partNames)
						{
							frame.originalSpeeds.insert(make_pair(partName, frame.speeds[partName]));
						}
					}

					// Play animation
					_playingAnimations.insert(make_pair(make_pair(animationID, modelID), *animation));
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
	return _playingAnimations.find(make_pair(animationID, modelID)) != _playingAnimations.end();
}

void AnimationEditor::stopAnimation(const string& animationID, const string& modelID)
{
	// Temporary values
	string errorMessage = "Trying to stop animation with ID \"" + animationID + "\" on model with ID \"" + modelID + "\": ";

	// Check if animation is already playing
	if (_playingAnimations.find(make_pair(animationID, modelID)) != _playingAnimations.end())
	{
		_playingAnimations.erase(make_pair(animationID, modelID));
	}
	else
	{
		_fe3d.logger_throwWarning(errorMessage +  "was not playing!");
	}
}

void AnimationEditor::_updateAnimationExecution()
{
	// Temporary values
	vector<pair<string, string>> animationsToStop;
	vector<pair<string, string>> animationsToStart;

	// Update all playing animations
	for (auto& [idPair, animation] : _playingAnimations)
	{
		// Retrieve current frame
		auto& frame = animation.frames[animation.frameIndex];

		// For every model part in this frame
		unsigned int finishedPartsAmount = 0;
		for (auto& partName : frame.partNames)
		{
			// Check if reached transformation of current frame
			if (_hasReachedFloat(frame.totalTransformations[partName].x, frame.targetTransformations[partName].x, frame.speeds[partName]) &&
				_hasReachedFloat(frame.totalTransformations[partName].y, frame.targetTransformations[partName].y, frame.speeds[partName]) &&
				_hasReachedFloat(frame.totalTransformations[partName].z, frame.targetTransformations[partName].z, frame.speeds[partName]))
			{
				finishedPartsAmount++;
			}
			else
			{
				// X transformation
				if (!_hasReachedFloat(frame.totalTransformations[partName].x, frame.targetTransformations[partName].x, frame.speeds[partName]))
				{
					// Determine speed type
					if (frame.speedTypes[partName] == AnimationSpeedType::LINEAR)
					{
						frame.totalTransformations[partName].x += frame.speeds[partName];
					}
					else
					{
						frame.totalTransformations[partName].x += frame.speeds[partName];
						frame.speeds[partName] += (frame.speeds[partName] / 100.0f);
					}

					// Determine transformation type
					if (animation.transformationType == TransformationType::TRANSLATION)
					{
						_fe3d.gameEntity_move(animation.animatedModelID, Vec3(frame.speeds[partName], 0.0f, 0.0f), partName);
					}
					else if (animation.transformationType == TransformationType::ROTATION)
					{
						_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(frame.speeds[partName], 0.0f, 0.0f), partName);
					}
					else if (animation.transformationType == TransformationType::SCALING)
					{
						_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(frame.speeds[partName], 0.0f, 0.0f), partName);
					}
				}

				// Y transformation
				if (!_hasReachedFloat(frame.totalTransformations[partName].y, frame.targetTransformations[partName].y, frame.speeds[partName]))
				{
					// Determine speed type
					if (frame.speedTypes[partName] == AnimationSpeedType::LINEAR)
					{
						frame.totalTransformations[partName].y += frame.speeds[partName];
					}
					else
					{
						frame.totalTransformations[partName].y += frame.speeds[partName];
						frame.speeds[partName] += (frame.speeds[partName] / 100.0f);
					}

					// Determine transformation type
					if (animation.transformationType == TransformationType::TRANSLATION)
					{
						_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, frame.speeds[partName], 0.0f), partName);
					}
					else if (animation.transformationType == TransformationType::ROTATION)
					{
						_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, frame.speeds[partName], 0.0f), partName);
					}
					else if (animation.transformationType == TransformationType::SCALING)
					{
						_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, frame.speeds[partName], 0.0f), partName);
					}
				}

				// Z transformation
				if (!_hasReachedFloat(frame.totalTransformations[partName].z, frame.targetTransformations[partName].z, frame.speeds[partName]))
				{
					// Determine speed type
					if (frame.speedTypes[partName] == AnimationSpeedType::LINEAR)
					{
						frame.totalTransformations[partName].z += frame.speeds[partName];
					}
					else
					{
						frame.totalTransformations[partName].z += frame.speeds[partName];
						frame.speeds[partName] += (frame.speeds[partName] / 100.0f);
					}

					// Determine transformation type
					if (animation.transformationType == TransformationType::TRANSLATION)
					{
						_fe3d.gameEntity_move(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speeds[partName]), partName);
					}
					else if (animation.transformationType == TransformationType::ROTATION)
					{
						_fe3d.gameEntity_rotate(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speeds[partName]), partName);
					}
					else if (animation.transformationType == TransformationType::SCALING)
					{
						_fe3d.gameEntity_scale(animation.animatedModelID, Vec3(0.0f, 0.0f, frame.speeds[partName]), partName);
					}
				}
			}
		}

		// Check if animation is finished
		if (finishedPartsAmount == frame.partNames.size())
		{
			// Next frame or reset animation
			if (animation.frameIndex >= animation.frames.size() - 1)
			{
				// Playing endlessly
				if (animation.timesToPlay == -1)
				{
					animationsToStop.push_back(idPair);
					animationsToStart.push_back(idPair);
				}

				// Played animation once
				animation.timesToPlay--;

				// Check if animation has ended
				if (animation.timesToPlay == 0)
				{
					animationsToStop.push_back(idPair);
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
	}

	// Remove all animations that ended
	for (auto& idPair : animationsToStop)
	{
		stopAnimation(idPair.first, idPair.second);
	}

	// Start all animations that play endlessly
	for (auto& idPair : animationsToStart)
	{
		startAnimation(idPair.first, idPair.second, -1);
	}
}