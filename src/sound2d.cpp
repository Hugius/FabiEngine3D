#include "sound2d.hpp"

#include <algorithm>

using std::clamp;

Sound2d::Sound2d(const string& id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

const string& Sound2d::getId() const
{
	return _id;
}

const string& Sound2d::getAudioPath() const
{
	return _audioPath;
}

void Sound2d::setAudio(shared_ptr<Audio> value)
{
	_audio = value;
}

void Sound2d::setAudioPath(const string& value)
{
	_audioPath = value;
}

void Sound2d::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

const float Sound2d::getVolume() const
{
	return _volume;
}

const shared_ptr<Audio> Sound2d::getAudio() const
{
	return _audio;
}