#include <algorithm>

#include "model_editor.hpp"

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
		else if (screen->getButton("strength")->isHovered())
		{
			_gui->getGlobalScreen()->addValueForm("strength", "Specular strength", 
				_fe3d.gameEntity_getSpecularStrength(_currentModelName), vec2(0.0f, 0.1f), vec2(0.1f, 0.1f));
		}
		else if (screen->getButton("setColor")->isHovered())
		{
			_modelColorPicking = true;

			// Add textfields and writefields
			_gui->getGlobalScreen()->addTextfield("modelColorR", vec2(-0.3f, 0.1f), vec2(0.025f, 0.1f), "R", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelColorG", vec2(0.0f, 0.1f), vec2(0.025f, 0.1f), "G", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelColorB", vec2(0.3f, 0.1f), vec2(0.025f, 0.1f), "B", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("modelColorR", vec2(-0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 0);
			_gui->getGlobalScreen()->addWriteField("modelColorG", vec2(0.0f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 0);
			_gui->getGlobalScreen()->addWriteField("modelColorB", vec2(0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 0);
			_gui->getGlobalScreen()->addButton("done", vec2(0.0f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));

			// Set default model size
			vec3 currentColor = _fe3d.gameEntity_getColor(_currentModelName);
			_gui->getGlobalScreen()->getWriteField("modelColorR")->setTextContent(std::to_string(int(currentColor.x * 255.0f)));
			_gui->getGlobalScreen()->getWriteField("modelColorG")->setTextContent(std::to_string(int(currentColor.y * 255.0f)));
			_gui->getGlobalScreen()->getWriteField("modelColorB")->setTextContent(std::to_string(int(currentColor.z * 255.0f)));

			// Set GUI focus
			_gui->getGlobalScreen()->setFocus(true);
		}
		else if (screen->getButton("uvRepeat")->isHovered())
		{
			_settingModelUvRepeat = true;

			_gui->getGlobalScreen()->addTextfield("uvRepeat", vec2(0.0f, 0.1f), vec2(0.25f, 0.1f), "UV repeat", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("uvRepeat", vec2(-0.0f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 0);
			_gui->getGlobalScreen()->addButton("done", vec2(0.0f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));

			// Set default model UV repeat
			float currentRepeat = _fe3d.gameEntity_getUvRepeat(_currentModelName);
			_gui->getGlobalScreen()->getWriteField("uvRepeat")->setTextContent(std::to_string(int(currentRepeat)));

			// Set GUI focus
			_gui->getGlobalScreen()->setFocus(true);
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

	// Update specular strength
	if (_fe3d.gameEntity_isSpecularLighted(_currentModelName))
	{
		float strength = _fe3d.gameEntity_getSpecularStrength(_currentModelName);
		_gui->getGlobalScreen()->checkValueForm("strength", strength);
		_fe3d.gameEntity_setSpecularStrength(_currentModelName, strength);
	}

	// Update specular strength button hoverability
	screen->getButton("strength")->setHoverable(_fe3d.gameEntity_isSpecularLighted(_currentModelName));

	// Update model color changing through buttons
	if (_modelColorPicking)
	{
		// Current model size
		vec3 newColor = _fe3d.gameEntity_getColor(_currentModelName);

		// R
		if (_gui->getGlobalScreen()->getWriteField("modelColorR")->getTextContent() != "")
		{
			newColor.x = float(stoi(_gui->getGlobalScreen()->getWriteField("modelColorR")->getTextContent())) / 255.0f;
			newColor.x = std::clamp(newColor.x, 0.0f, 1.0f);
		}

		// G
		if (_gui->getGlobalScreen()->getWriteField("modelColorG")->getTextContent() != "")
		{
			newColor.y = float(stoi(_gui->getGlobalScreen()->getWriteField("modelColorG")->getTextContent())) / 255.0f;
			newColor.y = std::clamp(newColor.y, 0.0f, 1.0f);
		}

		// B
		if (_gui->getGlobalScreen()->getWriteField("modelColorB")->getTextContent() != "")
		{
			newColor.z = float(stoi(_gui->getGlobalScreen()->getWriteField("modelColorB")->getTextContent())) / 255.0f;
			newColor.z = std::clamp(newColor.z, 0.0f, 1.0f);
		}

		// Set new model color
		_fe3d.gameEntity_setColor(_currentModelName, newColor);

		// Done button
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (_gui->getGlobalScreen()->getButton("done")->isHovered())
			{
				_modelColorPicking = false;

				_gui->getGlobalScreen()->deleteTextfield("modelColorR");
				_gui->getGlobalScreen()->deleteWriteField("modelColorR");
				_gui->getGlobalScreen()->deleteTextfield("modelColorG");
				_gui->getGlobalScreen()->deleteWriteField("modelColorG");
				_gui->getGlobalScreen()->deleteTextfield("modelColorB");
				_gui->getGlobalScreen()->deleteWriteField("modelColorB");
				_gui->getGlobalScreen()->deleteButton("done");
				_gui->getGlobalScreen()->setFocus(false);
			}
		}
	}

	// Update changing model UV repeat through buttons
	if (_settingModelUvRepeat)
	{
		// Current UV repeat
		float newUvRepeat = _fe3d.gameEntity_getUvRepeat(_currentModelName);

		// Reading writefield
		if (_gui->getGlobalScreen()->getWriteField("uvRepeat")->getTextContent() != "")
		{
			newUvRepeat = float(stoi(_gui->getGlobalScreen()->getWriteField("uvRepeat")->getTextContent()));
		}

		// Set new model UV repeat
		_fe3d.gameEntity_setUvRepeat(_currentModelName, newUvRepeat);

		// Done button
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (_gui->getGlobalScreen()->getButton("done")->isHovered())
			{
				_settingModelUvRepeat = false;

				_gui->getGlobalScreen()->deleteTextfield("uvRepeat");
				_gui->getGlobalScreen()->deleteWriteField("uvRepeat");
				_gui->getGlobalScreen()->deleteButton("done");
				_gui->getGlobalScreen()->setFocus(false);
			}
		}
	}
}