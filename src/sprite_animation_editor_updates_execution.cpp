#include "sprite_animation_editor.hpp"

void SpriteAnimationEditor::_updateAnimationExecution()
{
	//// Update sprite animations
	//if(entity->isSpriteAnimationStarted() && !entity->isSpriteAnimationPaused() &&
	//   (entity->getSpriteAnimationLoops() != entity->getMaxSpriteAnimationLoops()))
	//{
	//	if(entity->getPassedSpriteAnimationFrames() >= entity->getSpriteAnimationFramestep()) // Is allowed to update
	//	{
	//		entity->resetPassedSpriteAnimationFrames(); // Reset counter

	//		if(entity->getSpriteAnimationColumnIndex() >= entity->getTotalSpriteAnimationColumnCount() - 1) // Reached column count
	//		{
	//			entity->setSpriteAnimationColumnIndex(0); // Reset column index

	//			if(entity->getSpriteAnimationRowIndex() >= entity->getTotalSpriteAnimationRowCount() - 1) // Reached row count
	//			{
	//				entity->increaseSpriteAnimationLoops();
	//				entity->setSpriteAnimationRowIndex(0); // Reset row index (animation finished)
	//			}
	//			else // Next row
	//			{
	//				entity->setSpriteAnimationRowIndex(entity->getSpriteAnimationRowIndex() + 1);
	//			}
	//		}
	//		else // Next column
	//		{
	//			entity->setSpriteAnimationColumnIndex(entity->getSpriteAnimationColumnIndex() + 1);
	//		}
	//	}
	//	else // Increase counter
	//	{
	//		entity->increasePassedSpriteAnimationFrames();
	//	}
	//}

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