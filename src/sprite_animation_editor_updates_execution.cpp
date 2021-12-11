#include "sprite_animation_editor.hpp"

void SpriteAnimationEditor::_updateAnimationExecution()
{
	// Update all started animations
	for(auto& [idPair, animation] : _startedAnimations)
	{
		// Check if animation is playing
		if(!animation.isPaused())
		{
			// Check if animation is allowed to update
			if(animation.getPassedFrames() >= animation.getFramestep())
			{
				// Reset frames
				animation.setPassedFrames(0);

				// Reached if animation reached column count
				if(animation.getColumnIndex() >= animation.getColumnCount() - 1)
				{
					// Reset column index
					animation.setColumnIndex(0);

					// Check if animation reached row count
					if(animation.getRowIndex() >= animation.getRowCount() - 1)
					{
						// Check if animation is endless
						if(animation.getTimesToPlay() == -1)
						{
							_animationsToStop.insert(idPair);
							_animationsToStartAgain.insert(idPair);
						}
						else
						{
							// Animation finished current play
							animation.setTimesToPlay(animation.getTimesToPlay() - 1);

							// Check if animation must stop
							if(animation.getTimesToPlay() == 0)
							{
								_animationsToStop.insert(idPair);
							}
							else
							{
								animation.setRowIndex(0);
							}
						}
					}
					else // Next row
					{
						animation.setRowIndex(animation.getRowIndex() + 1);
					}
				}
				else // Next column
				{
					animation.setColumnIndex(animation.getColumnIndex() + 1);
				}
			}
			else // Next frame
			{
				animation.setPassedFrames(animation.getPassedFrames() + 1);
			}
		}

		// Apply sprite animation on entity
		const float multiplierX = (1.0f / static_cast<float>(animation.getRowCount()));
		const float multiplierY = (1.0f / static_cast<float>(animation.getColumnCount()));
		const float adderX = (static_cast<float>(animation.getRowIndex()) * multiplierX);
		const float adderY = (static_cast<float>(animation.getColumnIndex()) * multiplierY);
		_fe3d.billboard_setMultiplierUV(idPair.second, fvec2(multiplierX, multiplierY));
		_fe3d.billboard_setAdderUV(idPair.second, fvec2(adderX, adderY));
	}

	// Remove all animations that ended
	for(const auto& idPair : _animationsToStop)
	{
		// Check if animation is still started
		if(isAnimationStarted(idPair.first, idPair.second))
		{
			// Stop animation
			stopAnimation(idPair.first, idPair.second);
		}
	}
	_animationsToStop.clear();

	// Start all endless animations again
	for(const auto& idPair : _animationsToStartAgain)
	{
		// Check if animation is not already started
		if(!isAnimationStarted(idPair.first, idPair.second))
		{
			// Start animation
			startAnimation(idPair.first, idPair.second, -1);
		}
	}
	_animationsToStartAgain.clear();
}