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
	vector<string> quad3dAnimation2dsToStop = {};

	for(auto & [mergedId, startedAnimation2d] : _startedQuad3dAnimation2ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation2d = _animation2dManager->getAnimation2d(splitKey.first);
		const auto quad3d = _quad3dManager->getQuad3d(splitKey.second);
		const auto interval = static_cast<int>(static_cast<float>(animation2d->getInterval() * startedAnimation2d->getIntervalMultiplier()) / static_cast<float>(startedAnimation2d->getIntervalDivider()));

		if(!startedAnimation2d->isPaused())
		{
			if(startedAnimation2d->getUpdateCount() == interval)
			{
				startedAnimation2d->setUpdateCount(0);

				if(startedAnimation2d->getColumnIndex() >= (animation2d->getColumnCount() - 1))
				{
					startedAnimation2d->setColumnIndex(0);

					if(startedAnimation2d->getRowIndex() >= (animation2d->getRowCount() - 1))
					{
						startedAnimation2d->setRowIndex(0);

						if(startedAnimation2d->getPlayCount() != -1)
						{
							startedAnimation2d->setPlayCount(startedAnimation2d->getPlayCount() - 1);

							if(startedAnimation2d->getPlayCount() == 0)
							{
								quad3dAnimation2dsToStop.push_back(mergedId);
							}
						}
					}
					else
					{
						startedAnimation2d->setRowIndex(startedAnimation2d->getRowIndex() + 1);
					}
				}
				else
				{
					startedAnimation2d->setColumnIndex(startedAnimation2d->getColumnIndex() + 1);
				}
			}
			else
			{
				startedAnimation2d->setUpdateCount(startedAnimation2d->getUpdateCount() + 1);
			}

			if(startedAnimation2d->isAutopaused())
			{
				startedAnimation2d->setPaused(true);
			}
		}

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation2d->getColumnCount())),
										(1.0f / static_cast<float>(animation2d->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation2d->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation2d->getRowCount() - startedAnimation2d->getRowIndex() - 1) * uvMultiplier.y));

		quad3d->setUvMultiplier(uvMultiplier);
		quad3d->setUvOffset(uvOffset);
	}

	for(const auto & mergedId : quad3dAnimation2dsToStop)
	{
		_startedQuad3dAnimation2ds.erase(mergedId);
	}
}

void Animation2dPlayer::_updateQuad2dAnimation2dExecution()
{
	vector<string> quad2dAnimation2dsToStop = {};

	for(auto & [mergedId, startedAnimation2d] : _startedQuad2dAnimation2ds)
	{
		const auto splitKey = Tools::splitStringIntoTwo(mergedId, DELIMITER);
		const auto animation2d = _animation2dManager->getAnimation2d(splitKey.first);
		const auto quad2d = _quad2dManager->getQuad2d(splitKey.second);
		const auto interval = static_cast<int>(static_cast<float>(animation2d->getInterval()) / static_cast<float>(startedAnimation2d->getIntervalDivider()));

		if(!startedAnimation2d->isPaused())
		{
			if(startedAnimation2d->getUpdateCount() == interval)
			{
				startedAnimation2d->setUpdateCount(0);

				if(startedAnimation2d->getColumnIndex() >= (animation2d->getColumnCount() - 1))
				{
					startedAnimation2d->setColumnIndex(0);

					if(startedAnimation2d->getRowIndex() >= (animation2d->getRowCount() - 1))
					{
						startedAnimation2d->setRowIndex(0);

						if(startedAnimation2d->getPlayCount() != -1)
						{
							startedAnimation2d->setPlayCount(startedAnimation2d->getPlayCount() - 1);

							if(startedAnimation2d->getPlayCount() == 0)
							{
								quad2dAnimation2dsToStop.push_back(mergedId);
							}
						}
					}
					else
					{
						startedAnimation2d->setRowIndex(startedAnimation2d->getRowIndex() + 1);
					}
				}
				else
				{
					startedAnimation2d->setColumnIndex(startedAnimation2d->getColumnIndex() + 1);
				}
			}
			else
			{
				startedAnimation2d->setUpdateCount(startedAnimation2d->getUpdateCount() + 1);
			}
		}

		const auto uvMultiplier = fvec2((1.0f / static_cast<float>(animation2d->getColumnCount())),
										(1.0f / static_cast<float>(animation2d->getRowCount())));
		const auto uvOffset = fvec2((static_cast<float>(startedAnimation2d->getColumnIndex()) * uvMultiplier.x),
									(static_cast<float>(animation2d->getRowCount() - startedAnimation2d->getRowIndex() - 1) * uvMultiplier.y));

		quad2d->setUvMultiplier(uvMultiplier);
		quad2d->setUvOffset(uvOffset);
	}

	for(const auto & mergedId : quad2dAnimation2dsToStop)
	{
		_startedQuad2dAnimation2ds.erase(mergedId);
	}
}