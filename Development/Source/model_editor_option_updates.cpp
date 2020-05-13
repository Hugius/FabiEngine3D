#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateModelEditingOptions()
{
	auto screen = _window->getScreen("modelEditingOptions");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getScrollingList("optionsList")->getButton("faceculled")->isHovered())
		{
			auto textfieldID = screen->getScrollingList("optionsList")->getButton("faceculled")->getTextfield()->getEntityID();
			auto isCulled = _fe3d.gameEntity_isFaceCulled(_currentModelName);

			_fe3d.textEntity_setTextContent(textfieldID, isCulled ? "Culling: OFF" : "Culling: ON");
			_fe3d.gameEntity_setFaceCulled(_currentModelName, !isCulled);
		}
		else if (screen->getScrollingList("optionsList")->getButton("shadowed")->isHovered())
		{
			auto textfieldID = screen->getScrollingList("optionsList")->getButton("shadowed")->getTextfield()->getEntityID();
			auto isShadowed = _fe3d.gameEntity_isShadowed(_currentModelName);

			_fe3d.textEntity_setTextContent(textfieldID, isShadowed ? "Shadowed: OFF" : "Shadowed: ON");
			_fe3d.gameEntity_setShadowed(_currentModelName, !isShadowed);
		}
		else if (screen->getScrollingList("optionsList")->getButton("transparent")->isHovered())
		{
			auto textfieldID = screen->getScrollingList("optionsList")->getButton("transparent")->getTextfield()->getEntityID();
			auto isTransparent = _fe3d.gameEntity_isTransparent(_currentModelName);

			_fe3d.textEntity_setTextContent(textfieldID, isTransparent ? "No-white: OFF" : "No-white: ON");
			_fe3d.gameEntity_setTransparent(_currentModelName, !isTransparent);
		}
		else if (screen->getScrollingList("optionsList")->getButton("specular")->isHovered())
		{
			auto textfieldID = screen->getScrollingList("optionsList")->getButton("specular")->getTextfield()->getEntityID();
			auto isSpecular = _fe3d.gameEntity_isSpecularLighted(_currentModelName);

			_fe3d.textEntity_setTextContent(textfieldID, isSpecular ? "Specular: OFF" : "Specular: ON");
			_fe3d.gameEntity_setSpecularLighted(_currentModelName, !isSpecular);
		}
		else if (screen->getScrollingList("optionsList")->getButton("setColor")->isHovered())
		{
			_modelColorPicking = true;

			// Add textfields and writefields
			_gui->getGlobalScreen()->addTextfield("modelColorR", vec2(-0.3f, 0.1f), vec2(0.025f, 0.1f), "R", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelColorG", vec2(0.0f, 0.1f), vec2(0.025f, 0.1f), "G", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelColorB", vec2(0.3f, 0.1f), vec2(0.025f, 0.1f), "B", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("modelColorR", vec2(-0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addWriteField("modelColorG", vec2(0.0f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addWriteField("modelColorB", vec2(0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f)), 0, 1, 1, 1;
			_gui->getGlobalScreen()->addButton("done", vec2(0.0f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));

			// Set default model size
			vec3 currentColor = _fe3d.gameEntity_getColor(_currentModelName);
			_gui->getGlobalScreen()->getWriteField("modelColorR")->setTextContent(std::to_string(int(currentColor.x * 255.0f)));
			_gui->getGlobalScreen()->getWriteField("modelColorG")->setTextContent(std::to_string(int(currentColor.y * 255.0f)));
			_gui->getGlobalScreen()->getWriteField("modelColorB")->setTextContent(std::to_string(int(currentColor.z * 255.0f)));

			// Set GUI focus
			_gui->setFocus(true);
		}
		else if (screen->getScrollingList("optionsList")->getButton("uvRepeat")->isHovered())
		{
			_settingModelUvRepeat = true;

			_gui->getGlobalScreen()->addTextfield("uvRepeat", vec2(0.0f, 0.1f), vec2(0.25f, 0.1f), "UV repeat", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("uvRepeat", vec2(-0.0f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addButton("done", vec2(0.0f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));

			// Set default model UV repeat
			float currentRepeat = _fe3d.gameEntity_getUvRepeat(_currentModelName);
			_gui->getGlobalScreen()->getWriteField("uvRepeat")->setTextContent(std::to_string(int(currentRepeat)));

			// Set GUI focus
			_gui->setFocus(true);
		}
		else if (screen->getScrollingList("optionsList")->getButton("setSize")->isHovered())
		{
			_modelResizingEnabled = true;

			// Add textfields and writefields
			_gui->getGlobalScreen()->addTextfield("modelSizeX", vec2(-0.3f, 0.1f), vec2(0.025f, 0.1f), "X", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelSizeY", vec2(0.0f, 0.1f), vec2(0.025f, 0.1f), "Y", vec3(1.0f));
			_gui->getGlobalScreen()->addTextfield("modelSizeZ", vec2(0.3f, 0.1f), vec2(0.025f, 0.1f), "Z", vec3(1.0f));
			_gui->getGlobalScreen()->addWriteField("modelSizeX", vec2(-0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addWriteField("modelSizeY", vec2(0.0f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1);
			_gui->getGlobalScreen()->addWriteField("modelSizeZ", vec2(0.3f, 0.0f), vec2(0.2f, 0.1f), vec3(0.25f), vec3(0.5f), vec3(1.0f), vec3(0.0f)), 0, 1, 1, 1;
			_gui->getGlobalScreen()->addButton("done", vec2(0.0f, -0.2f), vec2(0.15f, 0.1f), vec3(0.0f, 0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f), "Done", vec3(1.0f), vec3(0.0f));

			// Set default model size
			vec3 currentSize = _fe3d.gameEntity_getSize(_currentModelName);
			_gui->getGlobalScreen()->getWriteField("modelSizeX")->setTextContent(std::to_string(int(currentSize.x * 10.0f)));
			_gui->getGlobalScreen()->getWriteField("modelSizeY")->setTextContent(std::to_string(int(currentSize.y * 10.0f)));
			_gui->getGlobalScreen()->getWriteField("modelSizeZ")->setTextContent(std::to_string(int(currentSize.z * 10.0f)));

			// Set GUI focus
			_gui->setFocus(true);
		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("modelEditingMain");
		}
	}

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
				_gui->setFocus(false);
			}
		}
	}

	// Update changing model uv repeat through buttons
	if (_settingModelUvRepeat)
	{
		// Current UV repeat
		float newUvRepeat = _fe3d.gameEntity_getUvRepeat(_currentModelName);

		// Reading writefield
		if (_gui->getGlobalScreen()->getWriteField("uvRepeat")->getTextContent() != "")
		{
			newUvRepeat = float(stoi(_gui->getGlobalScreen()->getWriteField("uvRepeat")->getTextContent()));
		}

		// Set new model color
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
				_gui->setFocus(false);
			}
		}
	}

	// Update model resizing through cursor
	if (_fe3d.input_getKeyDown(Input::KEY_S))
	{
		float scrollSpeed = float(_fe3d.input_getMouseWheelY()) * 0.05f;
		_fe3d.gameEntity_setSize(_currentModelName, _fe3d.gameEntity_getSize(_currentModelName) * (1.0f + (scrollSpeed)));
	}

	// Update model resizing through buttons
	if (_modelResizingEnabled)
	{
		// Current model size
		vec3 newSize = _fe3d.gameEntity_getSize(_currentModelName);

		// X
		if (_gui->getGlobalScreen()->getWriteField("modelSizeX")->getTextContent() != "")
		{
			newSize.x = float(stoi(_gui->getGlobalScreen()->getWriteField("modelSizeX")->getTextContent())) / 10.0f;
		}

		// Y
		if (_gui->getGlobalScreen()->getWriteField("modelSizeY")->getTextContent() != "")
		{
			newSize.y = float(stoi(_gui->getGlobalScreen()->getWriteField("modelSizeY")->getTextContent())) / 10.0f;
		}

		// Z
		if (_gui->getGlobalScreen()->getWriteField("modelSizeZ")->getTextContent() != "")
		{
			newSize.z = float(stoi(_gui->getGlobalScreen()->getWriteField("modelSizeZ")->getTextContent())) / 10.0f;
		}

		// Set new model size
		_fe3d.gameEntity_setSize(_currentModelName, newSize);

		// Done button
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (_gui->getGlobalScreen()->getButton("done")->isHovered())
			{
				_modelResizingEnabled = false;
				_gui->getGlobalScreen()->deleteTextfield("modelSizeX");
				_gui->getGlobalScreen()->deleteWriteField("modelSizeX");
				_gui->getGlobalScreen()->deleteTextfield("modelSizeY");
				_gui->getGlobalScreen()->deleteWriteField("modelSizeY");
				_gui->getGlobalScreen()->deleteTextfield("modelSizeZ");
				_gui->getGlobalScreen()->deleteWriteField("modelSizeZ");
				_gui->getGlobalScreen()->deleteButton("done");
				_gui->setFocus(false);
			}
		}
	}
}