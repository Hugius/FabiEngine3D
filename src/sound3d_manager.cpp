#include "sound3d_manager.hpp"

using std::make_shared;

void Sound3dManager::deleteSounds()
{
	_sounds.clear();
}

void Sound3dManager::deleteSound(const string & sound3dId)
{
	if(!isSoundExisting(sound3dId))
	{
		abort();
	}

	_sounds.erase(sound3dId);
}

void Sound3dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound3dManager::inject(shared_ptr<WaveBufferCache> waveBufferCache)
{
	_waveBufferCache = waveBufferCache;
}

void Sound3dManager::createSound(const string & sound3dId, const string & audioPath)
{
	if(isSoundExisting(sound3dId))
	{
		abort();
	}

	auto audio = _audioLoader->loadAudio(audioPath);

	if(audio == nullptr)
	{
		return;
	}

	auto sound = make_shared<Sound3d>(sound3dId);

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

	_sounds.insert({sound3dId, sound});
}

const bool Sound3dManager::isSoundExisting(const string & sound3dId) const
{
	return (_sounds.find(sound3dId) != _sounds.end());
}

const bool Sound3dManager::isSoundsExisting() const
{
	return !_sounds.empty();
}

const unordered_map<string, shared_ptr<Sound3d>> & Sound3dManager::getSounds() const
{
	return _sounds;
}

const shared_ptr<Sound3d> Sound3dManager::getSound(const string & sound3dId) const
{
	auto iterator = _sounds.find(sound3dId);

	if(iterator == _sounds.end())
	{
		abort();
	}

	return iterator->second;
}