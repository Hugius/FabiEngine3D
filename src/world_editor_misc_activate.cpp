#include "world_editor.hpp"

void WorldEditor::_activateModel(const string& id)
{
	_activeModelId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeModelId);

	rightWindow->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	rightWindow->getScreen("modelPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("modelPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("modelPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("modelId")->changeTextContent("Active Model: " + _activeModelId);
}

void WorldEditor::_activateQuad3d(const string& id)
{
	_activeQuadId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->quad3d_getPosition(_activeQuadId);

	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("quadId")->changeTextContent("Active Quad3D: " + _activeQuadId);
}

void WorldEditor::_activateText3d(const string& id)
{
	_activeTextId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->text3d_getPosition(_activeTextId);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("textId")->changeTextContent("Active Text3D: " + _activeTextId);
}

void WorldEditor::_activateSound(const string& id)
{
	_activeSpeakerId = ("@@speaker_" + id);

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->sound3d_getPosition(_activeSpeakerId.substr(string("@@speaker_").size()));
	auto maxVolume = _fe3d->sound3d_getMaxVolume(_activeSpeakerId.substr(string("@@speaker_").size()));
	auto maxDistance = _fe3d->sound3d_getMaxDistance(_activeSpeakerId.substr(string("@@speaker_").size()));

	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundId")->getEntityId(), true);
	_gui->getOverlay()->getTextField("soundId")->changeTextContent("Active Sound: " + _activeSpeakerId);
}

void WorldEditor::_activatePointlight(const string& id)
{
	_activeLampId = ("@@lamp_" + id);

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeLampId);

	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("pointlightPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_activateSpotlight(const string& id)
{
	_activeTorchId = ("@@torch_" + id);

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeTorchId);

	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("spotlightPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_activateReflection(const string& id)
{
	_activeCameraId = ("@@camera_" + id);

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->model_getBasePosition(_activeCameraId);

	rightWindow->getScreen("reflectionPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
}

void WorldEditor::_deactivateModel()
{
	if(!_activeModelId.empty())
	{
		_unselectModel(_activeModelId);
	}

	_activeModelId = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), false);
}

void WorldEditor::_deactivateQuad3d()
{
	if(!_activeQuadId.empty())
	{
		_unselectQuad3d(_activeQuadId);
	}

	_activeQuadId = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
}

void WorldEditor::_deactivateText3d()
{
	if(!_activeTextId.empty())
	{
		_unselectText3d(_activeTextId);
	}

	_activeTextId = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), false);
}

void WorldEditor::_deactivateSound()
{
	if(!_activeSpeakerId.empty())
	{
		_unselectSound(_activeSpeakerId);
	}

	_activeSpeakerId = "";
	_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("soundId")->getEntityId(), false);
}

void WorldEditor::_deactivatePointlight()
{
	if(!_activeLampId.empty())
	{
		_unselectPointlight(_activeLampId);
	}

	_activeLampId = "";
}

void WorldEditor::_deactivateSpotlight()
{
	if(!_activeTorchId.empty())
	{
		_unselectSpotlight(_activeTorchId);
	}

	_activeTorchId = "";
}

void WorldEditor::_deactivateReflection()
{
	if(!_activeCameraId.empty())
	{
		_unselectReflection(_activeCameraId);
	}

	_activeCameraId = "";
}