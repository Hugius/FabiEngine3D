#include "world_editor.hpp"

void WorldEditor::_updateModelHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		auto partIds = _fe3d->model_getPartIDs(id);

		for(size_t i = 0; i < partIds.size(); i++)
		{
			auto opacity = _fe3d->model_getOpacity(id, partIds[i]);

			if((opacity == 0.0f) && (i == 0))
			{
				direction *= -1;
			}
			if((opacity == 1.0f) && (i == 0))
			{
				direction *= -1;
			}
			const float speed = (MODEL_HIGHLIGHT_SPEED * static_cast<float>(direction));
			_fe3d->model_setOpacity(id, partIds[i], (opacity + speed));
		}
	}
}

void WorldEditor::_updateQuad3dHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		auto opacity = _fe3d->quad3d_getOpacity(id);

		if(opacity == 0.0f)
		{
			direction *= -1;
		}
		if(opacity == 1.0f)
		{
			direction *= -1;
		}

		const float speed = (QUAD3D_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d->quad3d_setOpacity(id, (opacity + speed));
	}
}

void WorldEditor::_updateText3dHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		auto opacity = _fe3d->text3d_getOpacity(id);

		if(opacity == 0.0f)
		{
			direction *= -1;
		}
		if(opacity == 1.0f)
		{
			direction *= -1;
		}

		const float speed = (TEXT3D_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d->text3d_setOpacity(id, (opacity + speed));
	}
}

void WorldEditor::_updateSpeakerHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		if(_fe3d->model_getBaseSize(id).y < DEFAULT_SPEAKER_SIZE.y)
		{
			_fe3d->model_setBaseSize(id, DEFAULT_SPEAKER_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(id).y > (DEFAULT_SPEAKER_SIZE.y * SPEAKER_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(id, (DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE));
			direction *= -1;
		}

		const auto color = _fe3d->model_getBaseSize(id);
		fvec3 speed = (fvec3(SPEAKER_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_SPEAKER_SIZE * SPEAKER_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
		_fe3d->model_setBaseSize(id, (color + speed));
	}
}

void WorldEditor::_updateLampHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		if(_fe3d->model_getBaseSize(id).y < DEFAULT_LAMP_SIZE.y)
		{
			_fe3d->model_setBaseSize(id, DEFAULT_LAMP_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(id).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(id, (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d->model_getBaseSize(id);
		fvec3 speed = (fvec3(LAMP_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
		_fe3d->model_setBaseSize(id, (size + speed));
	}
}

void WorldEditor::_updateTorchHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		if(_fe3d->model_getBaseSize(id).y < DEFAULT_TORCH_SIZE.y)
		{
			_fe3d->model_setBaseSize(id, DEFAULT_TORCH_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(id).y > (DEFAULT_TORCH_SIZE.y * TORCH_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(id, (DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d->model_getBaseSize(id);
		fvec3 speed = (fvec3(TORCH_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_TORCH_SIZE * TORCH_SIZE_INCREASE) - DEFAULT_TORCH_SIZE);
		_fe3d->model_setBaseSize(id, (size + speed));
	}
}

void WorldEditor::_updateCameraHighlighting(const string& id, int& direction)
{
	if(id.empty())
	{
		direction = 1;
	}

	if(!id.empty())
	{
		if(_fe3d->model_getBaseSize(id).y < DEFAULT_CAMERA_SIZE.y)
		{
			_fe3d->model_setBaseSize(id, DEFAULT_CAMERA_SIZE);
			direction *= -1;
		}

		if(_fe3d->model_getBaseSize(id).y > (DEFAULT_CAMERA_SIZE.y * CAMERA_SIZE_INCREASE))
		{
			_fe3d->model_setBaseSize(id, (DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE));
			direction *= -1;
		}

		const auto size = _fe3d->model_getBaseSize(id);
		fvec3 speed = (fvec3(CAMERA_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
		speed *= ((DEFAULT_CAMERA_SIZE * CAMERA_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
		_fe3d->model_setBaseSize(id, (size + speed));
	}
}