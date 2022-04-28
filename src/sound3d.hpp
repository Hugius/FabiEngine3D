#pragma once

#include "wave_buffer.hpp"
#include "mathematics.hpp"

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

class Sound3d final
{
public:
	Sound3d(const string & id);

	void updateTarget();
	void setWaveBuffer(shared_ptr<WaveBuffer> value);
	void setAudioPath(const string & value);
	void setPosition(const fvec3 & value);
	void move(const fvec3 & change);
	void moveTo(const fvec3 & target, float speed);
	void setMaxVolume(float value);
	void setMaxDistance(float value);

	const shared_ptr<WaveBuffer> getWaveBuffer() const;

	const string & getId() const;
	const string & getAudioPath() const;

	const fvec3 & getPosition() const;

	const float getMaxVolume() const;
	const float getMaxDistance() const;

private:
	const string _id;

	shared_ptr<WaveBuffer> _waveBuffer = nullptr;

	string _audioPath = "";

	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);

	float _positionTargetSpeed = 0.0f;
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;
};