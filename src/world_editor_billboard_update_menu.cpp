#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateBillboardMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuBillboard")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboardPlace");
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboardChoice");

			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButtons();

			auto IDs = _fe3d.billboard_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& billboardID : IDs)
			{
				if(billboardID[0] != '@')
				{
					reverse(billboardID.begin(), billboardID.end());
					string rawID = billboardID.substr(billboardID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(billboardID.begin(), billboardID.end());

					_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->createButton(billboardID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateBillboardPlacingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuBillboardPlace")
	{
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			if(!_currentTemplateBillboardID.empty())
			{
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), false);
				_fe3d.billboard_setVisible(_currentTemplateBillboardID, false);
				_currentTemplateBillboardID = "";
			}

			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& billboardID : _billboardEditor.getLoadedIDs())
			{
				if(_fe3d.billboard_isExisting(billboardID))
				{
					if(screen->getScrollingList("billboardList")->getButton(billboardID)->isHovered())
					{
						_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateBillboard();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateReflection();

						_currentTemplateBillboardID = billboardID;
						_fe3d.billboard_setPosition(_currentTemplateBillboardID, fvec3(0.0f));
						_fe3d.billboard_setVisible(_currentTemplateBillboardID, true);
						_fe3d.text_setVisible(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), true);
						_fe3d.text_setContent(_gui.getOverlay()->getTextField("billboardID")->getEntityID(), "Billboard: " + _currentTemplateBillboardID.substr(1), 0.025f);
						_fe3d.misc_centerCursor();

						if(_fe3d.terrain_getSelectedID().empty())
						{
							_gui.getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui.getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
						}

						break;
					}
				}
			}
		}
	}
}

void WorldEditor::_updateBillboardChoosingMenu()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuBillboardChoice")
	{
		for(const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->getButtons())
		{
			if(!_fe3d.billboard_isExisting(button->getID()))
			{
				_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& billboardID : _fe3d.billboard_getIDs())
		{
			if(billboardID[0] != '@')
			{
				if(screen->getScrollingList("billboardList")->getButton(billboardID)->isHovered())
				{
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateBillboard(billboardID);
					}
					else
					{
						_dontResetSelectedBillboard = true;
						_selectBillboard(billboardID);
					}

					break;
				}
			}
		}

		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
			return;
		}
	}
}