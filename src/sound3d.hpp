#pragma once

#include "sound2d.hpp"

#include "mathematics.hpp"

class Sound3d final : public Sound2d
{
public:
	using Sound2d::Sound2d;

	// VOID
	void updateTransformation();
	void setPosition(fvec3 value);
	void move(fvec3 value);
	void moveTo(fvec3 target, float speed);
	void setMaxVolume(float value);
	void setMaxDistance(float value);

	// FVEC3
	const fvec3 getPosition() const;

	// FLOAT
	const float getMaxVolume() const;
	const float getMaxDistance() const;

private:
	// FVEC3
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);

	// FLOAT
	float _positionTargetSpeed = 0.0f;
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;
};