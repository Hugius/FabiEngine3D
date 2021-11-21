#include "shadow_generator.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

using std::max;

ShadowGenerator::ShadowGenerator(RenderBus& renderBus)
	:
	_renderBus(renderBus)
{

}

void ShadowGenerator::update()
{
	if(_renderBus.isShadowsEnabled())
	{
		if(_passedFrames >= _interval)
		{
			_passedFrames = 0;

			updateMatrix();
		}
		else
		{
			_passedFrames++;
		}
	}
}

void ShadowGenerator::updateMatrix()
{
	if(_isFollowingCamera)
	{
		// Temporary values
		auto cameraPosition = _renderBus.getCameraPosition();
		auto eyePosition = _renderBus.getShadowEyePosition();
		auto centerPosition = _renderBus.getShadowCenterPosition();

		// Update eye & center
		fvec3 newEyePosition = fvec3(cameraPosition.x, 0.0f, cameraPosition.z);
		fvec3 newCenterPosition = fvec3(cameraPosition.x, 0.0f, cameraPosition.z);
		newEyePosition += eyePosition;
		newCenterPosition += centerPosition;

		// Apply
		_renderBus.setShadowEyePosition(newEyePosition);
		_renderBus.setShadowCenterPosition(newCenterPosition);
	}

	// Create light space matrix
	_renderBus.setShadowMatrix(_createLightSpaceMatrix());
}

const mat44 ShadowGenerator::_createLightSpaceMatrix() const
{
	// Temporary values
	auto eye = _renderBus.getShadowEyePosition();
	auto center = _renderBus.getShadowCenterPosition();
	auto size = _renderBus.getShadowAreaSize();
	auto reach = _renderBus.getShadowAreaReach();

	// Matrix generation
	mat44 lightViewMatrix = Math::createViewMatrix(eye, center, fvec3(0.0f, 1.0f, 0.0f));
	mat44 lightProjectionMatrix = Math::createOrthoMatrix(-size / 2.0f, size / 2.0f, -size / 2.0f, size / 2.0f, NEAR_DISTANCE, reach);

	// Return
	return (lightProjectionMatrix * lightViewMatrix);
}

void ShadowGenerator::setInterval(unsigned int value)
{
	_interval = value;
	_passedFrames = 0;
}

void ShadowGenerator::setFollowingCamera(bool value)
{
	_isFollowingCamera = value;
}

const unsigned int ShadowGenerator::getInterval() const
{
	return _interval;
}

const bool ShadowGenerator::isFollowingCamera() const
{
	return _isFollowingCamera;
}
