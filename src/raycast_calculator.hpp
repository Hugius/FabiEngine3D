#pragma once

#include "ray.hpp"
#include "camera.hpp"

class RaycastCalculator final
{
public:
	RaycastCalculator();

	void inject(shared_ptr<Camera> camera);
	void calculateCursorRay();
	void clearCursorRay();

	const shared_ptr<Ray> getCursorRay() const;

	static const fvec3 calculatePointOnRay(shared_ptr<Ray> ray, float distance);

private:
	const fvec4 _getCoordinatesInViewSpace(const fvec4 & clipCoordinates) const;

	const fvec3 _getCoordinatesInWorldSpace(const fvec4 & viewCoordinates) const;

	shared_ptr<Ray> _cursorRay = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};