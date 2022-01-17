#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateQuad3dMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuQuad3d")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3dPlace");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3dChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->deleteButtons();

			auto IDs = _fe3d->quad3d_getIDs();
			sort(IDs.begin(), IDs.end());
			for(auto& quadID : IDs)
			{
				if(quadID[0] != '@')
				{
					reverse(quadID.begin(), quadID.end());
					string rawID = quadID.substr(quadID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(quadID.begin(), quadID.end());

					_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->createButton(quadID, rawID);
				}
			}
		}
	}
}

void WorldEditor::_updateQuad3dPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuQuad3dPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateQuadID.empty())
			{
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), false);
				_fe3d->quad3d_setVisible(_currentTemplateQuadID, false);
				_currentTemplateQuadID = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& quadID : _quad3dEditor->getLoadedIDs())
			{
				if(_fe3d->quad3d_isExisting(quadID))
				{
					if(screen->getScrollingList("quad3dList")->getButton(quadID)->isHovered())
					{
						_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateQuad3d();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateReflection();

						_currentTemplateQuadID = quadID;
						_fe3d->quad3d_setPosition(_currentTemplateQuadID, fvec3(0.0f));
						_fe3d->quad3d_setVisible(_currentTemplateQuadID, true);
						_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadID")->getEntityID(), true);
						_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("quadID")->getEntityID(), "Quad3d: " + _currentTemplateQuadID.substr(1), 0.025f);
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

void WorldEditor::_updateQuad3dChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "worldEditorMenuQuad3dChoice")
	{
		for(const auto& button : _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->getButtons())
		{
			if(!_fe3d->quad3d_isExisting(button->getID()))
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->deleteButton(button->getID());
				break;
			}
		}

		for(const auto& quadID : _fe3d->quad3d_getIDs())
		{
			if(quadID[0] != '@')
			{
				if(screen->getScrollingList("quad3dList")->getButton(quadID)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateQuad3d(quadID);
					}
					else
					{
						_dontResetSelectedQuad3d = true;
						_selectQuad3d(quadID);
					}

					break;
				}
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
			return;
		}
	}
}