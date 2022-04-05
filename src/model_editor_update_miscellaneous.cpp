#include "model_editor.hpp"
#include "logger.hpp"

void ModelEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuMiscellaneous")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || !_currentPartId.empty());
		const auto isNoPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || _currentPartId.empty());

		auto size = (isNoPartSelected ? _fe3d->model_getBaseSize(_currentModelId) : fvec3(0.0f));
		auto opacity = (isPartSelected ? _fe3d->model_getOpacity(_currentModelId, _currentPartId) : 0.0f);
		auto minTextureAlpha = (isPartSelected ? _fe3d->model_getMinTextureAlpha(_currentModelId, _currentPartId) : 0.0f);
		auto isFaceCulled = (isPartSelected ? _fe3d->model_isFaceCulled(_currentModelId, _currentPartId) : false);
		auto levelOfDetailEntityId = (isNoPartSelected ? _fe3d->model_getLevelOfDetailEntityId(_currentModelId) : "");
		auto levelOfDetailDistance = (isNoPartSelected ? _fe3d->model_getLevelOfDetailDistance(_currentModelId) : 0.0f);
		auto rotationOrder = (isNoPartSelected ? _fe3d->model_getRotationOrder(_currentModelId) : DirectionOrder::XYZ);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.25f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.25f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			if(_currentPartId.empty())
			{
				_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			}
			else
			{
				_gui->getOverlay()->openValueForm("opacity", "Opacity", (_originalPartOpacity * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("minTextureAlpha")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minTextureAlpha", "Min Texture Alpha", (minTextureAlpha * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("isFaceCulled")->isHovered())
		{
			isFaceCulled = !isFaceCulled;
			_fe3d->model_setFaceCulled(_currentModelId, _currentPartId, isFaceCulled);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("levelOfDetailEntityId")->isHovered())
		{
			levelOfDetailEntityId = (levelOfDetailEntityId.empty()) ? levelOfDetailEntityId : levelOfDetailEntityId.substr(1, levelOfDetailEntityId.size() - 1);
			_gui->getOverlay()->openValueForm("levelOfDetailEntityId", "LOD Entity ID", levelOfDetailEntityId, fvec2(0.0f, 0.1f), 5, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("levelOfDetailDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("levelOfDetailDistance", "LOD Distance", levelOfDetailDistance, fvec2(0.0f, 0.1f), 5, false, true, false);
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
			_fe3d->model_setRotationOrder(_currentModelId, rotationOrder);
		}

		//if(_gui->getOverlay()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d->model_setBaseSize(_currentModelId, size);
		}
		//if(_gui->getOverlay()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d->model_setBaseSize(_currentModelId, size);
		}
		//if(_gui->getOverlay()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d->model_setBaseSize(_currentModelId, size);
		}
		//if(_gui->getOverlay()->checkValueForm("opacity", opacity))
		{
			opacity /= 100.0f;

			if(_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_currentModelId, _currentPartId, opacity);
			}
			else
			{
				_originalPartOpacity = opacity;
			}
		}
		//if(_gui->getOverlay()->checkValueForm("minTextureAlpha", minTextureAlpha))
		{
			minTextureAlpha /= 100.0f;
			_fe3d->model_setMinTextureAlpha(_currentModelId, _currentPartId, minTextureAlpha);
		}
		//if(_gui->getOverlay()->checkValueForm("levelOfDetailEntityId", levelOfDetailEntityId, {}))
		{
			if(levelOfDetailEntityId.empty())
			{
				_fe3d->model_setLevelOfDetailEntityId(_currentModelId, "");
			}
			else if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), ("@" + levelOfDetailEntityId)) == _loadedEntityIds.end())
			{
				Logger::throwWarning("LOD entity does not exist");
			}
			else
			{
				_fe3d->model_setLevelOfDetailEntityId(_currentModelId, ("@" + levelOfDetailEntityId));
			}
		}
		//if(_gui->getOverlay()->checkValueForm("levelOfDetailDistance", levelOfDetailDistance, {}))
		{
			_fe3d->model_setLevelOfDetailDistance(_currentModelId, levelOfDetailDistance);
		}

		screen->getButton("size")->setHoverable(isNoPartSelected);
		screen->getButton("opacity")->setHoverable(isPartSelected);
		screen->getButton("minTextureAlpha")->setHoverable(isPartSelected);
		screen->getButton("isFaceCulled")->setHoverable(isPartSelected);
		screen->getButton("levelOfDetailEntityId")->setHoverable(isNoPartSelected);
		screen->getButton("levelOfDetailDistance")->setHoverable(isNoPartSelected);
		screen->getButton("rotationOrder")->setHoverable(isNoPartSelected);

		screen->getButton("isFaceCulled")->setTextContent(isFaceCulled ? "Culling: ON" : "Culling: OFF");
		if(rotationOrder == DirectionOrder::XYZ)
		{
			screen->getButton("rotationOrder")->setTextContent("Rotation: X Y Z");
		}
		else if(rotationOrder == DirectionOrder::XZY)
		{
			screen->getButton("rotationOrder")->setTextContent("Rotation: X Z Y");
		}
		else if(rotationOrder == DirectionOrder::YXZ)
		{
			screen->getButton("rotationOrder")->setTextContent("Rotation: Y X Z");
		}
		else if(rotationOrder == DirectionOrder::YZX)
		{
			screen->getButton("rotationOrder")->setTextContent("Rotation: Y Z X");
		}
		else if(rotationOrder == DirectionOrder::ZXY)
		{
			screen->getButton("rotationOrder")->setTextContent("Rotation: Z X Y");
		}
		else if(rotationOrder == DirectionOrder::ZYX)
		{
			screen->getButton("rotationOrder")->setTextContent("Rotation: Z Y X");
		}
	}
}