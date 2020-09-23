#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingOptions()
{
	auto screen = _leftWindow->getScreen("modelEditorMenuOptions");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("isFaceculled")->isHovered())
		{
			_fe3d.gameEntity_setFaceCulled(_currentModelName, !_fe3d.gameEntity_isFaceCulled(_currentModelName));
		}
		else if (screen->getButton("isTransparent")->isHovered())
		{
			_fe3d.gameEntity_setTransparent(_currentModelName, !_fe3d.gameEntity_isTransparent(_currentModelName));
		}
		else if (screen->getButton("setColor")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.gameEntity_getColor(_currentModelName).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
			_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.gameEntity_getColor(_currentModelName).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
			_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.gameEntity_getColor(_currentModelName).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("uvRepeat")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV Repeat", _fe3d.gameEntity_getUvRepeat(_currentModelName), vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("lodID")->isHovered())
		{
			string lodID = _fe3d.gameEntity_getLevelOfDetailEntityID(_currentModelName);
			lodID = (lodID == "") ? lodID : lodID.substr(1, lodID.size() - 1);
			_gui->getGlobalScreen()->addValueForm("lodID", "LOD entity ID", lodID, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("back")->isHovered())
		{
			_leftWindow->setActiveScreen("modelEditorMenuChoice");
		}
	}

	// Update GUI button contents
	auto faceculledID = screen->getButton("isFaceculled")->getTextfield()->getEntityID();
	auto isCulled = _fe3d.gameEntity_isFaceCulled(_currentModelName);
	auto transparentID = screen->getButton("isTransparent")->getTextfield()->getEntityID();
	auto isTransparent = _fe3d.gameEntity_isTransparent(_currentModelName);
	_fe3d.textEntity_setTextContent(faceculledID, isCulled ? "Culling: ON" : "Culling: OFF");
	_fe3d.textEntity_setTextContent(transparentID, isTransparent ? "Alpha: ON" : "Alpha: OFF");

	// Setting model color
	vec3 newColor = _fe3d.gameEntity_getColor(_currentModelName) * 255.0f;
	_gui->getGlobalScreen()->checkValueForm("colorR", newColor.r, { });
	_gui->getGlobalScreen()->checkValueForm("colorG", newColor.g, { });
	_gui->getGlobalScreen()->checkValueForm("colorB", newColor.b, { });
	newColor.r = std::clamp(newColor.r / 255.0f, 0.0f, 1.0f);
	newColor.g = std::clamp(newColor.g / 255.0f, 0.0f, 1.0f);
	newColor.b = std::clamp(newColor.b / 255.0f, 0.0f, 1.0f);
	_fe3d.gameEntity_setColor(_currentModelName, newColor);

	// Setting model UV repeat
	float newUvRepeat = _fe3d.gameEntity_getUvRepeat(_currentModelName);
	_gui->getGlobalScreen()->checkValueForm("uvRepeat", newUvRepeat, { });
	_fe3d.gameEntity_setUvRepeat(_currentModelName, newUvRepeat);
	
	// Setting LOD entityID
	string lodID = "";
	if (_gui->getGlobalScreen()->checkValueForm("lodID", lodID, { }))
	{
		// Check if LOD entity exists
		if (std::find(_modelNames.begin(), _modelNames.end(), "@" + lodID) == _modelNames.end())
		{
			_fe3d.logger_throwWarning("Cannot find LOD entity name: " + lodID);
		}
		else
		{
			_fe3d.gameEntity_setLevelOfDetailEntity(_currentModelName, "@" + lodID);
		}
	}
}