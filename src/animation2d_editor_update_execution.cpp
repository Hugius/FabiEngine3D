#include "animation2d_editor.hpp"

void Animation2dEditor::_updateBillboardAnimationExecution()
{
	for(auto& [idPair, animation] : _startedBillboardAnimations)
	{
		if(!animation.isPaused())
		{
			if(animation.getPassedFrames() == animation.getFramestep())
			{
				animation.setPassedFrames(0);

				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					animation.setColumnIndex(0);

					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						if(animation.getPlayCount() == -1)
						{
							_billboardAnimationsToStop.insert(idPair);
							_billboardAnimationsToStart.insert(idPair);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_billboardAnimationsToStop.insert(idPair);
							}
							else
							{
								animation.setRowIndex(0);
							}
						}
					}
					else
					{
						animation.setRowIndex(animation.getRowIndex() + 1);
					}
				}
				else
				{
					animation.setColumnIndex(animation.getColumnIndex() + 1);
				}
			}
			else
			{
				animation.setPassedFrames(animation.getPassedFrames() + 1);
			}
		}

		fvec2 multiplierUV = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 adderUV = fvec2((static_cast<float>(animation.getColumnIndex()) * multiplierUV.x),
							  (static_cast<float>(animation.getRowIndex()) * multiplierUV.y));

		_fe3d.billboard_setMultiplierUV(idPair.second, multiplierUV);
		_fe3d.billboard_setAdderUV(idPair.second, adderUV);
	}

	for(const auto& idPair : _billboardAnimationsToStop)
	{
		if(isBillboardAnimationStarted(idPair.first, idPair.second))
		{
			stopBillboardAnimation(idPair.first, idPair.second);
		}
	}
	_billboardAnimationsToStop.clear();

	for(const auto& idPair : _billboardAnimationsToStart)
	{
		if(!isBillboardAnimationStarted(idPair.first, idPair.second))
		{
			startBillboardAnimation(idPair.first, idPair.second, -1);
		}
	}
	_billboardAnimationsToStart.clear();
}

void Animation2dEditor::_updateImageAnimationExecution()
{
	for(auto& [idPair, animation] : _startedImageAnimations)
	{
		if(!animation.isPaused())
		{
			if(animation.getPassedFrames() == animation.getFramestep())
			{
				animation.setPassedFrames(0);

				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					animation.setColumnIndex(0);

					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						if(animation.getPlayCount() == -1)
						{
							_imageAnimationsToStop.insert(idPair);
							_imageAnimationsToStart.insert(idPair);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_imageAnimationsToStop.insert(idPair);
							}
							else
							{
								animation.setRowIndex(0);
							}
						}
					}
					else
					{
						animation.setRowIndex(animation.getRowIndex() + 1);
					}
				}
				else
				{
					animation.setColumnIndex(animation.getColumnIndex() + 1);
				}
			}
			else
			{
				animation.setPassedFrames(animation.getPassedFrames() + 1);
			}
		}

		fvec2 multiplierUV = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 adderUV = fvec2((static_cast<float>(animation.getColumnIndex()) * multiplierUV.x),
							  (static_cast<float>(animation.getRowIndex()) * multiplierUV.y));

		_fe3d.image_setMultiplierUV(idPair.second, multiplierUV);
		_fe3d.image_setAdderUV(idPair.second, adderUV);
	}

	for(const auto& idPair : _imageAnimationsToStop)
	{
		if(isImageAnimationStarted(idPair.first, idPair.second))
		{
			stopImageAnimation(idPair.first, idPair.second);
		}
	}
	_imageAnimationsToStop.clear();

	for(const auto& idPair : _imageAnimationsToStart)
	{
		if(!isImageAnimationStarted(idPair.first, idPair.second))
		{
			startImageAnimation(idPair.first, idPair.second, -1);
		}
	}
	_imageAnimationsToStart.clear();
}