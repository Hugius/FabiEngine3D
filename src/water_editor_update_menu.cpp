#include "water_editor.hpp"

#include <algorithm>

void WaterEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			if(_fe3d->sky_getSelectedId().empty())
			{
				auto skyIds = _skyEditor->getLoadedSkyIds();

				for(auto & skyId : skyIds)
				{
					skyId = skyId.substr(1);
				}

				_gui->getOverlay()->openChoiceForm("selectSky", "Select Sky", CENTER_CHOICE_FORM_POSITION, skyIds);
			}
			else
			{
				_fe3d->sky_select("");
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createWater", "Create Water", "", VALUE_FORM_POSITION, 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto waterIds = _loadedWaterIds;

			for(auto & waterId : waterIds)
			{
				waterId = waterId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editWater", "Edit Water", LEFT_CHOICE_FORM_POSITION, waterIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto waterIds = _loadedWaterIds;

			for(auto & waterId : waterIds)
			{
				waterId = waterId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteWater", "Delete Water", LEFT_CHOICE_FORM_POSITION, waterIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveWatersToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}

		screen->getButton("sky")->setTextContent(_fe3d->sky_getSelectedId().empty() ? "Select Sky" : "Unselect Sky");
	}
}

void WaterEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuMain");

			_gui->getOverlay()->getTextField(WATER_TITLE_ID)->setVisible(false);

			_fe3d->water_setWireframed(_currentWaterId, false);
			_fe3d->water_select("");

			_currentWaterId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuLighting");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuMiscellaneous");
		}
	}
}