#include "water_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void WaterEditor::_updateMainMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "waterEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getOverlay()->createValueForm("waterCreate", "Create Water", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingWater = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getOverlay()->createChoiceForm("waterList", "Edit Water", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingWater = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getOverlay()->createChoiceForm("waterList", "Delete Water", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingWater = true;
			_isDeletingWater = true;
		}

		// Update answer forms
		if(_gui.getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void WaterEditor::_updateChoiceMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "waterEditorMenuChoice")
	{
		// Temporary values
		float size = _fe3d.water_getSize(_currentWaterID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("waterID")->getEntityID(), false);
			_fe3d.water_setWireframed(_currentWaterID, false);
			_fe3d.water_select("");
			_currentWaterID = "";
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui.getOverlay()->createValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuTexturing");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuLighting");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMiscellaneous");
		}

		// Update value forms
		if(_gui.getOverlay()->checkValueForm("size", size, {0.0f}))
		{
			_fe3d.water_setSize(_currentWaterID, size);
		}

		// Update buttons hoverability
		screen->getButton("lighting")->setHoverable(_fe3d.water_isExisting(_currentWaterID));
		screen->getButton("miscellaneous")->setHoverable(_fe3d.water_isExisting(_currentWaterID));
	}
}