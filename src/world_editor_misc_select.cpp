#include "world_editor.hpp"

void WorldEditor::_selectModel(const string & id)
{
	_selectedModelId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Model: " + _selectedModelId);
}

void WorldEditor::_selectQuad(const string & id)
{
	_selectedQuad3dId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Quad3D: " + _selectedQuad3dId);
}

void WorldEditor::_selectText(const string & id)
{
	_selectedTextId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Text3D: " + _selectedTextId);
}

void WorldEditor::_selectPointlight(const string & id)
{
	_selectedPointlightId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Pointlight: " + _selectedPointlightId);
}

void WorldEditor::_selectSpotlight(const string & id)
{
	_selectedSpotlightId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Spotlight: " + _selectedSpotlightId);
}

void WorldEditor::_selectCaptor(const string & id)
{
	_selectedCaptorId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Captor: " + _selectedCaptorId);
}

void WorldEditor::_selectSound(const string & id)
{
	_selectedSoundId = id;

	_gui->getOverlay()->getTextField("selectedId")->setTextContent("Selected Sound: " + _selectedSoundId);
}

void WorldEditor::_deselectModel(const string & id)
{
	for(const auto & partId : _fe3d->model_getPartIds(id))
	{
		_fe3d->model_setOpacity(id, partId, 1.0f);
	}
}

void WorldEditor::_deselectQuad(const string & id)
{
	_fe3d->quad3d_setOpacity(id, 1.0f);
}

void WorldEditor::_deselectText(const string & id)
{
	_fe3d->text3d_setOpacity(id, 1.0f);
}

void WorldEditor::_deselectPointlight(const string & id)
{
	_fe3d->model_setBaseSize(("@@lamp_" + id), DEFAULT_LAMP_SIZE);
	_fe3d->aabb_setLocalSize(("@@lamp_" + id), DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_deselectSpotlight(const string & id)
{
	_fe3d->model_setBaseSize(("@@torch_" + id), DEFAULT_TORCH_SIZE);
	_fe3d->aabb_setLocalSize(("@@torch_" + id), DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_deselectCaptor(const string & id)
{
	_fe3d->model_setBaseSize(("@@camera_" + id), DEFAULT_CAMERA_SIZE);
	_fe3d->aabb_setLocalSize(("@@camera_" + id), DEFAULT_CAMERA_AABB_SIZE);
}

void WorldEditor::_deselectSound(const string & id)
{
	_fe3d->model_setBaseSize(("@@speaker_" + id), DEFAULT_SPEAKER_SIZE);
	_fe3d->aabb_setLocalSize(("@@speaker_" + id), DEFAULT_SPEAKER_AABB_SIZE);
}