#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingOptions()
{
	auto screen = _leftWindow->getScreen("modelEditingOptions");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("faceculled")->isHovered())
		{
			_fe3d.gameEntity_setFaceCulled(_currentModelName, !_fe3d.gameEntity_isFaceCulled(_currentModelName));
		}
		else if (screen->getButton("shadowed")->isHovered())
		{
			_fe3d.gameEntity_setShadowed(_currentModelName, !_fe3d.gameEntity_isShadowed(_currentModelName));
		}
		else if (screen->getButton("transparent")->isHovered())
		{
			_fe3d.gameEntity_setTransparent(_currentModelName, !_fe3d.gameEntity_isTransparent(_currentModelName));
		}
		else if (screen->getButton("specular")->isHovered())
		{
			_fe3d.gameEntity_setSpecularLighted(_currentModelName, !_fe3d.gameEntity_isSpecularLighted(_currentModelName));
		}
		else if (screen->getButton("factor")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("factor", "Specular factor",
				_fe3d.gameEntity_getSpecularFactor(_currentModelName), vec2(0.0f, 0.1f), vec2(0.1f, 0.1f));
		}
		else if (screen->getButton("setColor")->isHovered())
		{
			std::cout << _fe3d.gameEntity_getColor(_currentModelName).g << std::endl;
			_gui->getGlobalScreen()->addValueForm("colorG", "G(0-255)", _fe3d.gameEntity_getColor(_currentModelName).g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
			_gui->getGlobalScreen()->addValueForm("colorR", "R(0-255)", _fe3d.gameEntity_getColor(_currentModelName).r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
			_gui->getGlobalScreen()->addValueForm("colorB", "B(0-255)", _fe3d.gameEntity_getColor(_currentModelName).b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("uvRepeat")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("uvRepeat", "UV Repeat", _fe3d.gameEntity_getUvRepeat(_currentModelName), vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
		}
		else if (screen->getButton("back")->isHovered())
		{
			_leftWindow->setActiveScreen("modelEditingMain");
		}
	}

	// Update GUI button contents
	auto faceculledID = screen->getButton("faceculled")->getTextfield()->getEntityID();
	auto isCulled = _fe3d.gameEntity_isFaceCulled(_currentModelName);
	auto shadowedID = screen->getButton("shadowed")->getTextfield()->getEntityID();
	auto isShadowed = _fe3d.gameEntity_isShadowed(_currentModelName);
	auto transparentID = screen->getButton("transparent")->getTextfield()->getEntityID();
	auto isTransparent = _fe3d.gameEntity_isTransparent(_currentModelName);
	auto specularID = screen->getButton("specular")->getTextfield()->getEntityID();
	auto isSpecular = _fe3d.gameEntity_isSpecularLighted(_currentModelName);
	_fe3d.textEntity_setTextContent(faceculledID, isCulled ? "Culling: ON" : "Culling: OFF");
	_fe3d.textEntity_setTextContent(shadowedID, isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	_fe3d.textEntity_setTextContent(transparentID, isTransparent ? "No-white: ON" : "No-white: OFF");
	_fe3d.textEntity_setTextContent(specularID, isSpecular ? "Specular: ON" : "Specular: OFF");

	// Update specular factor
	if (_fe3d.gameEntity_isSpecularLighted(_currentModelName))
	{
		float factor = _fe3d.gameEntity_getSpecularFactor(_currentModelName);
		_gui->getGlobalScreen()->checkValueForm("factor", factor);
		_fe3d.gameEntity_setSpecularFactor(_currentModelName, factor);
	}

	// Update specular factor button hoverability
	screen->getButton("factor")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelName));

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
}