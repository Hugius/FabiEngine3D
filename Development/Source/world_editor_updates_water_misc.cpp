#include "world_editor.hpp"

void WorldEditor::_updateWaterEditor()
{
	if (_currentWorldPart == WorldPart::WATER)
	{
		_updateWaterMenuMain();
		_updateWaterMenuChoice();
		_updateWaterMenuMesh();
		_updateWaterMenuEffects();
		_updateWaterMenuOptions();
		_updateWaterCreation();
		_updateWaterChoosing();
		_updateWaterRemoval();
		_updateWaterCamera();
	}
}

void WorldEditor::_updateWaterCreation()
{

}

void WorldEditor::_updateWaterChoosing()
{

}

void WorldEditor::_updateWaterRemoval()
{

}

void WorldEditor::_updateWaterCamera()
{
	if (_isLoaded && _currentWaterID != "")
	{
		if (_fe3d.waterEntity_isExisting(_currentWaterID))
		{
			// Get scroll wheel input
			if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
			{
				float rotationAcceleration = float(_fe3d.input_getMouseWheelY()) / _scrollWheelDivider;
				_cameraRotationSpeed += rotationAcceleration;
			}

			// Apply camera smoothing & rotation
			_cameraRotationSpeed *= 0.975f;
			_totalCameraRotation += _cameraRotationSpeed;

			// Calculate new camera position
			vec3 waterPosition = _fe3d.waterEntity_getPosition(_currentWaterID);
			float waterSize = _fe3d.waterEntity_getSize(_currentWaterID);
			float x = waterPosition.x + (waterSize / 2.0f) * sin(_totalCameraRotation);
			float y = waterPosition.y + (waterPosition.y + (waterSize / 16.0f));
			float z = waterPosition.z + (waterSize / 2.0f) * cos(_totalCameraRotation);

			// Update camera position
			_fe3d.camera_setPosition(vec3(x, y, z));
			_fe3d.camera_enableLookat(waterPosition);
		}
	}
}