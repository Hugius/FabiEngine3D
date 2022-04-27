#include "world_editor.hpp"

void WorldEditor::_activateModel(const string & id)
{
	_activeModelId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->model_getBasePosition(_activeModelId);

	rightWindow->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	rightWindow->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	rightWindow->getScreen("modelPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("modelPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("modelPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Model: " + _activeModelId);
}

void WorldEditor::_activateQuad(const string & id)
{
	_activeQuad3dId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->quad3d_getPosition(_activeQuad3dId);

	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("quad3dPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Quad3D: " + _activeQuad3dId);
}

void WorldEditor::_activateText(const string & id)
{
	_activeTextId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->text3d_getPosition(_activeTextId);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Text3D: " + _activeTextId);
}

void WorldEditor::_activatePointlight(const string & id)
{
	_activePointlightId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->pointlight_getPosition(_activePointlightId);

	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("pointlightPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Pointlight: " + _activePointlightId);
}

void WorldEditor::_activateSpotlight(const string & id)
{
	_activeSpotlightId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);

	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("spotlightPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Spotlight: " + _activeSpotlightId);
}

void WorldEditor::_activateCaptor(const string & id)
{
	_activeCaptorId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->captor_getPosition(_activeCaptorId);

	rightWindow->getScreen("captorPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("captorPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("captorPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Captor: " + _activeCaptorId);
}

void WorldEditor::_activateSound(const string & id)
{
	_activeSoundId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->sound3d_getPosition(_activeSoundId);
	const auto maxVolume = _fe3d->sound3d_getMaxVolume(_activeSoundId);
	const auto maxDistance = _fe3d->sound3d_getMaxDistance(_activeSoundId);

	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputBox("volume")->setTextContent(to_string(static_cast<int>(maxVolume * SOUND_VOLUME_MULTIPLIER)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputBox("distance")->setTextContent(to_string(static_cast<int>(maxDistance)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Sound: " + _activeSoundId);
}

void WorldEditor::_deactivateModel()
{
	if(!_activeModelId.empty())
	{
		_deselectModel(_activeModelId);
	}

	_activeModelId = "";
}

void WorldEditor::_deactivateQuad()
{
	if(!_activeQuad3dId.empty())
	{
		_deselectQuad(_activeQuad3dId);
	}

	_activeQuad3dId = "";
}

void WorldEditor::_deactivateText()
{
	if(!_activeTextId.empty())
	{
		_deselectText(_activeTextId);
	}

	_activeTextId = "";
}

void WorldEditor::_deactivatePointlight()
{
	if(!_activePointlightId.empty())
	{
		_deselectPointlight(_activePointlightId);
	}

	_activePointlightId = "";
}

void WorldEditor::_deactivateSpotlight()
{
	if(!_activeSpotlightId.empty())
	{
		_deselectSpotlight(_activeSpotlightId);
	}

	_activeSpotlightId = "";
}

void WorldEditor::_deactivateCaptor()
{
	if(!_activeCaptorId.empty())
	{
		_deselectCaptor(_activeCaptorId);
	}

	_activeCaptorId = "";
}

void WorldEditor::_deactivateSound()
{
	if(!_activeSoundId.empty())
	{
		_deselectSound(_activeSoundId);
	}

	_activeSoundId = "";
}