#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::_updateMiscellaneousMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "modelEditorMenuMiscellaneous")
	{
		// Temporary values
		auto levelOfDetailEntityID = _fe3d.modelEntity_getLevelOfDetailEntityID(_currentModelID);
		auto isInstanced = _fe3d.modelEntity_isInstanced(_currentModelID);
		auto isFaceCulled = _fe3d.modelEntity_isFaceCulled(_currentModelID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lodEntityID")->isHovered())
		{
			levelOfDetailEntityID = (levelOfDetailEntityID.empty()) ? levelOfDetailEntityID : levelOfDetailEntityID.substr(1, levelOfDetailEntityID.size() - 1);
			_gui.getGlobalScreen()->createValueForm("lodEntityID", "LOD entity ID", levelOfDetailEntityID, Vec2(0.0f, 0.1f), Vec2(0.4f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isInstanced")->isHovered())
		{
			isInstanced = !isInstanced;
			if (isInstanced)
			{
				_fe3d.modelEntity_enableInstancing(_currentModelID, { Vec3(0.0f) });
			}
			else
			{
				_fe3d.modelEntity_disableInstancing(_currentModelID);
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFaceCulled")->isHovered())
		{
			isFaceCulled = !isFaceCulled;
			_fe3d.modelEntity_setFaceCulled(_currentModelID, isFaceCulled);
		}

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("lodEntityID", levelOfDetailEntityID, {}))
		{
			if (levelOfDetailEntityID == "@") // No LOD entity
			{
				_fe3d.modelEntity_setLevelOfDetailEntity(_currentModelID, "");
			}
			else if (find(_loadedModelIDs.begin(), _loadedModelIDs.end(), ("@" + levelOfDetailEntityID)) == _loadedModelIDs.end()) // Check LOD entity
			{
				Logger::throwWarning("Cannot find LOD entity with ID \"" + levelOfDetailEntityID + "\"");
			}
			else // Set LOD entity
			{
				_fe3d.modelEntity_setLevelOfDetailEntity(_currentModelID, ("@" + levelOfDetailEntityID));
			}
		}

		// Update button text contents
		screen->getButton("isFaceCulled")->changeTextContent(isFaceCulled ? "Culling: ON" : "Culling: OFF");
		screen->getButton("isInstanced")->changeTextContent(isInstanced ? "Instanced: ON" : "Instanced: OFF");
	}
}