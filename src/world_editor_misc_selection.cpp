#include "world_editor.hpp"

void WorldEditor::_selectModel(const string& ID)
{
	// Set ID
	_selectedModelID = ID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");

	// Enable wireframed rendering
	for(const auto& partID : _fe3d.modelEntity_getPartIDs(_selectedModelID))
	{
		_fe3d.modelEntity_setWireframed(_selectedModelID, partID, true);
	}

	// Check if nothing is active
	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the modelID and updating the text content
		string tempID = _selectedModelID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Selected model: " + rawID, 0.025f);
	}
}

void WorldEditor::_selectBillboard(const string& ID)
{
	// Set ID
	_selectedBillboardID = ID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");

	// Enable wireframed rendering
	_fe3d.billboardEntity_setWireframed(_selectedBillboardID, true);

	// Check if nothing is active
	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the billboardID and updating the text content
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Selected billboard: " + rawID, 0.025f);
	}
}

void WorldEditor::_selectSound(const string& ID)
{
	// Set ID
	_selectedSpeakerID = ("@@speaker_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the soundID and updating the text content
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Selected sound: " + rawID, 0.025f);
	}
}

void WorldEditor::_selectPointlight(const string& ID)
{
	// Set ID
	_selectedLampID = ("@@lamp_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");
}

void WorldEditor::_selectSpotlight(const string& ID)
{
	// Set ID
	_selectedTorchID = ("@@torch_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");
}

void WorldEditor::_selectReflection(const string& ID)
{
	// Set ID
	_selectedCameraID = ("@@camera_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\assets\\textures\\cursor_pointing.png");
}

void WorldEditor::_unselectModel(const string& ID)
{
	for(const auto& partID : _fe3d.modelEntity_getPartIDs(ID))
	{
		_fe3d.modelEntity_setWireframeColor(ID, partID, 1.0f);
		_fe3d.modelEntity_setWireframed(ID, partID, false);
	}
}

void WorldEditor::_unselectBillboard(const string& ID)
{
	_fe3d.billboardEntity_setWireframeColor(ID, 1.0f);
	_fe3d.billboardEntity_setWireframed(ID, false);
}

void WorldEditor::_unselectSound(const string& ID)
{
	_fe3d.modelEntity_setBaseSize(ID, DEFAULT_SPEAKER_SIZE);
	_fe3d.aabbEntity_setLocalSize(ID, DEFAULT_SPEAKER_AABB_SIZE);
}

void WorldEditor::_unselectPointlight(const string& ID)
{
	_fe3d.modelEntity_setBaseSize(ID, DEFAULT_LAMP_SIZE);
	_fe3d.aabbEntity_setLocalSize(ID, DEFAULT_LAMP_AABB_SIZE);
}

void WorldEditor::_unselectSpotlight(const string& ID)
{
	_fe3d.modelEntity_setBaseSize(ID, DEFAULT_TORCH_SIZE);
	_fe3d.aabbEntity_setLocalSize(ID, DEFAULT_TORCH_AABB_SIZE);
}

void WorldEditor::_unselectReflection(const string& ID)
{
	_fe3d.modelEntity_setBaseSize(ID, DEFAULT_CAMERA_SIZE);
	_fe3d.aabbEntity_setLocalSize(ID, DEFAULT_CAMERA_AABB_SIZE);
}