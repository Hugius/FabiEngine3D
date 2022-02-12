#include "animation2d_player.hpp"

void Animation2dPlayer::update()
{
	_updateQuad3dAnimationExecution();
	_updateQuad2dAnimationExecution();
}

void Animation2dPlayer::_updateQuad3dAnimationExecution()
{
	set<pair<string, string>> quad3dAnimationsToStop;

	for(auto& [key, startedAnimation] : _startedQuad3dAnimations)
	{
		const auto animation = _animation2dManager->getAnimation(key.first);
		const auto quad = _quad3dEntityManager->getEntity(key.second);

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getCycleCount() == static_cast<unsigned int>(animation->getInterval() / startedAnimation->getIntervalDivider()))
			{
				startedAnimation->setCycleCount(0);

				if(startedAnimation->getColumnIndex() >= (animation->getColumnCount() - 1))
				{
					startedAnimation->setColumnIndex(0);

					if(startedAnimation->getRowIndex() >= (animation->getRowCount() - 1))
					{
						startedAnimation->setRowIndex(0);

						if(startedAnimation->getPlayCount() != -1)
						{
							startedAnimation->setPlayCount(startedAnimation->getPlayCount() - 1);

							if(startedAnimation->getPlayCount() == 0)
							{
								quad3dAnimationsToStop.insert(key);
							}
						}
					}
					else
					{
						startedAnimation->setRowIndex(startedAnimation->getRowIndex() + 1);
					}
				}
				else
				{
					startedAnimation->setColumnIndex(startedAnimation->getColumnIndex() + 1);
				}
			}
			else
			{
				startedAnimation->setCycleCount(startedAnimation->getCycleCount() + 1);
			}

			if(startedAnimation->isAutopaused())
			{
				startedAnimation->setPaused(true);
			}
		}

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation->getColumnCount())),
										(1.0f / static_cast<float>(animation->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation->getRowCount() - startedAnimation->getRowIndex() - 1) * uvMultiplier.y));

		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);
	}

	for(const auto& key : quad3dAnimationsToStop)
	{
		_startedQuad3dAnimations.erase(make_pair(key.first, key.second));
	}
}

void Animation2dPlayer::_updateQuad2dAnimationExecution()
{
	set<pair<string, string>> quad2dAnimationsToStop;

	for(auto& [key, startedAnimation] : _startedQuad2dAnimations)
	{
		const auto animation = _animation2dManager->getAnimation(key.first);
		const auto quad = _quad2dEntityManager->getEntity(key.second);

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getCycleCount() == static_cast<unsigned int>(animation->getInterval() / startedAnimation->getIntervalDivider()))
			{
				startedAnimation->setCycleCount(0);

				if(startedAnimation->getColumnIndex() >= (animation->getColumnCount() - 1))
				{
					startedAnimation->setColumnIndex(0);

					if(startedAnimation->getRowIndex() >= (animation->getRowCount() - 1))
					{
						startedAnimation->setRowIndex(0);

						if(startedAnimation->getPlayCount() != -1)
						{
							startedAnimation->setPlayCount(startedAnimation->getPlayCount() - 1);

							if(startedAnimation->getPlayCount() == 0)
							{
								quad2dAnimationsToStop.insert(key);
							}
						}
					}
					else
					{
						startedAnimation->setRowIndex(startedAnimation->getRowIndex() + 1);
					}
				}
				else
				{
					startedAnimation->setColumnIndex(startedAnimation->getColumnIndex() + 1);
				}
			}
			else
			{
				startedAnimation->setCycleCount(startedAnimation->getCycleCount() + 1);
			}
		}

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation->getColumnCount())),
										(1.0f / static_cast<float>(animation->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation->getRowCount() - startedAnimation->getRowIndex() - 1) * uvMultiplier.y));

		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);
	}

	for(const auto& key : quad2dAnimationsToStop)
	{
		_startedQuad2dAnimations.erase(make_pair(key.first, key.second));
	}
}