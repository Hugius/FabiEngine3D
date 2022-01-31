#include "animation2d_editor.hpp"
#include "logger.hpp"

const vector<string> Animation2dEditor::getAnimationIds()
{
	vector<string> result;

	for(const auto& animation : _animations)
	{
		result.push_back(animation->getId());
	}

	sort(result.begin(), result.end());

	return result;
}

const vector<string> Animation2dEditor::getStartedQuad3dAnimationIds() const
{
	set<string> Ids;

	for(const auto& [key, animation] : _startedQuad3dAnimations)
	{
		Ids.insert(key.first);
	}

	return vector<string>(Ids.begin(), Ids.end());
}

const vector<string> Animation2dEditor::getStartedQuad2dAnimationIds() const
{
	set<string> Ids;

	for(const auto& [key, animation] : _startedQuad2dAnimations)
	{
		Ids.insert(key.first);
	}

	return vector<string>(Ids.begin(), Ids.end());
}

const vector<string> Animation2dEditor::getStartedQuad3dAnimationIds(const string& quadId) const
{
	set<string> Ids;

	for(const auto& [key, animation] : _startedQuad3dAnimations)
	{
		if(quadId == key.second)
		{
			Ids.insert(key.first);
		}
	}

	return vector<string>(Ids.begin(), Ids.end());
}

const vector<string> Animation2dEditor::getStartedQuad2dAnimationIds(const string& quadId) const
{
	set<string> Ids;

	for(const auto& [key, animation] : _startedQuad2dAnimations)
	{
		if(quadId == key.second)
		{
			Ids.insert(key.first);
		}
	}

	return vector<string>(Ids.begin(), Ids.end());
}

const unsigned int Animation2dEditor::getQuad3dAnimationRowCount(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getRowCount();
}

const unsigned int Animation2dEditor::getQuad3dAnimationColumnCount(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getColumnCount();
}

const unsigned int Animation2dEditor::getQuad3dAnimationRowIndex(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getRowIndex();
}

const unsigned int Animation2dEditor::getQuad3dAnimationColumnIndex(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getColumnIndex();
}

const int Animation2dEditor::getQuad3dAnimationPlayCount(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getPlayCount();
}

const unsigned int Animation2dEditor::getQuad3dAnimationInterval(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->getInterval();
}

const unsigned int Animation2dEditor::getQuad2dAnimationRowCount(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getRowCount();
}

const unsigned int Animation2dEditor::getQuad2dAnimationColumnCount(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getColumnCount();
}

const unsigned int Animation2dEditor::getQuad2dAnimationRowIndex(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getRowIndex();
}

const unsigned int Animation2dEditor::getQuad2dAnimationColumnIndex(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getColumnIndex();
}

const int Animation2dEditor::getQuad2dAnimationPlayCount(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getPlayCount();
}

const unsigned int Animation2dEditor::getQuad2dAnimationInterval(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->getInterval();
}

void Animation2dEditor::_deleteAnimation(const string& id)
{
	for(size_t i = 0; i < _animations.size(); i++)
	{
		if(_animations[i]->getId() == id)
		{
			_animations.erase(_animations.begin() + i);
			return;
		}
	}

	abort();
}

shared_ptr<Animation2d> Animation2dEditor::_getAnimation(const string& id) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getId() == id)
		{
			return animation;
		}
	}

	abort();
}

const bool Animation2dEditor::isAnimationExisting(const string& id) const
{
	for(const auto& animation : _animations)
	{
		if(animation->getId() == id)
		{
			return true;
		}
	}

	return false;
}

const bool Animation2dEditor::isQuad3dAnimationStarted(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}

	return (_startedQuad3dAnimations.find(make_pair(animationId, quadId)) != _startedQuad3dAnimations.end());
}

const bool Animation2dEditor::isQuad3dAnimationPlaying(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return !isQuad3dAnimationPaused(animationId, quadId);
}

const bool Animation2dEditor::isQuad3dAnimationPaused(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->isPaused();
}

const bool Animation2dEditor::isQuad3dAnimationAutopaused(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad3d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad3dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad3dAnimations.at(make_pair(animationId, quadId))->isAutopaused();
}

const bool Animation2dEditor::isQuad2dAnimationStarted(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}

	return (_startedQuad2dAnimations.find(make_pair(animationId, quadId)) != _startedQuad2dAnimations.end());
}

const bool Animation2dEditor::isQuad2dAnimationPlaying(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return !isQuad2dAnimationPaused(animationId, quadId);
}

const bool Animation2dEditor::isQuad2dAnimationPaused(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->isPaused();
}

const bool Animation2dEditor::isQuad2dAnimationAutopaused(const string& animationId, const string& quadId) const
{
	if(!isAnimationExisting(animationId))
	{
		abort();
	}
	if(!_fe3d->quad2d_isExisting(quadId))
	{
		abort();
	}
	if(!isQuad2dAnimationStarted(animationId, quadId))
	{
		abort();
	}

	return _startedQuad2dAnimations.at(make_pair(animationId, quadId))->isAutopaused();
}