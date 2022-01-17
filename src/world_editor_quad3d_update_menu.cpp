#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateBillboardMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuBillboard")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuBillboardPlace");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuBillboardChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButtons();

			auto IDs = _fe3d->quad3d_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& quad3dID : IDs)
			{
				if(quad3dID[0] != '@')
				{
					reverse(quad3dID.begin(), quad3dID.end());
					string rawID = quad3dID.substr(quad3dID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(quad3dID.begin(), quad3dID.end());

					_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->createButton(quad3dID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateBillboardPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuBillboardPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateQuad3dID.empty())
			{
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), false);
				_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, false);
				_currentTemplateQuad3dID = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& quad3dID : _quad3dEditor->getLoadedIDs())
			{
				if(_fe3d->quad3d_isExisting(quad3dID))
				{
					if(screen->getScrollingList("billboardList")->getButton(quad3dID)->isHovered())
					{
						_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateBillboard();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateReflection();

						_currentTemplateQuad3dID = quad3dID;
						_fe3d->quad3d_setPosition(_currentTemplateQuad3dID, fvec3(0.0f));
						_fe3d->quad3d_setVisible(_currentTemplateQuad3dID, true);
						_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), true);
						_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quad3dID")->getEntityID(), "Billboard: " + _currentTemplateQuad3dID.substr(1), 0.025f);
						_fe3d->misc_centerCursor();

						if(_fe3d->terrain_getSelectedID().empty())
						{
							_gui->getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui->getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
							_gui->getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
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
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuBillboardChoice")
	{
		for(const auto& button : _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->getButtons())
		{
			if(!_fe3d->quad3d_isExisting(button->getID()))
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuBillboardChoice")->getScrollingList("billboardList")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& quad3dID : _fe3d->quad3d_getIDs())
		{
			if(quad3dID[0] != '@')
			{
				if(screen->getScrollingList("billboardList")->getButton(quad3dID)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateBillboard(quad3dID);
					}
					else
					{
						_dontResetSelectedBillboard = true;
						_selectBillboard(quad3dID);
					}

					break;
				}
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuBillboard");
			return;
		}
	}
}