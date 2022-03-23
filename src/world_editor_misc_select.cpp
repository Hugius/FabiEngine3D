#include "world_editor.hpp"

void WorldEditor::_selectModel(const string& id)
{
	_selectedModelId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Model: " + _selectedModelId);
}

void WorldEditor::_selectQuad3d(const string& id)
{
	_selectedQuadId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Quad3D: " + _selectedQuadId);
}

void WorldEditor::_selectText3d(const string& id)
{
	_selectedTextId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Text3D: " + _selectedTextId);
}

void WorldEditor::_selectPointlight(const string& id)
{
	_selectedPointlightId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Pointlight: " + _selectedPointlightId);
}

void WorldEditor::_selectSpotlight(const string& id)
{
	_selectedSpotlightId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Spotlight: " + _selectedSpotlightId);
}

void WorldEditor::_selectReflection(const string& id)
{
	_selectedReflectionId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Reflection: " + _selectedReflectionId);
}

void WorldEditor::_selectSound(const string& id)
{
	_selectedSoundId = id;

	_gui->getOverlay()->getTextField("selectedId")->changeTextContent("Selected Sound: " + _selectedSoundId);
}

void WorldEditor::_deselectModel(const string& id)
{
	for(const auto& partId : _fe3d->model_getPartIds(id))
	{
		_fe3d->model_setOpacity(id, partId, 1.0f);
	}
}

void WorldEditor::_deselectQuad3d(const string& id)
{
	_fe3d->quad3d_setOpacity(id, 1.0f);
}

void WorldEditor::_deselectText3d(const string& id)
{
	_fe3d->text3d_setOpacity(id, 1.0f);
}

void WorldEditor::_deselectPointlight(const string& id)
{
	_fe3d->model_setBaseSize(("@@lamp_" + id), DEFAULT_LAMP_SIZE);
	_fe3d->aabb_setLocalSize(("@@lamp_" + id), DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_deselectSpotlight(const string& id)
{
	_fe3d->model_setBaseSize(("@@torch_" + id), DEFAULT_TORCH_SIZE);
	_fe3d->aabb_setLocalSize(("@@torch_" + id), DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_deselectReflection(const string& id)
{
	_fe3d->model_setBaseSize(("@@camera_" + id), DEFAULT_CAMERA_SIZE);
	_fe3d->aabb_setLocalSize(("@@camera_" + id), DEFAULT_CAMERA_AABB_SIZE);
}

void WorldEditor::_deselectSound(const string& id)
{
	_fe3d->model_setBaseSize(("@@speaker_" + id), DEFAULT_SPEAKER_SIZE);
	_fe3d->aabb_setLocalSize(("@@speaker_" + id), DEFAULT_SPEAKER_AABB_SIZE);
}