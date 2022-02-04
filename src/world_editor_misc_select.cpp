#include "world_editor.hpp"

void WorldEditor::_selectModel(const string& id)
{
	_selectedModelId = id;

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	if(_activeModelId.empty() && _activeQuadId.empty() && _activeSpeakerId.empty() && _activeLampId.empty() && _activeCameraId.empty())
	{
		string tempId = _selectedModelId;
		reverse(tempId.begin(), tempId.end());
		string rawId = tempId.substr(tempId.find('_') + 1);
		reverse(rawId.begin(), rawId.end());
		_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), true);
		_gui->getOverlay()->getTextField("modelId")->changeTextContent("Selected model: " + rawId);
	}
}

void WorldEditor::_selectQuad3d(const string& id)
{
	_selectedQuadId = id;

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	if(_activeModelId.empty() && _activeQuadId.empty() && _activeSpeakerId.empty() && _activeLampId.empty() && _activeCameraId.empty())
	{
		string tempId = id;
		reverse(tempId.begin(), tempId.end());
		string rawId = tempId.substr(tempId.find('_') + 1);
		reverse(rawId.begin(), rawId.end());
		_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
		_gui->getOverlay()->getTextField("quadId")->changeTextContent("Selected quad3d: " + rawId);
	}
}

void WorldEditor::_selectText3d(const string& id)
{
	_selectedTextId = id;

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	if(_activeModelId.empty() && _activeTextId.empty() && _activeSpeakerId.empty() && _activeLampId.empty() && _activeCameraId.empty())
	{
		string tempId = id;
		reverse(tempId.begin(), tempId.end());
		string rawId = tempId.substr(tempId.find('_') + 1);
		reverse(rawId.begin(), rawId.end());
		_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
		_gui->getOverlay()->getTextField("textId")->changeTextContent("Selected text3d: " + rawId);
	}
}

void WorldEditor::_selectSound(const string& id)
{
	_selectedSpeakerId = ("@@speaker_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");

	if(_activeModelId.empty() && _activeQuadId.empty() && _activeSpeakerId.empty() && _activeLampId.empty() && _activeCameraId.empty())
	{
		string tempId = id;
		reverse(tempId.begin(), tempId.end());
		string rawId = tempId.substr(tempId.find('_') + 1);
		reverse(rawId.begin(), rawId.end());
		_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundId")->getEntityId(), true);
		_gui->getOverlay()->getTextField("soundId")->changeTextContent("Selected sound: " + rawId);
	}
}

void WorldEditor::_selectPointlight(const string& id)
{
	_selectedLampId = ("@@lamp_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
}

void WorldEditor::_selectSpotlight(const string& id)
{
	_selectedTorchId = ("@@torch_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
}

void WorldEditor::_selectReflection(const string& id)
{
	_selectedCameraId = ("@@camera_" + id);

	_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
}

void WorldEditor::_unselectModel(const string& id)
{
	for(const auto& partId : _fe3d->model_getPartIds(id))
	{
		_fe3d->model_setOpacity(id, partId, 1.0f);
	}
}

void WorldEditor::_unselectQuad3d(const string& id)
{
	_fe3d->quad3d_setOpacity(id, 1.0f);
}

void WorldEditor::_unselectText3d(const string& id)
{
	_fe3d->text3d_setOpacity(id, 1.0f);
}

void WorldEditor::_unselectSound(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_SPEAKER_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_SPEAKER_AABB_SIZE);
}

void WorldEditor::_unselectPointlight(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_LAMP_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_unselectSpotlight(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_TORCH_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_unselectReflection(const string& id)
{
	_fe3d->model_setBaseSize(id, DEFAULT_CAMERA_SIZE);
	_fe3d->aabb_setLocalSize(id, DEFAULT_CAMERA_AABB_SIZE);
}