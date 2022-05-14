#include "raycast_calculator.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

using std::make_shared;

RaycastCalculator::RaycastCalculator()
{
	_cursorRay = make_shared<Ray>(fvec3(0.0f), fvec3(0.0f));
}

void RaycastCalculator::update()
{
	_cursorRay = _calculateCursorRay();
}

void RaycastCalculator::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const shared_ptr<Ray> RaycastCalculator::getCursorRay() const
{
	return _cursorRay;
}

const shared_ptr<Ray> RaycastCalculator::_calculateCursorRay() const
{
	const auto ndcCoords = Tools::convertPositionRelativeFromDisplay(Tools::convertToNdc(Tools::getCursorPosition()));
	const auto clipSpaceCoords = fvec4(ndcCoords.x, ndcCoords.y, -1.0f, 1.0f);
	const auto viewSpaceCoords = _convertToViewSpace(clipSpaceCoords);
	const auto worldSpaceCoords = _convertToWorldSpace(viewSpaceCoords);

	return make_shared<Ray>(_camera->getPosition(), Mathematics::normalize(worldSpaceCoords));
}

const fvec4 RaycastCalculator::_convertToViewSpace(const fvec4 & clipCoords) const
{
	const auto invertedProjection = Mathematics::invertMatrix(_camera->getProjection());
	const auto viewCoords = (invertedProjection * clipCoords);

	return fvec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

const fvec3 RaycastCalculator::_convertToWorldSpace(const fvec4 & viewCoords) const
{
	const auto invertedView = Mathematics::invertMatrix(_camera->getView());
	const auto worldCoords = (invertedView * viewCoords);

	return fvec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

const fvec3 RaycastCalculator::calculatePointOnRay(const shared_ptr<Ray> ray, float distance) const
{
	return (ray->getPosition() + (ray->getDirection() * distance));
}