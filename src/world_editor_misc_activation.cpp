#include "world_editor.hpp"

void WorldEditor::_activateModel(const string& ID)
{
	// Set ID
	_activeModelID = ID;

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.model_getBasePosition(_activeModelID);

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
	_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), true);
	_fe3d.text_setContent(_gui.getOverlay()->getTextField("modelID")->getEntityID(), "Active model: " + rawID, 0.025f);
}

void WorldEditor::_activateBillboard(const string& ID)
{
	// Set ID
	_activeBillboardID = ID;

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.billboard_getPosition(_activeBillboardID);

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
	_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), true);
	_fe3d.text_setContent(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), "Active billboard: " + rawID, 0.025f);
}

void WorldEditor::_activateSound(const string& ID)
{
	// Set ID
	_activeSpeakerID = ("@@speaker_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.sound3d_getPosition(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxVolume = _fe3d.sound3d_getMaxVolume(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxDistance = _fe3d.sound3d_getMaxDistance(_activeSpeakerID.substr(string("@@speaker_").size()));

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
	_fe3d.text_setVisible(_gui.getOverlay()->getTextField("soundID")->getEntityID(), true);
	_fe3d.text_setContent(_gui.getOverlay()->getTextField("soundID")->getEntityID(), "Active sound: " + rawID, 0.025f);
}

void WorldEditor::_activatePointlight(const string& ID)
{
	// Set ID
	_activeLampID = ("@@lamp_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.model_getBasePosition(_activeLampID);

	// Update buttons hoverability
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("color")->setHoverable(true);

	// Filling writeFields
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_activateSpotlight(const string& ID)
{
	// Set ID
	_activeTorchID = ("@@torch_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.model_getBasePosition(_activeTorchID);

	// Update buttons hoverability
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	// Filling writeFields
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_activateReflection(const string& ID)
{
	// Set ID
	_activeCameraID = ("@@camera_" + ID);

	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");
	auto position = _fe3d.model_getBasePosition(_activeCameraID);

	// Filling writeFields
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_deactivateModel()
{
	// Unselect model
	if(!_activeModelID.empty())
	{
		_unselectModel(_activeModelID);
	}

	// Deactivate model
	_activeModelID = "";
	_fe3d.text_setVisible(_gui.getOverlay()->getTextField("modelID")->getEntityID(), false);
}

void WorldEditor::_deactivateBillboard()
{
	// Unselect billboard
	if(!_activeBillboardID.empty())
	{
		_unselectBillboard(_activeBillboardID);
	}

	// Deactivate billboard
	_activeBillboardID = "";
	_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
}

void WorldEditor::_deactivateSound()
{
	// Unselect sound
	if(!_activeSpeakerID.empty())
	{
		_unselectBillboard(_activeSpeakerID);
	}

	// Deactivate sound
	_activeSpeakerID = "";
	_fe3d.text_setVisible(_gui.getOverlay()->getTextField("soundID")->getEntityID(), false);
}

void WorldEditor::_deactivatePointlight()
{
	// Unselect pointlight
	if(!_activeLampID.empty())
	{
		_unselectBillboard(_activeLampID);
	}

	// Deactivate pointlight
	_activeLampID = "";
}

void WorldEditor::_deactivateSpotlight()
{
	// Unselect spotlight
	if(!_activeTorchID.empty())
	{
		_unselectBillboard(_activeTorchID);
	}

	// Deactivate spotlight
	_activeTorchID = "";
}

void WorldEditor::_deactivateReflection()
{
	// Unselect reflection
	if(!_activeCameraID.empty())
	{
		_unselectBillboard(_activeCameraID);
	}

	// Deactivate reflection
	_activeCameraID = "";
}