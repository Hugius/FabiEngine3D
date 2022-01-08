#include "animation2d_editor.hpp"

void Animation2dEditor::_updateBillboardAnimationExecution()
{
	for(auto& [key, animation] : _startedBillboardAnimations)
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
							_billboardAnimationsToStop.insert(key);
							_billboardAnimationsToStart.insert(key);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_billboardAnimationsToStop.insert(key);
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

		fvec2 uvMultiplier = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 uvOffset = fvec2((static_cast<float>(animation.getColumnIndex()) * uvMultiplier.x),
							   (static_cast<float>(animation.getRowCount() - animation.getRowIndex() - 1) * uvMultiplier.y));

		_fe3d.billboard_setUvMultiplier(key.second, uvMultiplier);
		_fe3d.billboard_setUvOffset(key.second, uvOffset);
	}

	for(const auto& key : _billboardAnimationsToStop)
	{
		if(isBillboardAnimationStarted(key.first, key.second))
		{
			stopBillboardAnimation(key.first, key.second);
		}
	}
	_billboardAnimationsToStop.clear();

	for(const auto& key : _billboardAnimationsToStart)
	{
		if(!isBillboardAnimationStarted(key.first, key.second))
		{
			startBillboardAnimation(key.first, key.second, -1);
		}
	}
	_billboardAnimationsToStart.clear();
}

void Animation2dEditor::_updateQuadAnimationExecution()
{
	for(auto& [key, animation] : _startedQuadAnimations)
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
							_quadAnimationsToStop.insert(key);
							_quadAnimationsToStart.insert(key);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_quadAnimationsToStop.insert(key);
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

		fvec2 uvMultiplier = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
								   (1.0f / static_cast<float>(animation.getRowCount())));
		fvec2 uvOffset = fvec2((static_cast<float>(animation.getColumnIndex()) * uvMultiplier.x),
							   (static_cast<float>(animation.getRowIndex()) * uvMultiplier.y));

		_fe3d.quad_setUvMultiplier(key.second, uvMultiplier);
		_fe3d.quad_setUvOffset(key.second, uvOffset);
	}

	for(const auto& key : _quadAnimationsToStop)
	{
		if(isQuadAnimationStarted(key.first, key.second))
		{
			stopQuadAnimation(key.first, key.second);
		}
	}
	_quadAnimationsToStop.clear();

	for(const auto& key : _quadAnimationsToStart)
	{
		if(!isQuadAnimationStarted(key.first, key.second))
		{
			startQuadAnimation(key.first, key.second, -1);
		}
	}
	_quadAnimationsToStart.clear();
}