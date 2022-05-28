#pragma once

#include "mathematics.hpp"

#include <string>

using std::string;

class Spotlight final
{
public:
	Spotlight(const string & id);

	void updateTarget();
	void updateFront();
	void setPosition(const fvec3 & value);
	void move(const fvec3 & change);
	void moveTo(const fvec3 & target, float speed);
	void setColor(const fvec3 & value);
	void setYaw(float value);
	void setPitch(float value);
	void setIntensity(float value);
	void setAngle(float value);
	void setDistance(float value);
	void setVisible(bool value);

	const string & getId() const;

	const fvec3 & getPosition() const;
	const fvec3 & getFront() const;
	const fvec3 & getColor() const;

	const float getYaw() const;
	const float getPitch() const;
	const float getIntensity() const;
	const float getAngle() const;
	const float getDistance() const;

	const bool isVisible() const;

private:
	const string _id;

	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _front = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);

	float _positionTargetSpeed = 0.0f;
	float _yaw = 0.0f;
	float _pitch = 0.0f;
	float _intensity = 1.0f;
	float _angle = 0.0f;
	float _distance = 0.0f;

	bool _isVisible = true;
};