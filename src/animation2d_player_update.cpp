#include "animation2d_player.hpp"
#include "tools.hpp"

#include <set>

using std::set;

void Animation2dPlayer::update()
{
	_updateQuad3dAnimationExecution();
	_updateQuad2dAnimationExecution();
}

void Animation2dPlayer::_updateQuad3dAnimationExecution()
{
	vector<string> quad3dAnimationsToStop;

	for(auto & [mergedId, startedAnimation] : _startedQuad3dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation = _animation2dManager->getAnimation(splitKey.first);
		const auto quad3d = _quad3dEntityManager->getEntity(splitKey.second);
		const auto interval = static_cast<int>(static_cast<float>(animation->getInterval() * startedAnimation->getIntervalMultiplier()) / static_cast<float>(startedAnimation->getIntervalDivider()));

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getUpdateCount() == interval)
			{
				startedAnimation->setUpdateCount(0);

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
								quad3dAnimationsToStop.push_back(mergedId);
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
				startedAnimation->setUpdateCount(startedAnimation->getUpdateCount() + 1);
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

		quad3d->setUvMultiplier(uvMultiplier);
		quad3d->setUvOffset(uvOffset);
	}

	for(const auto & mergedId : quad3dAnimationsToStop)
	{
		_startedQuad3dAnimations.erase(mergedId);
	}
}

void Animation2dPlayer::_updateQuad2dAnimationExecution()
{
	vector<string> quad2dAnimationsToStop;

	for(auto & [mergedId, startedAnimation] : _startedQuad2dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation = _animation2dManager->getAnimation(splitKey.first);
		const auto quad2d = _quad2dEntityManager->getEntity(splitKey.second);
		const auto interval = static_cast<int>(static_cast<float>(animation->getInterval()) / static_cast<float>(startedAnimation->getIntervalDivider()));

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getUpdateCount() == interval)
			{
				startedAnimation->setUpdateCount(0);

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
								quad2dAnimationsToStop.push_back(mergedId);
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
				startedAnimation->setUpdateCount(startedAnimation->getUpdateCount() + 1);
			}
		}

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation->getColumnCount())),
										(1.0f / static_cast<float>(animation->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation->getRowCount() - startedAnimation->getRowIndex() - 1) * uvMultiplier.y));

		quad2d->setUvMultiplier(uvMultiplier);
		quad2d->setUvOffset(uvOffset);
	}

	for(const auto & mergedId : quad2dAnimationsToStop)
	{
		_startedQuad2dAnimations.erase(mergedId);
	}
}