#include "raycast_calculator.hpp"
#include "render_storage.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

using std::make_shared;

RaycastCalculator::RaycastCalculator()
{
	_cursorRay = make_shared<Ray>(fvec3(0.0f), fvec3(0.0f));
}

void RaycastCalculator::update(const ivec2& cursorPosition)
{
	_cursorRay = _calculateCursorRay(cursorPosition);
}

void RaycastCalculator::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void RaycastCalculator::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const shared_ptr<Ray> RaycastCalculator::getCursorRay() const
{
	return _cursorRay;
}

const shared_ptr<Ray> RaycastCalculator::_calculateCursorRay(const ivec2& cursorPosition) const
{
	fvec2 screenCoords = Tools::convertFromScreenCoords(cursorPosition);
	fvec2 ndcCoords = Math::convertToNdc(screenCoords);
	fvec4 clipCoords = fvec4(ndcCoords.x, ndcCoords.y, -1.0f, 1.0f);
	fvec4 viewCoords = _convertToViewSpace(clipCoords);
	fvec3 worldCoords = _convertToWorldSpace(viewCoords);

	return make_shared<Ray>(_camera->getPosition(), Math::normalize(worldCoords));
}

const fvec4 RaycastCalculator::_convertToViewSpace(const fvec4& clipCoords) const
{
	auto invertedProjection = Math::invertMatrix(_camera->getProjection());
	auto viewCoords = (invertedProjection * clipCoords);

	return fvec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

const fvec3 RaycastCalculator::_convertToWorldSpace(const fvec4& viewCoords) const
{
	auto invertedView = Math::invertMatrix(_camera->getView());
	auto worldCoords = (invertedView * viewCoords);

	return fvec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

const fvec3 RaycastCalculator::calculatePointOnRay(const shared_ptr<Ray> ray, float distance) const
{
	return (ray->getPosition() + (ray->getDirection() * distance));
}