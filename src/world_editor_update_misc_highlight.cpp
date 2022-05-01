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

void WorldEditor::_updateSound3dHighlighting(const string & sound3dId, int & direction)
{
	if(sound3dId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@sound3d_" + sound3dId).y < DEFAULT_SOUND3D_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@sound3d_" + sound3dId), DEFAULT_SOUND3D_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@sound3d_" + sound3dId).y > (DEFAULT_SOUND3D_SIZE.y * SOUND3D_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@sound3d_" + sound3dId), (DEFAULT_SOUND3D_SIZE * SOUND3D_SIZE_INCREASE));
		direction *= -1;
	}

	const auto color = _fe3d->model_getBaseSize("@@sound3d_" + sound3dId);
	fvec3 speed = (fvec3(SOUND3D_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_SOUND3D_SIZE * SOUND3D_SIZE_INCREASE) - DEFAULT_SOUND3D_SIZE);
	_fe3d->model_setBaseSize(("@@sound3d_" + sound3dId), (color + speed));
}

void WorldEditor::_updatePointlightHighlighting(const string & pointlightId, int & direction)
{
	if(pointlightId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@pointlight_" + pointlightId).y < DEFAULT_POINTLIGHT_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@pointlight_" + pointlightId), DEFAULT_POINTLIGHT_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@pointlight_" + pointlightId).y > (DEFAULT_POINTLIGHT_SIZE.y * POINTLIGHT_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@pointlight_" + pointlightId), (DEFAULT_POINTLIGHT_SIZE * POINTLIGHT_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@pointlight_" + pointlightId);
	fvec3 speed = (fvec3(POINTLIGHT_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_POINTLIGHT_SIZE * POINTLIGHT_SIZE_INCREASE) - DEFAULT_POINTLIGHT_SIZE);
	_fe3d->model_setBaseSize(("@@pointlight_" + pointlightId), (size + speed));
}

void WorldEditor::_updateSpotlightHighlighting(const string & spotlightId, int & direction)
{
	if(spotlightId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@spotlight_" + spotlightId).y < DEFAULT_SPOTLIGHT_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@spotlight_" + spotlightId), DEFAULT_SPOTLIGHT_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@spotlight_" + spotlightId).y > (DEFAULT_SPOTLIGHT_SIZE.y * SPOTLIGHT_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@spotlight_" + spotlightId), (DEFAULT_SPOTLIGHT_SIZE * SPOTLIGHT_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@spotlight_" + spotlightId);
	fvec3 speed = (fvec3(SPOTLIGHT_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_SPOTLIGHT_SIZE * SPOTLIGHT_SIZE_INCREASE) - DEFAULT_SPOTLIGHT_SIZE);
	_fe3d->model_setBaseSize(("@@spotlight_" + spotlightId), (size + speed));
}

void WorldEditor::_updateCaptorHighlighting(const string & captorId, int & direction)
{
	if(captorId.empty())
	{
		direction = 1;

		return;
	}

	if(_fe3d->model_getBaseSize("@@captor_" + captorId).y < DEFAULT_CAPTOR_SIZE.y)
	{
		_fe3d->model_setBaseSize(("@@captor_" + captorId), DEFAULT_CAPTOR_SIZE);
		direction *= -1;
	}

	if(_fe3d->model_getBaseSize("@@captor_" + captorId).y > (DEFAULT_CAPTOR_SIZE.y * CAPTOR_SIZE_INCREASE))
	{
		_fe3d->model_setBaseSize(("@@captor_" + captorId), (DEFAULT_CAPTOR_SIZE * CAPTOR_SIZE_INCREASE));
		direction *= -1;
	}

	const auto size = _fe3d->model_getBaseSize("@@captor_" + captorId);
	fvec3 speed = (fvec3(CAPTOR_HIGHLIGHT_SPEED) * fvec3(static_cast<float>(direction)));
	speed *= ((DEFAULT_CAPTOR_SIZE * CAPTOR_SIZE_INCREASE) - DEFAULT_CAPTOR_SIZE);
	_fe3d->model_setBaseSize(("@@captor_" + captorId), (size + speed));
}