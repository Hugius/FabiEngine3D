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

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Model: " + _activeModelId);
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

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Quad3D: " + _activeQuadId);
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

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Text3D: " + _activeTextId);
}

void WorldEditor::_activatePointlight(const string& id)
{
	_activePointlightId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->pointlight_getPosition(_activePointlightId);

	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("radius")->setHoverable(true);
	rightWindow->getScreen("pointlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("pointlightPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("pointlightPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Pointlight: " + _activePointlightId);
}

void WorldEditor::_activateSpotlight(const string& id)
{
	_activeSpotlightId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);

	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("position")->setHoverable(false);
	rightWindow->getScreen("spotlightPropertiesMenu")->getButton("color")->setHoverable(true);

	rightWindow->getScreen("spotlightPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("spotlightPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Spotlight: " + _activeSpotlightId);
}

void WorldEditor::_activateReflection(const string& id)
{
	_activeReflectionId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->reflection_getPosition(_activeReflectionId);

	rightWindow->getScreen("reflectionPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	rightWindow->getScreen("reflectionPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Reflection: " + _activeReflectionId);
}

void WorldEditor::_activateSound(const string& id)
{
	_activeSoundId = id;

	const auto rightWindow = _gui->getRightViewport()->getWindow("main");
	auto position = _fe3d->sound3d_getPosition(_activeSoundId);
	auto maxVolume = _fe3d->sound3d_getMaxVolume(_activeSoundId);
	auto maxDistance = _fe3d->sound3d_getMaxDistance(_activeSoundId);

	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("x")->changeTextContent(to_string(static_cast<int>(position.x)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("y")->changeTextContent(to_string(static_cast<int>(position.y)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("z")->changeTextContent(to_string(static_cast<int>(position.z)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("volume")->changeTextContent(to_string(static_cast<int>(maxVolume * 100.0f)));
	_gui->getRightViewport()->getWindow("main")->getScreen("soundPropertiesMenu")->getInputField("distance")->changeTextContent(to_string(static_cast<int>(maxDistance)));

	_gui->getOverlay()->getTextField("activeId")->changeTextContent("Active Sound: " + _activeSoundId);
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
	if(!_activeQuadId.empty())
	{
		_deselectQuad3d(_activeQuadId);
	}

	_activeQuadId = "";
}

void WorldEditor::_deactivateText3d()
{
	if(!_activeTextId.empty())
	{
		_deselectText3d(_activeTextId);
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

void WorldEditor::_deactivateReflection()
{
	if(!_activeReflectionId.empty())
	{
		_deselectReflection(_activeReflectionId);
	}

	_activeReflectionId = "";
}

void WorldEditor::_deactivateSound()
{
	if(!_activeSoundId.empty())
	{
		_deselectSound(_activeSoundId);
	}

	_activeSoundId = "";
}