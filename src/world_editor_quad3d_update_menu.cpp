#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateQuad3dMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuQuad3d")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentTemplateQuadId.empty())
			{
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), false);
				_fe3d->quad3d_setVisible(_currentTemplateQuadId, false);
				_currentTemplateQuadId = "";
			}

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

			for(auto& [key, templateId] : _loadedQuadIds)
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->createButton(key, key);
			}
		}

		screen->getButton("choice")->setHoverable(_currentTemplateQuadId.empty());
	}
}

void WorldEditor::_updateQuad3dPlacingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuQuad3dPlace")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			for(const auto& quadId : _quad3dEditor->getLoadedIds())
			{
				if(_fe3d->quad3d_isExisting(quadId))
				{
					if(screen->getScrollingList("quad3dList")->getButton(quadId)->isHovered())
					{
						_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

						_deactivateModel();
						_deactivateQuad3d();
						_deactivateSound();
						_deactivatePointlight();
						_deactivateReflection();

						_currentTemplateQuadId = quadId;
						_fe3d->quad3d_setVisible(_currentTemplateQuadId, true);
						_gui->getOverlay()->getTextField("quadId")->changeTextContent("Quad3D: " + _currentTemplateQuadId.substr(1));
						_fe3d->misc_centerCursor();

						if(_fe3d->terrain_getSelectedId().empty())
						{
							_fe3d->quad3d_setPosition(_currentTemplateQuadId, fvec3(0.0f));
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

	if(screen->getId() == "worldEditorMenuQuad3dChoice")
	{
		for(const auto& button : _gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->getButtons())
		{
			if(!_fe3d->quad3d_isExisting(button->getId()))
			{
				_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dChoice")->getScrollingList("quad3dList")->deleteButton(button->getId());
				break;
			}
		}

		for(auto& [key, templateId] : _loadedQuadIds)
		{
			if(screen->getScrollingList("quad3dList")->getButton(key)->isHovered())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					_deactivateModel();
					_deactivateQuad3d();
					_deactivateSound();
					_deactivatePointlight();
					_deactivateSpotlight();
					_deactivateReflection();

					_activateQuad3d(key);
				}
				else
				{
					_selectQuad3d(key);

					_dontResetSelectedQuad3d = true;
				}

				break;
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuQuad3d");
			return;
		}
	}
}