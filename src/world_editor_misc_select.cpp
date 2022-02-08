#include "world_editor.hpp"

void WorldEditor::_selectModel(const string& id)
{
	_selectedModelId = id;

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("modelId")->changeTextContent("Selected Model: " + _selectedModelId);
}

void WorldEditor::_selectQuad3d(const string& id)
{
	_selectedQuadId = id;

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("quadId")->changeTextContent("Selected Quad3D: " + _selectedQuadId);
}

void WorldEditor::_selectText3d(const string& id)
{
	_selectedTextId = id;

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("textId")->changeTextContent("Selected Text3D: " + _selectedTextId);
}

void WorldEditor::_selectSound(const string& id)
{
	_selectedSoundId = ("@@speaker_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("soundId")->changeTextContent("Selected Sound: " + _selectedSoundId);
}

void WorldEditor::_selectPointlight(const string& id)
{
	_selectedPointlightId = ("@@lamp_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
}

void WorldEditor::_selectSpotlight(const string& id)
{
	_selectedSpotlightId = ("@@torch_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
}

void WorldEditor::_selectReflection(const string& id)
{
	_selectedReflectionId = ("@@camera_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
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

void WorldEditor::_deselectSound(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_SPEAKER_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_SPEAKER_AABB_SIZE);
}

void WorldEditor::_deselectPointlight(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_LAMP_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_deselectSpotlight(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_TORCH_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_deselectReflection(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_CAMERA_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_CAMERA_AABB_SIZE);
}