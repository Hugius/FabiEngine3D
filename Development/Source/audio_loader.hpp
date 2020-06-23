#pragma once

#include <map>
#include <string>
#include <SDL\\SDL_mixer.h>

using std::string;

class AudioLoader final
{
public:
	AudioLoader() = default;
	~AudioLoader();
	
	Mix_Chunk* getChunk(const string& filePath);
	Mix_Music* getMusic(const string& filePath);

private:
	std::map<string, Mix_Chunk*> _chunkMap;
	std::map<string, Mix_Music*> _musicMap;
};