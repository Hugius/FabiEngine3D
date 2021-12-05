#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::_updateMiscellaneousMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "modelEditorMenuMiscellaneous")
	{
		// Temporary values
		auto levelOfDetailEntityID = _fe3d.model_getLevelOfDetailEntityID(_currentModelID);
		auto levelOfDetailDistance = _fe3d.model_getLevelOfDetailDistance(_currentModelID);
		auto isInstanced = _fe3d.model_isInstanced(_currentModelID);
		auto isFaceCulled = _fe3d.model_isFaceCulled(_currentModelID);
		auto rotationOrder = _fe3d.model_getRotationOrder(_currentModelID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("levelOfDetailEntityID")->isHovered())
		{
			levelOfDetailEntityID = (levelOfDetailEntityID.empty()) ? levelOfDetailEntityID : levelOfDetailEntityID.substr(1, levelOfDetailEntityID.size() - 1);
			_gui.getGlobalScreen()->createValueForm("levelOfDetailEntityID", "LOD Entity ID", levelOfDetailEntityID, fvec2(0.0f, 0.1f), fvec2(0.4f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("levelOfDetailDistance")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("levelOfDetailDistance", "Specular LOD Distance", levelOfDetailDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isInstanced")->isHovered())
		{
			isInstanced = !isInstanced;
			if(isInstanced)
			{
				_fe3d.model_enableInstancing(_currentModelID, {fvec3(0.0f)});
			}
			else
			{
				_fe3d.model_disableInstancing(_currentModelID);
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFaceCulled")->isHovered())
		{
			isFaceCulled = !isFaceCulled;
			_fe3d.model_setFaceCulled(_currentModelID, isFaceCulled);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrder")->isHovered())
		{
			if(rotationOrder == DirectionOrder::XYZ)
			{
				rotationOrder = DirectionOrder::XZY;
			}
			else if(rotationOrder == DirectionOrder::XZY)
			{
				rotationOrder = DirectionOrder::YXZ;
			}
			else if(rotationOrder == DirectionOrder::YXZ)
			{
				rotationOrder = DirectionOrder::YZX;
			}
			else if(rotationOrder == DirectionOrder::YZX)
			{
				rotationOrder = DirectionOrder::ZXY;
			}
			else if(rotationOrder == DirectionOrder::ZXY)
			{
				rotationOrder = DirectionOrder::ZYX;
			}
			else if(rotationOrder == DirectionOrder::ZYX)
			{
				rotationOrder = DirectionOrder::XYZ;
			}
			_fe3d.model_setRotationOrder(_currentModelID, rotationOrder);
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("levelOfDetailEntityID", levelOfDetailEntityID, {}))
		{
			if(levelOfDetailEntityID == "@") // No level of detail entity
			{
				_fe3d.model_setLevelOfDetailEntityID(_currentModelID, "");
			}
			else if(find(_loadedModelIDs.begin(), _loadedModelIDs.end(), ("@" + levelOfDetailEntityID)) == _loadedModelIDs.end()) // Check level of detail entity
			{
				Logger::throwWarning("Cannot find LOD entity with ID \"" + levelOfDetailEntityID + "\"");
			}
			else // Set level of detail entity
			{
				_fe3d.model_setLevelOfDetailEntityID(_currentModelID, ("@" + levelOfDetailEntityID));
			}
		}
		if (_gui.getGlobalScreen()->checkValueForm("levelOfDetailDistance", levelOfDetailDistance, {}))
		{
			_fe3d.model_setLevelOfDetailDistance(_currentModelID, levelOfDetailDistance);
		}

		// Update button text contents
		screen->getButton("isFaceCulled")->changeTextContent(isFaceCulled ? "Culling: ON" : "Culling: OFF");
		screen->getButton("isInstanced")->changeTextContent(isInstanced ? "Instanced: ON" : "Instanced: OFF");
		if(rotationOrder == DirectionOrder::XYZ)
		{
			screen->getButton("rotationOrder")->changeTextContent("Rotation: X Y Z");
		}
		else if(rotationOrder == DirectionOrder::XZY)
		{
			screen->getButton("rotationOrder")->changeTextContent("Rotation: X Z Y");
		}
		else if(rotationOrder == DirectionOrder::YXZ)
		{
			screen->getButton("rotationOrder")->changeTextContent("Rotation: Y X Z");
		}
		else if(rotationOrder == DirectionOrder::YZX)
		{
			screen->getButton("rotationOrder")->changeTextContent("Rotation: Y Z X");
		}
		else if(rotationOrder == DirectionOrder::ZXY)
		{
			screen->getButton("rotationOrder")->changeTextContent("Rotation: Z X Y");
		}
		else if(rotationOrder == DirectionOrder::ZYX)
		{
			screen->getButton("rotationOrder")->changeTextContent("Rotation: Z Y X");
		}
	}
}