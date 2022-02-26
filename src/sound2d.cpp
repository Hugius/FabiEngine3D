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

void Sound2d::setWaveBuffer(shared_ptr<WaveBuffer> value)
{
	_waveBuffer = value;
}

void Sound2d::setAudioPath(const string& value)
{
	_audioPath = value;
}

const shared_ptr<WaveBuffer> Sound2d::getWaveBuffer() const
{
	return _waveBuffer;
}