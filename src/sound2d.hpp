#pragma once

#include "audio.hpp"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

class Sound2d
{
public:
	Sound2d(const string& id);

	void setAudio(shared_ptr<Audio> value);
	void setAudioPath(const string& value);
	void setVolume(float value);

	const string& getId() const;
	const string& getAudioPath() const;

	const float getVolume() const;

	const shared_ptr<Audio> getAudio() const;

private:
	const string _id;

	shared_ptr<Audio> _audio = nullptr;

	string _audioPath = "";

	float _volume = 1.0f;
};