#pragma once

#include "ray.hpp"
#include "camera.hpp"

class RaycastCalculator final
{
public:
	RaycastCalculator();

	void inject(shared_ptr<Camera> camera);
	void update(const ivec2& cursorPosition);

	const fvec3 calculatePointOnRay(const shared_ptr<Ray> ray, float distance) const;

	const shared_ptr<Ray> getCursorRay() const;

private:
	const fvec4 _convertToViewSpace(const fvec4& clipCoords) const;

	const fvec3 _convertToWorldSpace(const fvec4& viewCoords) const;

	const shared_ptr<Ray> _calculateCursorRay(const ivec2& cursorPosition) const;

	shared_ptr<Ray> _cursorRay = nullptr;

	shared_ptr<Camera> _camera = nullptr;
};