#include "scene_editor.hpp"

void SceneEditor::_selectModel(const string& ID)
{
	// Set ID
	_selectedModelID = ID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\textures\\cursor_pointing.png");

	// Check if nothing is active
	if(_activeModelID.empty() && _activeBillboardID.empty() && _activeSpeakerID.empty() && _activeLampID.empty() && _activeCameraID.empty())
	{
		// Removing the unique number from the modelID and updating the text content
		string tempID = ID;
		reverse(tempID.begin(), tempID.end());
		string rawID = tempID.substr(tempID.find('_') + 1);
		reverse(rawID.begin(), rawID.end());
		_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
		_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Selected model: " + rawID, 0.025f);
	}
}

void SceneEditor::_activateModel(const string& ID)
{
	// Set ID
	_activeModelID = ID;

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeModelID);

	// Update buttons hoverability
	rightWindow->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	// Filling write fields
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the modelID and updating the text content
	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), "Active model: " + rawID, 0.025f);
}

void SceneEditor::_selectBillboard(const string& ID)
{
	// Set ID
	_selectedBillboardID = ID;

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\textures\\cursor_pointing.png");

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

void SceneEditor::_activateBillboard(const string& ID)
{
	// Set ID
	_activeBillboardID = ID;

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.billboardEntity_getPosition(_activeBillboardID);

	// Update buttons hoverability
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getButton("size")->setHoverable(true);

	// Filling write fields
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("billboardPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	// Removing the unique number from the billboardID and updating the text content
	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), "Active billboard: " + rawID, 0.025f);
}

void SceneEditor::_selectSound(const string& ID)
{
	// Set ID
	_selectedSpeakerID = ("@@speaker_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\textures\\cursor_pointing.png");

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

void SceneEditor::_selectPointlight(const string& ID)
{
	// Set ID
	_selectedLampID = ("@@lamp_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\textures\\cursor_pointing.png");
}

void SceneEditor::_selectSpotlight(const string& ID)
{
	// Set ID
	_selectedTorchID = ("@@torch_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\textures\\cursor_pointing.png");
}

void SceneEditor::_selectReflection(const string& ID)
{
	// Set ID
	_selectedCameraID = ("@@camera_" + ID);

	// Change cursor
	_fe3d.imageEntity_setDiffuseMap("@@cursor", "engine\\textures\\cursor_pointing.png");
}

void SceneEditor::_activateSound(const string& ID)
{
	// Set ID
	_activeSpeakerID = ("@@speaker_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.sound_getPosition(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxVolume = _fe3d.sound_getMaxVolume(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxDistance = _fe3d.sound_getMaxDistance(_activeSpeakerID.substr(string("@@speaker_").size()));

	// Filling write fields
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui.getViewport("right")->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	// Removing the unique number from the soundID and updating the text content
	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
	_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Active sound: " + rawID, 0.025f);
}

void SceneEditor::_activatePointlight(const string& ID)
{
	// Set ID
	_activeLampID = ("@@lamp_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeLampID);

	// Update buttons hoverability
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("color")->setHoverable(true);

	// Filling writeFields
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void SceneEditor::_activateSpotlight(const string& ID)
{
	// Set ID
	_activeTorchID = ("@@torch_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeTorchID);

	// Update buttons hoverability
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	// Filling writeFields
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void SceneEditor::_activateReflection(const string& ID)
{
	// Set ID
	_activeCameraID = ("@@camera_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.modelEntity_getBasePosition(_activeCameraID);

	// Filling writeFields
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void SceneEditor::_deactivateModel()
{
	_activeModelID = "";
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("modelID")->getEntityID(), false);
}

void SceneEditor::_deactivateBillboard()
{
	_activeBillboardID = "";
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
}

void SceneEditor::_deactivateSound()
{
	_activeSpeakerID = "";
	_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), false);
}

void SceneEditor::_deactivatePointlight()
{
	_activeLampID = "";
}

void SceneEditor::_deactivateSpotlight()
{
	_activeTorchID = "";
}

void SceneEditor::_deactivateReflection()
{
	_activeCameraID = "";
}