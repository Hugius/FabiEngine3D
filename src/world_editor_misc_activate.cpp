#include "world_editor.hpp"

void WorldEditor::_activateModel(const string& ID)
{
	_activeModelID = ID;

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeModelID);

	rightWindow->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("modelPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), true);
	_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("modelID")->getEntityID(), "Active model: " + rawID, 0.025f);
}

void WorldEditor::_activateQuad3d(const string& ID)
{
	_activeQuadID = ID;

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->quad3d_getPosition(_activeQuadID);

	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), true);
	_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadID")->getEntityID(), "Active quad3d: " + rawID, 0.025f);
}

void WorldEditor::_activateText3d(const string& ID)
{
	_activeTextID = ID;

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->text3d_getPosition(_activeTextID);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), true);
	_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textID")->getEntityID(), "Active text3d: " + rawID, 0.025f);
}

void WorldEditor::_activateSound(const string& ID)
{
	_activeSpeakerID = ("@@speaker_" + ID);

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->sound3d_getPosition(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxVolume = _fe3d->sound3d_getMaxVolume(_activeSpeakerID.substr(string("@@speaker_").size()));
	auto maxDistance = _fe3d->sound3d_getMaxDistance(_activeSpeakerID.substr(string("@@speaker_").size()));

	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getWriteField("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	string tempID = ID;
	reverse(tempID.begin(), tempID.end());
	string rawID = tempID.substr(tempID.find('_') + 1);
	reverse(rawID.begin(), rawID.end());
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), true);
	_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("soundID")->getEntityID(), "Active sound: " + rawID, 0.025f);
}

void WorldEditor::_activatePointlight(const string& ID)
{
	_activeLampID = ("@@lamp_" + ID);

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeLampID);

	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_activateSpotlight(const string& ID)
{
	_activeTorchID = ("@@torch_" + ID);

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeTorchID);

	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_activateReflection(const string& ID)
{
	_activeCameraID = ("@@camera_" + ID);

	auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeCameraID);

	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getWriteField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_deactivateModel()
{
	if(!_activeModelID.empty())
	{
		_unselectModel(_activeModelID);
	}

	_activeModelID = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), false);
}

void WorldEditor::_deactivateQuad3d()
{
	if(!_activeQuadID.empty())
	{
		_unselectQuad3d(_activeQuadID);
	}

	_activeQuadID = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), false);
}

void WorldEditor::_deactivateText3d()
{
	if(!_activeTextID.empty())
	{
		_unselectText3d(_activeTextID);
	}

	_activeTextID = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), false);
}

void WorldEditor::_deactivateSound()
{
	if(!_activeSpeakerID.empty())
	{
		_unselectSound(_activeSpeakerID);
	}

	_activeSpeakerID = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundID")->getEntityID(), false);
}

void WorldEditor::_deactivatePointlight()
{
	if(!_activeLampID.empty())
	{
		_unselectPointlight(_activeLampID);
	}

	_activeLampID = "";
}

void WorldEditor::_deactivateSpotlight()
{
	if(!_activeTorchID.empty())
	{
		_unselectSpotlight(_activeTorchID);
	}

	_activeTorchID = "";
}

void WorldEditor::_deactivateReflection()
{
	if(!_activeCameraID.empty())
	{
		_unselectReflection(_activeCameraID);
	}

	_activeCameraID = "";
}