#include "sound2d_manager.hpp"

void Sound2dManager::deleteSounds()
{
	_sounds.clear();
}

void Sound2dManager::deleteSound(const string& id)
{
	if(!isSoundExisting(id))
	{
		abort();
	}

	_sounds.erase(id);
}

void Sound2dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound2dManager::update()
{

}

void Sound2dManager::createSound(const string& id, const string& audioPath)
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

	auto sound = make_shared<Sound2d>(id);

	_sounds.insert(make_pair(id, sound));
}

const bool Sound2dManager::isSoundExisting(const string& id) const
{
	return (_sounds.find(id) != _sounds.end());
}

const bool Sound2dManager::isSoundsExisting() const
{
	return !_sounds.empty();
}

const unordered_map<string, shared_ptr<Sound2d>>& Sound2dManager::getSounds() const
{
	return _sounds;
}

const shared_ptr<Sound2d> Sound2dManager::getSound(const string& id) const
{
	auto iterator = _sounds.find(id);

	if(iterator == _sounds.end())
	{
		abort();
	}

	return iterator->second;
}