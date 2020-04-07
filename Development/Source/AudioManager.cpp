#include <algorithm>

#include <WE3D/AudioManager.hpp>
#include <WE3D/Logger.hpp>

AudioManager::AudioManager(AudioLoader& audioLoader) :
	p_audioLoader(audioLoader)
{

}

void AudioManager::deleteAllMusic()
{
	p_musicList.clear();
}

void AudioManager::deleteAllChunks()
{
	p_chunks.clear();
}

void AudioManager::addMusic(const string& fileName)
{
	p_musicList.push_back(AudioMusic(p_audioLoader.getMusic("../Game/Audio/" + fileName)));
}

void AudioManager::removeMusic()
{
	p_musicList.clear();
}

void AudioManager::addGlobalChunk(const std::string& ID, const std::string& fileName)
{
	p_checkValidAdd(ID);
	p_chunks.push_back(AudioChunk(ID, p_audioLoader.getChunk("../Game/Audio/" + fileName)));
}

void AudioManager::addPointChunk(const std::string& ID, const std::string& fileName, vec3 position, float maxDistance)
{
	p_checkValidAdd(ID);
	p_chunks.push_back(AudioChunk(ID, p_audioLoader.getChunk("../Game/Audio/" + fileName), position, maxDistance));
}

void AudioManager::removeChunk(const std::string& ID)
{
	auto index = p_findIndex(ID);

	if (index == -1) // Does not exist
	{
		Logger::getInst().throwError("Tried to remove nonexisting audio chunk with ID \'", ID, "\'!");
	}
	else // Remove chunk
	{
		p_chunks.erase(p_chunks.begin() + index);
	}
}

bool AudioManager::isChunkExisting(const string& ID)
{
	return p_findIndex(ID) != -1;
}

AudioChunk& AudioManager::getChunk(const std::string& ID)
{
	auto index = p_findIndex(ID);

	if (index == -1)
	{
		Logger::getInst().throwError("Tried to get nonexisting audio chunk with ID \'", ID, "\'!");
	}
	else
	{
		return p_chunks[index];
	}
}

std::vector<AudioChunk>& AudioManager::getChunks()
{
	return p_chunks;
}

std::vector<AudioMusic>& AudioManager::getMusic()
{
	return p_musicList;
}

void AudioManager::p_checkValidAdd(const std::string& ID)
{
	if (p_findIndex(ID) != -1) // Already exists
	{
		Logger::getInst().throwError("Audio chunk with ID \'", ID, "\' already exists!");
	}
	else if (ID == "") // Empty ID
	{
		Logger::getInst().throwError("Tried to create audio chunk with empty ID!");
	}
}

int AudioManager::p_findIndex(const std::string& ID)
{
	for (size_t i = 0; i < p_chunks.size(); i++)
	{
		if (p_chunks[i].getID() == ID)
		{
			return i;
		}
	}

	return -1;
}