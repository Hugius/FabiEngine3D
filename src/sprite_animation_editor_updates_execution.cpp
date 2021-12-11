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
			if(animation->getLoops() == animation->getMaxLoops())
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
							animation->setLoops(animation->getLoops() + 1);
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
	}

	// Sprite animation
	//fvec2 uvMultiplier = fvec2(1.0f);
	//fvec2 uvAdder = fvec2(0.0f);
	//if(entity->isSpriteAnimationStarted())
	//{
	//	// Retrieve values
	//	const auto rowCount = entity->getTotalSpriteAnimationRowCount();
	//	const auto columnCount = entity->getTotalSpriteAnimationColumnCount();
	//	const auto rowIndex = entity->getSpriteAnimationRowIndex();
	//	const auto columnIndex = entity->getSpriteAnimationColumnIndex();

	//	// Apply values
	//	uvMultiplier = fvec2(1.0f / static_cast<float>(columnCount), 1.0f / static_cast<float>(rowCount));
	//	uvAdder = fvec2(static_cast<float>(columnIndex) * uvMultiplier.x, static_cast<float>(rowIndex) * uvMultiplier.y);
	//}
}