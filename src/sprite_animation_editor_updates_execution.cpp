#include "sprite_animation_editor.hpp"

void SpriteAnimationEditor::_updateAnimationExecution()
{
	// Update all started animations
	for(auto& [idPair, animation] : _startedAnimations)
	{
		// Check if animation is playing
		if(animation->isStarted() && !animation->isPaused())
		{
			// Check if animation is finished
			if(animation->getPassedLoops() == animation->getMaxLoops())
			{
				animation->stop();
			}
			else
			{
				// Check if allowed to update
				if(animation->getPassedFrames() >= animation->getFramestep())
				{
					// Reset frames
					animation->setPassedFrames(0);

					// Reached if reached column count
					if(animation->getColumnIndex() >= animation->getColumnCount() - 1)
					{
						// Reset column index
						animation->setColumnIndex(0);

						// Check if reached row count
						if(animation->getRowIndex() >= animation->getRowCount() - 1)
						{
							// Reset row index
							animation->setRowIndex(0);

							// Next loop
							animation->setPassedLoops(animation->getPassedLoops() + 1);
						}
						else // Next row
						{
							animation->setRowIndex(animation->getRowIndex() + 1);
						}
					}
					else // Next column
					{
						animation->setColumnIndex(animation->getColumnIndex() + 1);
					}
				}
				else // Next frame
				{
					animation->setPassedFrames(animation->getPassedFrames() + 1);
				}
			}
		}

		// Apply sprite animation
		const float multiplierX = (1.0f / static_cast<float>(animation->getRowCount()));
		const float multiplierY = (1.0f / static_cast<float>(animation->getColumnCount()));
		const float adderX = (static_cast<float>(animation->getRowIndex()) * multiplierX);
		const float adderY = (static_cast<float>(animation->getColumnIndex()) * multiplierY);

	}
}