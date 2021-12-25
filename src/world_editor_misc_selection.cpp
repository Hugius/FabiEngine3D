#include "world_editor.hpp"

void WorldEditor::_selectModel(const string& ID)
{
	_selectedModelID = ID;

	_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");

	for(const auto& partID : _fe3d.model_getPartIDs(_selectedModelID))
	{
		_fe3d.model_setWireframed(_selectedModelID, partID, true);
	}

	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		string tempID = _selectedModelID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), true);
		_fe3d.text_setContent(_gui.getOverlay()->getTextField("modelID")->getEntityID(), "Selected model: " + rawID, 0.025f);
	}
}

void WorldEditor::_selectBillboard(const string& ID)
{
	_selectedBillboardID = ID;

	_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");

	_fe3d.billboard_setWireframed(_selectedBillboardID, true);

	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), true);
		_fe3d.text_setContent(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), "Selected billboard: " + rawID, 0.025f);
	}
}

void WorldEditor::_selectSound(const string& ID)
{
	_selectedSpeakerID = ("@@speaker_" + ID);

	_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");

	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.text_setVisible(_gui.getOverlay()->getTextField("soundID")->getEntityID(), true);
		_fe3d.text_setContent(_gui.getOverlay()->getTextField("soundID")->getEntityID(), "Selected sound: " + rawID, 0.025f);
	}
}

void WorldEditor::_selectPointlight(const string& ID)
{
	_selectedLampID = ("@@lamp_" + ID);

	_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");
}

void WorldEditor::_selectSpotlight(const string& ID)
{
	_selectedTorchID = ("@@torch_" + ID);

	_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");
}

void WorldEditor::_selectReflection(const string& ID)
{
	_selectedCameraID = ("@@camera_" + ID);

	_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");
}

void WorldEditor::_unselectModel(const string& ID)
{
	for(const auto& partID : _fe3d.model_getPartIDs(ID))
	{
		_fe3d.model_setWireframeColor(ID, partID, 1.0f);
		_fe3d.model_setWireframed(ID, partID, false);
	}
}

void WorldEditor::_unselectBillboard(const string& ID)
{
	_fe3d.billboard_setWireframeColor(ID, 1.0f);
	_fe3d.billboard_setWireframed(ID, false);
}

void WorldEditor::_unselectSound(const string& ID)
{
	_fe3d.model_setBaseSize(ID, DEFAULT_SPEAKER_SIZE);
	_fe3d.aabb_setLocalSize(ID, DEFAULT_SPEAKER_AABB_SIZE);
}

void WorldEditor::_unselectPointlight(const string& ID)
{
	_fe3d.model_setBaseSize(ID, DEFAULT_LAMP_SIZE);
	_fe3d.aabb_setLocalSize(ID, DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_unselectSpotlight(const string& ID)
{
	_fe3d.model_setBaseSize(ID, DEFAULT_TORCH_SIZE);
	_fe3d.aabb_setLocalSize(ID, DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_unselectReflection(const string& ID)
{
	_fe3d.model_setBaseSize(ID, DEFAULT_CAMERA_SIZE);
	_fe3d.aabb_setLocalSize(ID, DEFAULT_CAMERA_AABB_SIZE);
}