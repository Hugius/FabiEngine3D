#include "world_editor.hpp"

void WorldEditor::_updateModelHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

	auto partIds = _fe3d->model_getPartIds(id);

	for(unsigned int index = 0; index < static_cast<unsigned int>(partIds.size()); index++)
	{
		auto opacity = _fe3d->model_getOpacity(id, partIds[index]);

		if((opacity == 0.0f) && (index == 0))
		{
			direction *= -1;
		}
		if((opacity == 1.0f) && (index == 0))
		{
			direction *= -1;
		}
		const float speed = (MODEL_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d->model_setOpacity(id, partIds[index], (opacity + speed));
	}
}

void WorldEditor::_updateQuad3dHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

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

void WorldEditor::_updateText3dHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

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

void WorldEditor::_updateSoundHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

	if(_fe3d->model_getBaseSize("@@speaker_" + id).y < DEFAULT_SPEAKER_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@speaker_" + id), DEFAULT_SPEAKER_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@speaker_" + id).y > (DEFAULT_SPEAKER_SIZE.y * SOUND_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@speaker_" + id), (DEFAULT_SPEAKER_SIZE * SOUND_SIZE_INCREASE));
		direction *= -1;
	}

	const auto color = _fe3d->model_getBaseSize("@@speaker_" + id);
	fvec3 speed = (fvec3(SOUND_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_SPEAKER_SIZE * SOUND_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
	_fe3d->model_setBaseSize(("@@speaker_" + id), (color + speed));
}

void WorldEditor::_updatePointlightHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

	if(_fe3d->model_getBaseSize("@@lamp_" + id).y < DEFAULT_LAMP_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@lamp_" + id), DEFAULT_LAMP_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@lamp_" + id).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@lamp_" + id), (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@lamp_" + id);
	fvec3 speed = (fvec3(LAMP_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
	_fe3d->model_setBaseSize(("@@lamp_" + id), (size + speed));
}

void WorldEditor::_updateSpotlightHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

	if(_fe3d->model_getBaseSize("@@torch_" + id).y < DEFAULT_TORCH_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@torch_" + id), DEFAULT_TORCH_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@torch_" + id).y > (DEFAULT_TORCH_SIZE.y * SPOTLIGHT_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@torch_" + id), (DEFAULT_TORCH_SIZE * SPOTLIGHT_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@torch_" + id);
	fvec3 speed = (fvec3(SPOTLIGHT_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_TORCH_SIZE * SPOTLIGHT_SIZE_INCREASE) - DEFAULT_TORCH_SIZE);
	_fe3d->model_setBaseSize(("@@torch_" + id), (size + speed));
}

void WorldEditor::_updateReflectionHighlighting(const string & id, int & direction)
{
	if(id.empty())
	{
		direction = 1;
		return;
	}

	if(_fe3d->model_getBaseSize("@@camera_" + id).y < DEFAULT_CAMERA_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@camera_" + id), DEFAULT_CAMERA_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@camera_" + id).y > (DEFAULT_CAMERA_SIZE.y * REFLECTION_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@camera_" + id), (DEFAULT_CAMERA_SIZE * REFLECTION_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@camera_" + id);
	fvec3 speed = (fvec3(REFLECTION_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_CAMERA_SIZE * REFLECTION_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
	_fe3d->model_setBaseSize(("@@camera_" + id), (size + speed));
}