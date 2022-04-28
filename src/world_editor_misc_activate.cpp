#include "world_editor.hpp"

void WorldEditor::_activateModel(const string & modelId)
{
	_activeModelId = modelId;

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

void WorldEditor::_activateQuad3d(const string & quad3dId)
{
	_activeQuad3dId = quad3dId;

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

void WorldEditor::_activateText3d(const string & text3dId)
{
	_activeText3dId = text3dId;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->text3d_getPosition(_activeText3dId);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("position")->setHoverable(false);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getButton("size")->setHoverable(true);

	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("text3dPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Text3D: " + _activeText3dId);
}

void WorldEditor::_activatePointlight(const string & pointlightId)
{
	_activePointlightId = pointlightId;

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

void WorldEditor::_activateSpotlight(const string & spotlightId)
{
	_activeSpotlightId = spotlightId;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);

	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("spotlightPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Spotlight: " + _activeSpotlightId);
}

void WorldEditor::_activateCaptor(const string & captorId)
{
	_activeCaptorId = captorId;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	const auto position = _fe3d->captor_getPosition(_activeCaptorId);

	rightWindow->getScreen("captorPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("captorPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("captorPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->setTextContent("Active Captor: " + _activeCaptorId);
}

void WorldEditor::_activateSound(const string & soundId)
{
	_activeSoundId = soundId;

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

void WorldEditor::_deactivateQuad3d()
{
	if(!_activeQuad3dId.empty())
	{
		_deselectQuad3d(_activeQuad3dId);
	}

	_activeQuad3dId = "";
}

void WorldEditor::_deactivateText3d()
{
	if(!_activeText3dId.empty())
	{
		_deselectText3d(_activeText3dId);
	}

	_activeText3dId = "";
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