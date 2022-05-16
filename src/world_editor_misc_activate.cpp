#include "world_editor.hpp"

void WorldEditor::_activateModel(const string & modelId)
{
	_activeModelId = modelId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->model_getBasePosition(_activeModelId);

	window->getScreen("modelPropertiesMenu")->getButton("position")->setHoverable(false);
	window->getScreen("modelPropertiesMenu")->getButton("rotation")->setHoverable(true);
	window->getScreen("modelPropertiesMenu")->getButton("size")->setHoverable(true);

	window->getScreen("modelPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("modelPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("modelPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Model: " + _activeModelId);
}

void WorldEditor::_activateQuad3d(const string & quad3dId)
{
	_activeQuad3dId = quad3dId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->quad3d_getPosition(_activeQuad3dId);

	window->getScreen("quad3dPropertiesMenu")->getButton("position")->setHoverable(false);
	window->getScreen("quad3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	window->getScreen("quad3dPropertiesMenu")->getButton("size")->setHoverable(true);

	window->getScreen("quad3dPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("quad3dPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("quad3dPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Quad3D: " + _activeQuad3dId);
}

void WorldEditor::_activateText3d(const string & text3dId)
{
	_activeText3dId = text3dId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->text3d_getPosition(_activeText3dId);

	window->getScreen("text3dPropertiesMenu")->getButton("position")->setHoverable(false);
	window->getScreen("text3dPropertiesMenu")->getButton("rotation")->setHoverable(true);
	window->getScreen("text3dPropertiesMenu")->getButton("size")->setHoverable(true);

	window->getScreen("text3dPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("text3dPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("text3dPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Text3D: " + _activeText3dId);
}

void WorldEditor::_activateAabb(const string & aabbId)
{
	_activeAabbId = aabbId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->aabb_getBasePosition(_activeAabbId);

	window->getScreen("aabbPropertiesMenu")->getButton("position")->setHoverable(false);
	window->getScreen("aabbPropertiesMenu")->getButton("size")->setHoverable(true);

	window->getScreen("aabbPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("aabbPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("aabbPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active AABB: " + _activeAabbId);
}

void WorldEditor::_activatePointlight(const string & pointlightId)
{
	_activePointlightId = pointlightId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->pointlight_getPosition(_activePointlightId);

	window->getScreen("pointlightPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("pointlightPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("pointlightPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Pointlight: " + _activePointlightId);
}

void WorldEditor::_activateSpotlight(const string & spotlightId)
{
	_activeSpotlightId = spotlightId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->spotlight_getPosition(_activeSpotlightId);

	window->getScreen("spotlightPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("spotlightPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("spotlightPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Spotlight: " + _activeSpotlightId);
}

void WorldEditor::_activateCaptor(const string & captorId)
{
	_activeCaptorId = captorId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->captor_getPosition(_activeCaptorId);

	window->getScreen("captorPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("captorPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("captorPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Captor: " + _activeCaptorId);
}

void WorldEditor::_activateSound3d(const string & sound3dId)
{
	_activeSound3dId = sound3dId;

	const auto window = _gui->getLeftViewport()->getWindow("main");
	const auto position = _fe3d->sound3d_getPosition(_activeSound3dId);

	window->getScreen("sound3dPropertiesMenu")->getInputBox("x")->setTextContent(to_string(static_cast<int>(position.x)));
	window->getScreen("sound3dPropertiesMenu")->getInputBox("y")->setTextContent(to_string(static_cast<int>(position.y)));
	window->getScreen("sound3dPropertiesMenu")->getInputBox("z")->setTextContent(to_string(static_cast<int>(position.z)));

	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setTextContent("Active Sound3D: " + _activeSound3dId);
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

void WorldEditor::_deactivateAabb()
{
	if(!_activeAabbId.empty())
	{
		_deselectAabb(_activeAabbId);
	}

	_activeAabbId = "";
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

void WorldEditor::_deactivateSound3d()
{
	if(!_activeSound3dId.empty())
	{
		_deselectSound3d(_activeSound3dId);
	}

	_activeSound3dId = "";
}