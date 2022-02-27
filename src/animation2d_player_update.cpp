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

	for(auto& [key, startedAnimation] : _startedQuad3dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(key, DELIMITER);
		const auto animation = _animation2dManager->getAnimation(splitKey.first);
		const auto quad = _quad3dEntityManager->getEntity(splitKey.second);
		const auto interval = static_cast<unsigned int>((animation->getInterval() * startedAnimation->getIntervalMultiplier()) / startedAnimation->getIntervalDivider());

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
								quad3dAnimationsToStop.push_back(key);
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

		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);
	}

	for(const auto& key : quad3dAnimationsToStop)
	{
		_startedQuad3dAnimations.erase(key);
	}
}

void Animation2dPlayer::_updateQuad2dAnimationExecution()
{
	vector<string> quad2dAnimationsToStop;

	for(auto& [key, startedAnimation] : _startedQuad2dAnimations)
	{
		const auto splitKey = Tools::splitStringIntoTwo(key, DELIMITER);
		const auto animation = _animation2dManager->getAnimation(splitKey.first);
		const auto quad = _quad2dEntityManager->getEntity(splitKey.second);

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getUpdateCount() == static_cast<unsigned int>(animation->getInterval() / startedAnimation->getIntervalDivider()))
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
								quad2dAnimationsToStop.push_back(key);
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

		quad->setUvMultiplier(uvMultiplier);
		quad->setUvOffset(uvOffset);
	}

	for(const auto& key : quad2dAnimationsToStop)
	{
		_startedQuad2dAnimations.erase(key);
	}
}