#include "world_editor.hpp"

void WorldEditor::_selectModel(const string & modelId)
{
	_selectedModelId = modelId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Model: " + _selectedModelId);
}

void WorldEditor::_selectQuad3d(const string & quad3dId)
{
	_selectedQuad3dId = quad3dId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Quad3D: " + _selectedQuad3dId);
}

void WorldEditor::_selectText3d(const string & text3dId)
{
	_selectedText3dId = text3dId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Text3D: " + _selectedText3dId);
}

void WorldEditor::_selectPointlight(const string & pointlightId)
{
	_selectedPointlightId = pointlightId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Pointlight: " + _selectedPointlightId);
}

void WorldEditor::_selectSpotlight(const string & spotlightId)
{
	_selectedSpotlightId = spotlightId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Spotlight: " + _selectedSpotlightId);
}

void WorldEditor::_selectCaptor(const string & captorId)
{
	_selectedCaptorId = captorId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Captor: " + _selectedCaptorId);
}

void WorldEditor::_selectSound(const string & soundId)
{
	_selectedSoundId = soundId;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Sound: " + _selectedSoundId);
}

void WorldEditor::_deselectModel(const string & modelId)
{
	for(const auto & partId : _fe3d->model_getPartIds(modelId))
	{
		_fe3d->model_setOpacity(modelId, partId, 1.0f);
	}
}

void WorldEditor::_deselectQuad3d(const string & quad3dId)
{
	_fe3d->quad3d_setOpacity(quad3dId, 1.0f);
}

void WorldEditor::_deselectText3d(const string & text3dId)
{
	_fe3d->text3d_setOpacity(text3dId, 1.0f);
}

void WorldEditor::_deselectPointlight(const string & pointlightId)
{
	_fe3d->model_setBaseSize(("@@lamp_" + pointlightId), DEFAULT_LAMP_SIZE);
	_fe3d->aabb_setLocalSize(("@@lamp_" + pointlightId), DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_deselectSpotlight(const string & spotlightId)
{
	_fe3d->model_setBaseSize(("@@torch_" + spotlightId), DEFAULT_TORCH_SIZE);
	_fe3d->aabb_setLocalSize(("@@torch_" + spotlightId), DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_deselectCaptor(const string & captorId)
{
	_fe3d->model_setBaseSize(("@@camera_" + captorId), DEFAULT_CAMERA_SIZE);
	_fe3d->aabb_setLocalSize(("@@camera_" + captorId), DEFAULT_CAMERA_AABB_SIZE);
}

void WorldEditor::_deselectSound(const string & soundId)
{
	_fe3d->model_setBaseSize(("@@speaker_" + soundId), DEFAULT_SPEAKER_SIZE);
	_fe3d->aabb_setLocalSize(("@@speaker_" + soundId), DEFAULT_SPEAKER_AABB_SIZE);
}