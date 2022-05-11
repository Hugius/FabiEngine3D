#pragma once

#include "mathematics.hpp"
#include "pointlight_shape_type.hpp"

#include <string>

using std::string;

class Pointlight final
{
public:
	Pointlight(const string & id);

	void updateTarget();
	void setPosition(const fvec3 & value);
	void move(const fvec3 & change);
	void moveTo(const fvec3 & target, float speed);
	void setRadius(const fvec3 & value);
	void setColor(const fvec3 & value);
	void setIntensity(float value);
	void setShape(PointlightShapeType value);
	void setVisible(bool value);

	const string & getId() const;

	const fvec3 & getPosition() const;
	const fvec3 & getColor() const;
	const fvec3 & getRadius() const;

	const float getIntensity() const;

	const bool isVisible() const;

	const PointlightShapeType getShape() const;

private:
	const string _id;

	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _radius = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);

	float _positionTargetSpeed = 0.0f;
	float _intensity = 1.0f;

	bool _isVisible = true;

	PointlightShapeType _shape = PointlightShapeType::CIRCLE;
};