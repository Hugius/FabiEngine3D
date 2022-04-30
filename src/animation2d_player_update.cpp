#include "animation2d_player.hpp"
#include "tools.hpp"

#include <set>

using std::set;

void Animation2dPlayer::update()
{
	_updateQuad3dAnimation2dExecution();
	_updateQuad2dAnimation2dExecution();
}

void Animation2dPlayer::_updateQuad3dAnimation2dExecution()
{
	vector<string> quad3dAnimationsToStop;

	for(auto & [mergedId, startedAnimation] : _startedQuad3dAnimation2ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation2d = _animation2dManager->getAnimation2d(splitKey.first);
		const auto quad3d = _quad3dManager->getQuad3d(splitKey.second);
		const auto interval = static_cast<int>(static_cast<float>(animation2d->getInterval() * startedAnimation->getIntervalMultiplier()) / static_cast<float>(startedAnimation->getIntervalDivider()));

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getUpdateCount() == interval)
			{
				startedAnimation->setUpdateCount(0);

				if(startedAnimation->getColumnIndex() >= (animation2d->getColumnCount() - 1))
				{
					startedAnimation->setColumnIndex(0);

					if(startedAnimation->getRowIndex() >= (animation2d->getRowCount() - 1))
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

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation2d->getColumnCount())),
										(1.0f / static_cast<float>(animation2d->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation2d->getRowCount() - startedAnimation->getRowIndex() - 1) * uvMultiplier.y));

		quad3d->setUvMultiplier(uvMultiplier);
		quad3d->setUvOffset(uvOffset);
	}

	for(const auto & mergedId : quad3dAnimationsToStop)
	{
		_startedQuad3dAnimation2ds.erase(mergedId);
	}
}

void Animation2dPlayer::_updateQuad2dAnimation2dExecution()
{
	vector<string> quad2dAnimationsToStop;

	for(auto & [mergedId, startedAnimation] : _startedQuad2dAnimation2ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation2d = _animation2dManager->getAnimation2d(splitKey.first);
		const auto quad2d = _quad2dManager->getQuad2d(splitKey.second);
		const auto interval = static_cast<int>(static_cast<float>(animation2d->getInterval()) / static_cast<float>(startedAnimation->getIntervalDivider()));

		if(!startedAnimation->isPaused())
		{
			if(startedAnimation->getUpdateCount() == interval)
			{
				startedAnimation->setUpdateCount(0);

				if(startedAnimation->getColumnIndex() >= (animation2d->getColumnCount() - 1))
				{
					startedAnimation->setColumnIndex(0);

					if(startedAnimation->getRowIndex() >= (animation2d->getRowCount() - 1))
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

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation2d->getColumnCount())),
										(1.0f / static_cast<float>(animation2d->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation2d->getRowCount() - startedAnimation->getRowIndex() - 1) * uvMultiplier.y));

		quad2d->setUvMultiplier(uvMultiplier);
		quad2d->setUvOffset(uvOffset);
	}

	for(const auto & mergedId : quad2dAnimationsToStop)
	{
		_startedQuad2dAnimation2ds.erase(mergedId);
	}
}