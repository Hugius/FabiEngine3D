#include <algorithm>

#include "model_editor.hpp"

void ModelEditor::_updateModelEditingSize()
{
	auto screen = _window->getScreen("modelEditingSize");

	// GUI management
	if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
	{
		if (screen->getButton("setSize")->isHovered())
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
		else if (screen->getButton("toggleResizeMesh")->isHovered())
		{
			_meshResizingToggled = !_meshResizingToggled;
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResizeMesh")->getTextfield()->getEntityID(), 
				_meshResizingToggled ? "Mesh resize: ON" : "Mesh resize: OFF");
		}
		else if (screen->getButton("toggleBoxView")->isHovered())
		{
			static bool frameRendering = false;
			frameRendering = !frameRendering;

			// Toggle
			frameRendering ? _fe3d.collision_enableFrameRendering() : _fe3d.collision_disableFrameRendering();
			_fe3d.textEntity_setTextContent(screen->getButton("toggleBoxView")->getTextfield()->getEntityID(),
				frameRendering ? "Hitbox: ON" : "Hitbox: OFF");
		}
		else if (screen->getButton("toggleResizeBox")->isHovered())
		{
			_boxResizingToggled = !_boxResizingToggled;
			_fe3d.textEntity_setTextContent(screen->getButton("toggleResizeBox")->getTextfield()->getEntityID(),
				_boxResizingToggled ? "Box resize: ON" : "Box resize: OFF");
		}
		else if (screen->getButton("back")->isHovered())
		{
			_window->setActiveScreen("modelEditingMain");
		}
	}

	// Update model resizing through cursor
	if (_meshResizingToggled)
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