#include "world_editor.hpp"

void WorldEditor::_updateModelHighlighting(const string & modelId, int & direction)
{
	if(modelId.empty())
	{
		direction = 1;

		return;
	}

	auto partIds = _fe3d->model_getPartIds(modelId);

	for(int index = 0; index < static_cast<int>(partIds.size()); index++)
	{
		auto opacity = _fe3d->model_getOpacity(modelId, partIds[index]);

		if((opacity == 0.0f) && (index == 0))
		{
			direction *= -1;
		}
		if((opacity == 1.0f) && (index == 0))
		{
			direction *= -1;
		}
		const float speed = (MODEL_HIGHLIGHT_SPEED * static_cast<float>(direction));
		_fe3d->model_setOpacity(modelId, partIds[index], (opacity + speed));
	}
}

void WorldEditor::_updateQuad3dHighlighting(const string & quad3dId, int & direction)
{
	if(quad3dId.empty())
	{
		direction = 1;

		return;
	}

	auto opacity = _fe3d->quad3d_getOpacity(quad3dId);

	if(opacity == 0.0f)
	{
		direction *= -1;
	}
	if(opacity == 1.0f)
	{
		direction *= -1;
	}

	const float speed = (QUAD3D_HIGHLIGHT_SPEED * static_cast<float>(direction));
	_fe3d->quad3d_setOpacity(quad3dId, (opacity + speed));
}

void WorldEditor::_updateText3dHighlighting(const string & text3dId, int & direction)
{
	if(text3dId.empty())
	{
		direction = 1;

		return;
	}

	auto opacity = _fe3d->text3d_getOpacity(text3dId);

	if(opacity == 0.0f)
	{
		direction *= -1;
	}
	if(opacity == 1.0f)
	{
		direction *= -1;
	}

	const float speed = (TEXT3D_HIGHLIGHT_SPEED * static_cast<float>(direction));
	_fe3d->text3d_setOpacity(text3dId, (opacity + speed));
}

void WorldEditor::_updateSoundHighlighting(const string & soundId, int & direction)
{
	if(soundId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@speaker_" + soundId).y < DEFAULT_SPEAKER_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@speaker_" + soundId), DEFAULT_SPEAKER_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@speaker_" + soundId).y > (DEFAULT_SPEAKER_SIZE.y * SOUND_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@speaker_" + soundId), (DEFAULT_SPEAKER_SIZE * SOUND_SIZE_INCREASE));
		direction *= -1;
	}

	const auto color = _fe3d->model_getBaseSize("@@speaker_" + soundId);
	fvec3 speed = (fvec3(SOUND_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_SPEAKER_SIZE * SOUND_SIZE_INCREASE) - DEFAULT_SPEAKER_SIZE);
	_fe3d->model_setBaseSize(("@@speaker_" + soundId), (color + speed));
}

void WorldEditor::_updatePointlightHighlighting(const string & pointlightId, int & direction)
{
	if(pointlightId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@lamp_" + pointlightId).y < DEFAULT_LAMP_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@lamp_" + pointlightId), DEFAULT_LAMP_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@lamp_" + pointlightId).y > (DEFAULT_LAMP_SIZE.y * LAMP_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@lamp_" + pointlightId), (DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@lamp_" + pointlightId);
	fvec3 speed = (fvec3(LAMP_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_LAMP_SIZE * LAMP_SIZE_INCREASE) - DEFAULT_LAMP_SIZE);
	_fe3d->model_setBaseSize(("@@lamp_" + pointlightId), (size + speed));
}

void WorldEditor::_updateSpotlightHighlighting(const string & spotlightId, int & direction)
{
	if(spotlightId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@torch_" + spotlightId).y < DEFAULT_TORCH_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@torch_" + spotlightId), DEFAULT_TORCH_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@torch_" + spotlightId).y > (DEFAULT_TORCH_SIZE.y * SPOTLIGHT_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@torch_" + spotlightId), (DEFAULT_TORCH_SIZE * SPOTLIGHT_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@torch_" + spotlightId);
	fvec3 speed = (fvec3(SPOTLIGHT_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_TORCH_SIZE * SPOTLIGHT_SIZE_INCREASE) - DEFAULT_TORCH_SIZE);
	_fe3d->model_setBaseSize(("@@torch_" + spotlightId), (size + speed));
}

void WorldEditor::_updateCaptorHighlighting(const string & captorId, int & direction)
{
	if(captorId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@camera_" + captorId).y < DEFAULT_CAMERA_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@camera_" + captorId), DEFAULT_CAMERA_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@camera_" + captorId).y > (DEFAULT_CAMERA_SIZE.y * CAPTOR_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@camera_" + captorId), (DEFAULT_CAMERA_SIZE * CAPTOR_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@camera_" + captorId);
	fvec3 speed = (fvec3(CAPTOR_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_CAMERA_SIZE * CAPTOR_SIZE_INCREASE) - DEFAULT_CAMERA_SIZE);
	_fe3d->model_setBaseSize(("@@camera_" + captorId), (size + speed));
}