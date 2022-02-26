#pragma once

#include "wave_buffer.hpp"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

class Sound2d
{
public:
	Sound2d(const string& id);

	void setWaveBuffer(shared_ptr<WaveBuffer> value);
	void setAudioPath(const string& value);

	const string& getId() const;
	const string& getAudioPath() const;

	const shared_ptr<WaveBuffer> getWaveBuffer() const;

private:
	const string _id;

	shared_ptr<WaveBuffer> _waveBuffer = nullptr;

	string _audioPath = "";
};