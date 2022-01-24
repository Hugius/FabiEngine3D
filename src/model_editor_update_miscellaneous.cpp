#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "modelEditorMenuMiscellaneous")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelID) || !_currentPartID.empty());
		const auto isNoPartSelected = (!_fe3d->model_isMultiParted(_currentModelID) || _currentPartID.empty());

		auto size = (isNoPartSelected ? _fe3d->model_getBaseSize(_currentModelID) : fvec3(0.0f));
		auto opacity = (isPartSelected ? _fe3d->model_getOpacity(_currentModelID, _currentPartID) : 0.0f);
		auto isFaceCulled = (isPartSelected ? _fe3d->model_isFaceCulled(_currentModelID, _currentPartID) : false);
		auto levelOfDetailEntityID = (isNoPartSelected ? _fe3d->model_getLevelOfDetailEntityID(_currentModelID) : "");
		auto levelOfDetailDistance = (isNoPartSelected ? _fe3d->model_getLevelOfDetailDistance(_currentModelID) : 0.0f);
		auto rotationOrder = (isNoPartSelected ? _fe3d->model_getRotationOrder(_currentModelID) : DirectionOrder::XYZ);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			if(_currentPartID.empty())
			{
				_gui->getOverlay()->createValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
			else
			{
				_gui->getOverlay()->createValueForm("opacity", "Opacity", (_originalPartOpacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFaceCulled")->isHovered())
		{
			isFaceCulled = !isFaceCulled;
			_fe3d->model_setFaceCulled(_currentModelID, _currentPartID, isFaceCulled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("levelOfDetailEntityID")->isHovered())
		{
			levelOfDetailEntityID = (levelOfDetailEntityID.empty()) ? levelOfDetailEntityID : levelOfDetailEntityID.substr(1, levelOfDetailEntityID.size() - 1);
			_gui->getOverlay()->createValueForm("levelOfDetailEntityID", "LOD Entity ID", levelOfDetailEntityID, fvec2(0.0f, 0.1f), fvec2(0.4f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("levelOfDetailDistance")->isHovered())
		{
			_gui->getOverlay()->createValueForm("levelOfDetailDistance", "Specular LOD Distance", levelOfDetailDistance, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotationOrder")->isHovered())
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
			_fe3d->model_setRotationOrder(_currentModelID, rotationOrder);
		}

		if(_gui->getOverlay()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d->model_setBaseSize(_currentModelID, size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d->model_setBaseSize(_currentModelID, size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d->model_setBaseSize(_currentModelID, size);
		}
		if(_gui->getOverlay()->checkValueForm("opacity", opacity))
		{
			opacity /= 100.0f;

			if(_currentPartID.empty())
			{
				_fe3d->model_setOpacity(_currentModelID, _currentPartID, opacity);
			}
			else
			{
				_originalPartOpacity = opacity;
			}
		}
		if(_gui->getOverlay()->checkValueForm("levelOfDetailEntityID", levelOfDetailEntityID, {}))
		{
			if(levelOfDetailEntityID == "@")
			{
				_fe3d->model_setLevelOfDetailEntityID(_currentModelID, "");
			}
			else if(find(_loadedModelIDs.begin(), _loadedModelIDs.end(), ("@" + levelOfDetailEntityID)) == _loadedModelIDs.end())
			{
				Logger::throwWarning("Cannot find LOD entity with ID \"" + levelOfDetailEntityID + "\"");
			}
			else
			{
				_fe3d->model_setLevelOfDetailEntityID(_currentModelID, ("@" + levelOfDetailEntityID));
			}
		}
		if(_gui->getOverlay()->checkValueForm("levelOfDetailDistance", levelOfDetailDistance, {}))
		{
			_fe3d->model_setLevelOfDetailDistance(_currentModelID, levelOfDetailDistance);
		}

		screen->getButton("size")->setHoverable(isNoPartSelected);
		screen->getButton("opacity")->setHoverable(isPartSelected);
		screen->getButton("isFaceCulled")->setHoverable(isPartSelected);
		screen->getButton("levelOfDetailEntityID")->setHoverable(isNoPartSelected);
		screen->getButton("levelOfDetailDistance")->setHoverable(isNoPartSelected);
		screen->getButton("rotationOrder")->setHoverable(isNoPartSelected);

		screen->getButton("isFaceCulled")->changeTextContent(isFaceCulled ? "Culling: ON" : "Culling: OFF");
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