#include "world_editor.hpp"

void WorldEditor::_updateModelBlinking(const string& ID, int& direction)
{
	// Reset multiplier if nothing active/selected
	if(ID.empty())
	{
		direction = 1;
	}

	// Update model inversion
	if(!ID.empty())
	{
		// Update all parts
		auto partIDs = _fe3d.modelEntity_getPartIDs(ID);
		for(size_t i = 0; i < partIDs.size(); i++)
		{
			// Check if inversion reached minimum
			if((_fe3d.modelEntity_getColorInversion(ID, partIDs[i]) == 0.0f) && (i == 0))
			{
				direction *= -1;
			}

			// Check if inversion reached maximum
			if((_fe3d.modelEntity_getColorInversion(ID, partIDs[i]) == 1.0f) && (i == 0))
			{
				direction *= -1;
			}

			// Set model inversion
			const float speed = (MODEL_BLINKING_SPEED * static_cast<float>(direction));
			_fe3d.modelEntity_setColorInversion(ID, partIDs[i], (_fe3d.modelEntity_getColorInversion(ID, partIDs[i]) + speed));
		}
	}
}

void WorldEditor::_updateBillboardBlinking(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if(ID.empty())
	{
		direction = 1;
	}

	// Update billboard inversion
	if(ID != "")
	{
		// Check if inversion reached minimum
		if(_fe3d.billboardEntity_getColorInversion(ID) == 0.0f)
		{
			direction *= -1;
		}

		// Check if inversion reached maximum
		if(_fe3d.billboardEntity_getColorInversion(ID) == 1.0f)
		{
			direction *= -1;
		}

		// Set billboard inversion
		float speed = (BILLBOARD_BLINKING_SPEED * static_cast<float>(direction));
		_fe3d.billboardEntity_setColorInversion(ID, _fe3d.billboardEntity_getColorInversion(ID) + speed);
	}
}

void WorldEditor::_updateSpeakerAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if(ID.empty())
	{
		direction = 1;
	}

	// Update speaker animation
	if(ID != "")
	{
		// Check if inversion reached minimum
		if(_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_SPEAKER_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_SPEAKER_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if(_fe3d.modelEntity_getBaseSize(ID).y > (DEFAULT_SPEAKER_SIZE.y * SPEAKER_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(SPEAKER_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, (_fe3d.modelEntity_getBaseSize(ID) + modelSpeed));
	}
}

void WorldEditor::_updateLampAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if(ID.empty())
	{
		direction = 1;
	}

	// Update lamp animation
	if(ID != "")
	{
		// Check if inversion reached minimum
		if(_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_LAMP_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_LAMP_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if(_fe3d.modelEntity_getBaseSize(ID).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(LAMP_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, (_fe3d.modelEntity_getBaseSize(ID) + modelSpeed));
	}
}

void WorldEditor::_updateTorchAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if(ID.empty())
	{
		direction = 1;
	}

	// Update torch animation
	if(ID != "")
	{
		// Check if inversion reached minimum
		if(_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_TORCH_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_TORCH_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if(_fe3d.modelEntity_getBaseSize(ID).y > (DEFAULT_TORCH_SIZE.y * TORCH_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(TORCH_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE) - DEFAULT_TORCH_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, (_fe3d.modelEntity_getBaseSize(ID) + modelSpeed));
	}
}

void WorldEditor::_updateCameraAnimation(const string& ID, int& direction)
{
	// Reset direction if nothing active/selected
	if(ID.empty())
	{
		direction = 1;
	}

	// Update reflection animation
	if(ID != "")
	{
		// Check if inversion reached minimum
		if(_fe3d.modelEntity_getBaseSize(ID).y < DEFAULT_CAMERA_SIZE.y)
		{
			_fe3d.modelEntity_setBaseSize(ID, DEFAULT_CAMERA_SIZE);
			direction *= -1;
		}

		// Check if inversion reached maximum
		if(_fe3d.modelEntity_getBaseSize(ID).y > (DEFAULT_CAMERA_SIZE.y * CAMERA_SIZE_INCREASE))
		{
			_fe3d.modelEntity_setBaseSize(ID, (DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE));
			direction *= -1;
		}

		// Set new sizes
		Vec3 modelSpeed = (Vec3(CAMERA_ANIMATION_SPEED) * Vec3(static_cast<float>(direction)));
		modelSpeed *= ((DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
		_fe3d.modelEntity_setBaseSize(ID, _fe3d.modelEntity_getBaseSize(ID) + modelSpeed);
	}
}