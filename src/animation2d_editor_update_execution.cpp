#include "animation2d_editor.hpp"

void Animation2dEditor::_updateQuad3dAnimationExecution()
{
	for(auto& [key, animation] : _startedQuad3dAnimations)
	{
		if(!_fe3d->quad3d_isExisting(key.second))
		{
			_quad3dAnimationsToStop.insert(key);
			continue;
		}

		if(!animation.isPaused())
		{
			if(animation.getPassedFrames() == animation.getInterval())
			{
				animation.setPassedFrames(0);

				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					animation.setColumnIndex(0);

					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						animation.setRowIndex(0);

						if(animation.getPlayCount() == -1)
						{
							_quad3dAnimationsToStop.insert(key);
							_quad3dAnimationsToStart.insert(key);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_quad3dAnimationsToStop.insert(key);
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

			if(animation.isAutopaused())
			{
				animation.setPaused(true);
			}
		}

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
										(1.0f / static_cast<float>(animation.getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(animation.getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation.getRowCount() - animation.getRowIndex() - 1) * uvMultiplier.y));

		_fe3d->quad3d_setUvMultiplier(key.second, uvMultiplier);
		_fe3d->quad3d_setUvOffset(key.second, uvOffset);
	}

	for(const auto& key : _quad3dAnimationsToStop)
	{
		if(isQuad3dAnimationStarted(key.first, key.second))
		{
			stopQuad3dAnimation(key.first, key.second);
		}
	}

	for(const auto& key : _quad3dAnimationsToStart)
	{
		if(!isQuad3dAnimationStarted(key.first, key.second))
		{
			startQuad3dAnimation(key.first, key.second, -1);
		}
	}

	_quad3dAnimationsToStop.clear();
	_quad3dAnimationsToStart.clear();
}

void Animation2dEditor::_updateQuad2dAnimationExecution()
{
	for(auto& [key, animation] : _startedQuad2dAnimations)
	{
		if(!_fe3d->quad2d_isExisting(key.second))
		{
			_quad2dAnimationsToStop.insert(key);
			continue;
		}

		if(!animation.isPaused())
		{
			if(animation.getPassedFrames() == animation.getInterval())
			{
				animation.setPassedFrames(0);

				if(animation.getColumnIndex() == (animation.getColumnCount() - 1))
				{
					animation.setColumnIndex(0);

					if(animation.getRowIndex() == (animation.getRowCount() - 1))
					{
						animation.setRowIndex(0);

						if(animation.getPlayCount() == -1)
						{
							_quad2dAnimationsToStop.insert(key);
							_quad2dAnimationsToStart.insert(key);
						}
						else
						{
							animation.setPlayCount(animation.getPlayCount() - 1);

							if(animation.getPlayCount() == 0)
							{
								_quad2dAnimationsToStop.insert(key);
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

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation.getColumnCount())),
										(1.0f / static_cast<float>(animation.getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(animation.getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation.getRowIndex()) * uvMultiplier.y));

		_fe3d->quad2d_setUvMultiplier(key.second, uvMultiplier);
		_fe3d->quad2d_setUvOffset(key.second, uvOffset);
	}

	for(const auto& key : _quad2dAnimationsToStop)
	{
		if(isQuad2dAnimationStarted(key.first, key.second))
		{
			stopQuad2dAnimation(key.first, key.second);
		}
	}

	for(const auto& key : _quad2dAnimationsToStart)
	{
		if(!isQuad2dAnimationStarted(key.first, key.second))
		{
			startQuad2dAnimation(key.first, key.second, -1);
		}
	}

	_quad2dAnimationsToStop.clear();
	_quad2dAnimationsToStart.clear();
}