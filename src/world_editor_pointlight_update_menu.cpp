#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updatePointlightMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuPointlight")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			if(_isPlacingPointlight)
			{
				_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
				_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);
				_isPlacingPointlight = false;
			}

			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateBillboard();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			_isPlacingPointlight = true;
			_fe3d.model_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d.pointlight_setPosition(TEMPLATE_LAMP_ID, fvec3(0.0f));
			_fe3d.misc_centerCursor();

			if(_fe3d.terrain_getSelectedID().empty())
			{
				_gui.getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui.getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui.getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuPointlightChoice");

			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlights")->deleteButtons();

			auto IDs = _fe3d.pointlight_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& pointlightID : IDs)
			{
				if(pointlightID[0] != '@')
				{
					reverse(pointlightID.begin(), pointlightID.end());
					string rawID = pointlightID.substr(pointlightID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(pointlightID.begin(), pointlightID.end());

					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuPointlightChoice")->getScrollingList("pointlights")->createButton(pointlightID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updatePointlightChoosingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuPointlightChoice")
	{
		for(const auto& button : screen->getScrollingList("pointlights")->getButtons())
		{
			if(!_fe3d.pointlight_isExisting(button->getID()))
			{
				screen->getScrollingList("pointlights")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& pointlightID : _fe3d.pointlight_getIDs())
		{
			if(pointlightID[0] != '@')
			{
				if(screen->getScrollingList("pointlights")->getButton(pointlightID)->isHovered())
				{
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activatePointlight(pointlightID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedLamp = true;
						_selectPointlight(pointlightID);
					}

					break;
				}
			}
		}

		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuPointlight");
				return;
			}
		}
	}
}