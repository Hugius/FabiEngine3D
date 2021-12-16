#include "animation2d_editor.hpp"

void Animation2dEditor::_updateBillboardAnimationExecution()
{
	// Update all started animations
	for(auto& [idPair, animation] : _startedBillboardAnimations)
	{
		// Check if animation is playing
		if(!animation.isPaused())
		{
			// Check if animation is allowed to update
			if(animation.getPassedFrames() == animation.getFramestep())
			{
				// Reset frames
				animation.setPassedFrames(0);

				// Reached if animation reached column count
				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					// Reset column index
					animation.setColumnIndex(0);

					// Check if animation reached row count
					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						// Check if animation is endless
						if(animation.getTimesToPlay() == -1)
						{
							_billboardAnimationsToStop.insert(idPair);
							_billboardAnimationsToStart.insert(idPair);
						}
						else
						{
							// Animation finished current play
							animation.setTimesToPlay(animation.getTimesToPlay() - 1);

							// Check if animation must stop
							if(animation.getTimesToPlay() == 0)
							{
								_billboardAnimationsToStop.insert(idPair);
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

		// Update UV properties
		fvec2 multiplierUV = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 adderUV = fvec2((static_cast<float>(animation.getColumnIndex()) * multiplierUV.x),
							  (static_cast<float>(animation.getRowIndex()) * multiplierUV.y));

		// Apply to entity
		_fe3d.billboard_setMultiplierUV(idPair.second, multiplierUV);
		_fe3d.billboard_setAdderUV(idPair.second, adderUV);
	}

	// Remove all animations that ended
	for(const auto& idPair : _billboardAnimationsToStop)
	{
		// Check if animation is still started
		if(isBillboardAnimationStarted(idPair.first, idPair.second))
		{
			stopBillboardAnimation(idPair.first, idPair.second);
		}
	}
	_billboardAnimationsToStop.clear();

	// Start all endless animations again
	for(const auto& idPair : _billboardAnimationsToStart)
	{
		// Check if animation is not already started
		if(!isBillboardAnimationStarted(idPair.first, idPair.second))
		{
			// Start animation
			startBillboardAnimation(idPair.first, idPair.second, -1);
		}
	}
	_billboardAnimationsToStart.clear();
}

void Animation2dEditor::_updateImageAnimationExecution()
{
	// Update all started animations
	for(auto& [idPair, animation] : _startedImageAnimations)
	{
		// Check if animation is playing
		if(!animation.isPaused())
		{
			// Check if animation is allowed to update
			if(animation.getPassedFrames() == animation.getFramestep())
			{
				// Reset frames
				animation.setPassedFrames(0);

				// Reached if animation reached column count
				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					// Reset column index
					animation.setColumnIndex(0);

					// Check if animation reached row count
					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						// Check if animation is endless
						if(animation.getTimesToPlay() == -1)
						{
							_imageAnimationsToStop.insert(idPair);
							_imageAnimationsToStart.insert(idPair);
						}
						else
						{
							// Animation finished current play
							animation.setTimesToPlay(animation.getTimesToPlay() - 1);

							// Check if animation must stop
							if(animation.getTimesToPlay() == 0)
							{
								_imageAnimationsToStop.insert(idPair);
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

		// Update UV properties
		fvec2 multiplierUV = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 adderUV = fvec2((static_cast<float>(animation.getColumnIndex()) * multiplierUV.x),
							  (static_cast<float>(animation.getRowIndex()) * multiplierUV.y));

		// Apply to entity
		_fe3d.image_setMultiplierUV(idPair.second, multiplierUV);
		_fe3d.image_setAdderUV(idPair.second, adderUV);
	}

	// Remove all animations that ended
	for(const auto& idPair : _imageAnimationsToStop)
	{
		// Check if animation is still started
		if(isImageAnimationStarted(idPair.first, idPair.second))
		{
			stopImageAnimation(idPair.first, idPair.second);
		}
	}
	_imageAnimationsToStop.clear();

	// Start all endless animations again
	for(const auto& idPair : _imageAnimationsToStart)
	{
		// Check if animation is not already started
		if(!isImageAnimationStarted(idPair.first, idPair.second))
		{
			// Start animation
			startImageAnimation(idPair.first, idPair.second, -1);
		}
	}
	_imageAnimationsToStart.clear();
}