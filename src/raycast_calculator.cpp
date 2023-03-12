#include "raycast_calculator.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

using std::make_shared;

RaycastCalculator::RaycastCalculator()
{
	clearCursorRay();
}

void RaycastCalculator::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const shared_ptr<Ray> RaycastCalculator::getCursorRay() const
{
	return _cursorRay;
}

void RaycastCalculator::calculateCursorRay()
{
	_camera->calculateMatrices();

	const auto ndcCoordinates = Tools::convertPositionRelativeFromDisplay(Tools::convertToNdc(Tools::getCursorPosition()));
	const auto clipSpaceCoordinates = fvec4(ndcCoordinates.x, ndcCoordinates.y, -1.0f, 1.0f);
	const auto viewSpaceCoordinates = _getCoordinatesInViewSpace(clipSpaceCoordinates);
	const auto worldSpaceCoordinates = _getCoordinatesInWorldSpace(viewSpaceCoordinates);

	_cursorRay = make_shared<Ray>(_camera->getPosition(), Mathematics::normalize(worldSpaceCoordinates));
}

void RaycastCalculator::clearCursorRay()
{
	_cursorRay = make_shared<Ray>(fvec3(0.0f), fvec3(0.0f));
}

const fvec4 RaycastCalculator::_getCoordinatesInViewSpace(const fvec4 & clipCoordinates) const
{
	const auto invertedProjection = Mathematics::invertMatrix(_camera->getProjection());
	const auto viewCoordinates = (invertedProjection * clipCoordinates);

	return fvec4(viewCoordinates.x, viewCoordinates.y, -1.0f, 0.0f);
}

const fvec3 RaycastCalculator::_getCoordinatesInWorldSpace(const fvec4 & viewCoordinates) const
{
	const auto invertedView = Mathematics::invertMatrix(_camera->getView());
	const auto worldCoordinates = (invertedView * viewCoordinates);

	return fvec3(worldCoordinates.x, worldCoordinates.y, worldCoordinates.z);
}

const fvec3 RaycastCalculator::calculatePointOnRay(shared_ptr<Ray> ray, float distance)
{
	return (ray->getPosition() + (ray->getDirection() * distance));
}