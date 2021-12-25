#include "world_editor.hpp"

void WorldEditor::_updateModelHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		auto partIDs = _fe3d.model_getPartIDs(ID);
		for(size_t i = 0; i < partIDs.size(); i++)
		{
			if((_fe3d.model_getWireframeColor(ID, partIDs[i]) == 0.0f) && (i == 0))
			{
				direction *= -1;
			}

			if((_fe3d.model_getWireframeColor(ID, partIDs[i]) == 1.0f) && (i == 0))
			{
				direction *= -1;
			}

			const auto color = _fe3d.model_getWireframeColor(ID, partIDs[i]);
			const float speed = (MODEL_HIGHLIGHT_SPEED * static_cast<float>(direction));
			_fe3d.model_setWireframeColor(ID, partIDs[i], (color + speed));
		}
	}
}

void WorldEditor::_updateBillboardHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		if(_fe3d.billboard_getWireframeColor(ID) == 0.0f)
		{
			direction *= -1;
		}

		if(_fe3d.billboard_getWireframeColor(ID) == 1.0f)
		{
			direction *= -1;
		}

		const auto color = _fe3d.billboard_getWireframeColor(ID);
		const float speed = (BILLBOARD_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d.billboard_setWireframeColor(ID, (color + speed));
	}
}

void WorldEditor::_updateSpeakerHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		if(_fe3d.model_getBaseSize(ID).y < DEFAULT_SPEAKER_SIZE.y)
		{
			_fe3d.model_setBaseSize(ID, DEFAULT_SPEAKER_SIZE);
			direction *= -1;
		}

		if(_fe3d.model_getBaseSize(ID).y > (DEFAULT_SPEAKER_SIZE.y * SPEAKER_SIZE_INCREASE))
		{
			_fe3d.model_setBaseSize(ID, (DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE));
			direction *= -1;
		}

		const auto color = _fe3d.model_getBaseSize(ID);
		fvec3 speed = (fvec3(SPEAKER_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
		_fe3d.model_setBaseSize(ID, (color + speed));
	}
}

void WorldEditor::_updateLampHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		if(_fe3d.model_getBaseSize(ID).y < DEFAULT_LAMP_SIZE.y)
		{
			_fe3d.model_setBaseSize(ID, DEFAULT_LAMP_SIZE);
			direction *= -1;
		}

		if(_fe3d.model_getBaseSize(ID).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
		{
			_fe3d.model_setBaseSize(ID, (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d.model_getBaseSize(ID);
		fvec3 speed = (fvec3(LAMP_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
		_fe3d.model_setBaseSize(ID, (size + speed));
	}
}

void WorldEditor::_updateTorchHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		if(_fe3d.model_getBaseSize(ID).y < DEFAULT_TORCH_SIZE.y)
		{
			_fe3d.model_setBaseSize(ID, DEFAULT_TORCH_SIZE);
			direction *= -1;
		}

		if(_fe3d.model_getBaseSize(ID).y > (DEFAULT_TORCH_SIZE.y * TORCH_SIZE_INCREASE))
		{
			_fe3d.model_setBaseSize(ID, (DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d.model_getBaseSize(ID);
		fvec3 speed = (fvec3(TORCH_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE) - DEFAULT_TORCH_SIZE);
		_fe3d.model_setBaseSize(ID, (size + speed));
	}
}

void WorldEditor::_updateCameraHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		if(_fe3d.model_getBaseSize(ID).y < DEFAULT_CAMERA_SIZE.y)
		{
			_fe3d.model_setBaseSize(ID, DEFAULT_CAMERA_SIZE);
			direction *= -1;
		}

		if(_fe3d.model_getBaseSize(ID).y > (DEFAULT_CAMERA_SIZE.y * CAMERA_SIZE_INCREASE))
		{
			_fe3d.model_setBaseSize(ID, (DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d.model_getBaseSize(ID);
		fvec3 speed = (fvec3(CAMERA_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
		_fe3d.model_setBaseSize(ID, (size + speed));
	}
}