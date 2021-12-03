#pragma once

#include "sound_2d.hpp"

#include "mathematics.hpp"

class Sound3D final : public Sound2D
{
public:
	using Sound2D::Sound2D;

	// VOID
	void setPosition(fvec3 value);
	void move(fvec3 value);
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

	// FLOAT
	float _maxVolume = 0.0f;
	float _maxDistance = 0.0f;
};