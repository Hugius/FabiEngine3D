#pragma once

#include "sound2d.hpp"

#include "mathematics.hpp"

class Sound3d final : public Sound2d
{
public:
	using Sound2d::Sound2d;

	void updateTarget();
	void setPosition(const fvec3 & value);
	void move(const fvec3 & value);
	void moveTo(const fvec3 & target, float speed);
	void setMaxVolume(float value);
	void setMaxDistance(float value);

	const fvec3 & getPosition() const;

	const float getMaxVolume() const;
	const float getMaxDistance() const;

private:
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);

	float _positionTargetSpeed = 0.0f;
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;
};