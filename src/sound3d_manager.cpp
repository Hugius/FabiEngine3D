#include "sound3d_manager.hpp"

using std::make_shared;

void Sound3dManager::deleteSounds()
{
	_sounds.clear();
}

void Sound3dManager::deleteSound(const string& id)
{
	if(!isSoundExisting(id))
	{
		abort();
	}

	_sounds.erase(id);
}

void Sound3dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound3dManager::inject(shared_ptr<WaveBufferCache> waveBufferCache)
{
	_waveBufferCache = waveBufferCache;
}

void Sound3dManager::update()
{

}

void Sound3dManager::createSound(const string& id, const string& audioPath)
{
	if(isSoundExisting(id))
	{
		abort();
	}

	auto audio = _audioLoader->loadAudio(audioPath);

	if(audio == nullptr)
	{
		return;
	}

	auto sound = make_shared<Sound3d>(id);

	auto buffer = _waveBufferCache->getBuffer(audioPath);

	if(buffer == nullptr)
	{
		auto audio = _audioLoader->loadAudio(audioPath);

		if(audio == nullptr)
		{
			return;
		}

		buffer = make_shared<WaveBuffer>(audio);

		_waveBufferCache->storeBuffer(audioPath, buffer);
	}

	_sounds.insert(make_pair(id, sound));
}

const bool Sound3dManager::isSoundExisting(const string& id) const
{
	return (_sounds.find(id) != _sounds.end());
}

const bool Sound3dManager::isSoundsExisting() const
{
	return !_sounds.empty();
}

const unordered_map<string, shared_ptr<Sound3d>>& Sound3dManager::getSounds() const
{
	return _sounds;
}

const shared_ptr<Sound3d> Sound3dManager::getSound(const string& id) const
{
	auto iterator = _sounds.find(id);

	if(iterator == _sounds.end())
	{
		abort();
	}

	return iterator->second;
}