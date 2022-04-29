#include "sound2d_manager.hpp"

using std::make_shared;

void Sound2dManager::deleteSound2ds()
{
	_sound2ds.clear();
}

void Sound2dManager::deleteSound2d(const string & sound2dId)
{
	if(!isSound2dExisting(sound2dId))
	{
		abort();
	}

	_sound2ds.erase(sound2dId);
}

void Sound2dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound2dManager::inject(shared_ptr<WaveBufferCache> waveBufferCache)
{
	_waveBufferCache = waveBufferCache;
}

void Sound2dManager::createSound2d(const string & sound2dId, const string & audioPath)
{
	if(isSound2dExisting(sound2dId))
	{
		abort();
	}

	auto audio = _audioLoader->loadAudio(audioPath);

	if(audio == nullptr)
	{
		return;
	}

	auto sound = make_shared<Sound2d>(sound2dId);

	auto waveBuffer = _waveBufferCache->getBuffer(audioPath);

	if(waveBuffer == nullptr)
	{
		auto audio = _audioLoader->loadAudio(audioPath);

		if(audio == nullptr)
		{
			return;
		}

		waveBuffer = make_shared<WaveBuffer>(audio);

		_waveBufferCache->storeBuffer(audioPath, waveBuffer);
	}

	sound->setWaveBuffer(waveBuffer);
	sound->setAudioPath(audioPath);

	_sound2ds.insert({sound2dId, sound});
}

const bool Sound2dManager::isSound2dExisting(const string & sound2dId) const
{
	return (_sound2ds.find(sound2dId) != _sound2ds.end());
}

const bool Sound2dManager::isSound2dsExisting() const
{
	return !_sound2ds.empty();
}

const unordered_map<string, shared_ptr<Sound2d>> & Sound2dManager::getSound2ds() const
{
	return _sound2ds;
}

const shared_ptr<Sound2d> Sound2dManager::getSound2d(const string & sound2dId) const
{
	auto iterator = _sound2ds.find(sound2dId);

	if(iterator == _sound2ds.end())
	{
		abort();
	}

	return iterator->second;
}