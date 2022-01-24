#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateText3dMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3d")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateTextId.empty())
			{
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), false);
				_fe3d->text3d_setVisible(_currentTemplateTextId, false);
				_currentTemplateTextId = "";
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3dPlace");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3dChoice");

			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("text3dList")->deleteButtons();

			auto Ids = _fe3d->text3d_getIds();
			sort(Ids.begin(), Ids.end());
			for(auto& textId : Ids)
			{
				if(textId[0] != '@')
				{
					reverse(textId.begin(), textId.end());
					string rawId = textId.substr(textId.find('_') + 1);
					reverse(rawId.begin(), rawId.end());
					reverse(textId.begin(), textId.end());

					_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("text3dList")->createButton(textId, rawId);
				}
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateTextId.empty());
	}
}

void WorldEditor::_updateText3dPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& textId : _text3dEditor->getLoadedIds())
			{
				if(_fe3d->text3d_isExisting(textId))
				{
					if(screen->getScrollingList("text3dList")->getButton(textId)->isHovered())
					{
						_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateText3d();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateReflection();

						_currentTemplateTextId = textId;
						_fe3d->text3d_setVisible(_currentTemplateTextId, true);
						_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textId")->getEntityId(), true);
						_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("textId")->getEntityId(), "Text3d: " + _currentTemplateTextId.substr(1), 0.025f);
						_fe3d->misc_centerCursor();

						if(_fe3d->terrain_getSelectedId().empty())
						{
							_fe3d->text3d_setPosition(_currentTemplateTextId, fvec3(0.0f));
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

void WorldEditor::_updateText3dChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuText3dChoice")
	{
		for(const auto& button : _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("text3dList")->getButtons())
		{
			if(!_fe3d->text3d_isExisting(button->getId()))
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dChoice")->getScrollingList("text3dList")->deleteButton(button->getId());
				break;
			}
		}

		for(const auto& textId : _fe3d->text3d_getIds())
		{
			if(textId[0] != '@')
			{
				if(screen->getScrollingList("text3dList")->getButton(textId)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateText3d(textId);
					}
					else
					{
						_dontResetSelectedText3d = true;
						_selectText3d(textId);
					}

					break;
				}
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuText3d");
			return;
		}
	}
}