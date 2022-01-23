#include "world_editor.hpp"

void WorldEditor::_updateModelHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		auto partIDs = _fe3d->model_getPartIDs(ID);

		for(size_t i = 0; i < partIDs.size(); i++)
		{
			auto opacity = _fe3d->model_getOpacity(ID, partIDs[i]);

			if((opacity == 0.0f) && (i == 0))
			{
				direction *= -1;
			}
			if((opacity == 1.0f) && (i == 0))
			{
				direction *= -1;
			}
			const float speed = (MODEL_HIGHLIGHT_SPEED * static_cast<float>(direction));
			_fe3d->model_setOpacity(ID, partIDs[i], (opacity + speed));
		}
	}
}

void WorldEditor::_updateQuad3dHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		auto opacity = _fe3d->quad3d_getOpacity(ID);

		if(opacity == 0.0f)
		{
			direction *= -1;
		}
		if(opacity == 1.0f)
		{
			direction *= -1;
		}

		const float speed = (QUAD3D_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d->quad3d_setOpacity(ID, (opacity + speed));
	}
}

void WorldEditor::_updateText3dHighlighting(const string& ID, int& direction)
{
	if(ID.empty())
	{
		direction = 1;
	}

	if(!ID.empty())
	{
		auto opacity = _fe3d->text3d_getOpacity(ID);

		if(opacity == 0.0f)
		{
			direction *= -1;
		}
		if(opacity == 1.0f)
		{
			direction *= -1;
		}

		const float speed = (TEXT3D_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d->text3d_setOpacity(ID, (opacity + speed));
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
		if(_fe3d->model_getBaseSize(ID).y < DEFAULT_SPEAKER_SIZE.y)
		{
			_fe3d->model_setBaseSize(ID, DEFAULT_SPEAKER_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(ID).y > (DEFAULT_SPEAKER_SIZE.y * SPEAKER_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(ID, (DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE));
			direction *= -1;
		}

		const auto color = _fe3d->model_getBaseSize(ID);
		fvec3 speed = (fvec3(SPEAKER_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
		_fe3d->model_setBaseSize(ID, (color + speed));
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
		if(_fe3d->model_getBaseSize(ID).y < DEFAULT_LAMP_SIZE.y)
		{
			_fe3d->model_setBaseSize(ID, DEFAULT_LAMP_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(ID).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(ID, (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d->model_getBaseSize(ID);
		fvec3 speed = (fvec3(LAMP_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
		_fe3d->model_setBaseSize(ID, (size + speed));
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
		if(_fe3d->model_getBaseSize(ID).y < DEFAULT_TORCH_SIZE.y)
		{
			_fe3d->model_setBaseSize(ID, DEFAULT_TORCH_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(ID).y > (DEFAULT_TORCH_SIZE.y * TORCH_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(ID, (DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d->model_getBaseSize(ID);
		fvec3 speed = (fvec3(TORCH_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE) - DEFAULT_TORCH_SIZE);
		_fe3d->model_setBaseSize(ID, (size + speed));
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
		if(_fe3d->model_getBaseSize(ID).y < DEFAULT_CAMERA_SIZE.y)
		{
			_fe3d->model_setBaseSize(ID, DEFAULT_CAMERA_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(ID).y > (DEFAULT_CAMERA_SIZE.y * CAMERA_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(ID, (DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d->model_getBaseSize(ID);
		fvec3 speed = (fvec3(CAMERA_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
		_fe3d->model_setBaseSize(ID, (size + speed));
	}
}