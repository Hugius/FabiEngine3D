#include "world_editor.hpp"

void WorldEditor::_updateSkyMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuSky")
	{
		if((_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> skyIds;

			for(const auto & id : _skyEditor->getLoadedEntityIds())
			{
				if(id[0] == '@')
				{
					skyIds.push_back(id.substr(1));
				}
			}

			_gui->getOverlay()->openChoiceForm("selectSky", "Select Sky", fvec2(0.0f, 0.1f), skyIds);
		}
		else if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->sky_delete(_fe3d->sky_getSelectedId());
		}

		if((_gui->getOverlay()->getChoiceFormId() == "selectSky") && _gui->getOverlay()->isChoiceFormConfirmed())
		{
			const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

			_worldHelper->copyTemplateSky(selectedOptionId, ("@" + selectedOptionId));

			_fe3d->sky_select(selectedOptionId);
		}

		screen->getButton("choose")->setHoverable(_fe3d->sky_getSelectedId().empty());
		screen->getButton("delete")->setHoverable(!_fe3d->sky_getSelectedId().empty());
	}
}