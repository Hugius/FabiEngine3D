#include "world_editor.hpp"

#include <algorithm>

void WorldEditor::_updateReflectionMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuReflection")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_isPlacingReflection)
			{
				_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
				_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, false);
				_isPlacingReflection = false;
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");

			_deactivateModel();
			_deactivateQuad3d();
			_deactivateSound();
			_deactivatePointlight();
			_deactivateSpotlight();
			_deactivateReflection();

			_isPlacingReflection = true;
			_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, true);
			_fe3d->reflection_setVisible(TEMPLATE_CAMERA_ID, true);
			_fe3d->misc_centerCursor();

			if(_fe3d->terrain_getSelectedId().empty())
			{
				_fe3d->reflection_setPosition(TEMPLATE_CAMERA_ID, fvec3(0.0f));
				_gui->getOverlay()->createValueForm("positionX", "X", 0.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui->getOverlay()->createValueForm("positionY", "Y", 0.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
				_gui->getOverlay()->createValueForm("positionZ", "Z", 0.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuReflectionChoice");
			_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuReflectionChoice")->getScrollingList("reflectionList")->deleteButtons();

			auto Ids = _fe3d->reflection_getIds();
			sort(Ids.begin(), Ids.end());
			for(auto& reflectionId : Ids)
			{
				if(reflectionId[0] != '@')
				{
					reverse(reflectionId.begin(), reflectionId.end());
					string rawId = reflectionId.substr(reflectionId.find('_') + 1);
					reverse(rawId.begin(), rawId.end());
					reverse(reflectionId.begin(), reflectionId.end());

					_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuReflectionChoice")->getScrollingList("reflectionList")->createButton(reflectionId, rawId);
				}
			}
		}

		screen->getButton("choice")->setHoverable(!_isPlacingReflection);
	}
}

void WorldEditor::_updateReflectionChoosingMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuReflectionChoice")
	{
		for(const auto& button : screen->getScrollingList("reflectionList")->getButtons())
		{
			if(!_fe3d->reflection_isExisting(button->getId()))
			{
				screen->getScrollingList("reflectionList")->deleteButton(button->getId());
				break;
			}
		}

		for(const auto& reflectionId : _fe3d->reflection_getIds())
		{
			if(reflectionId[0] != '@')
			{
				if(screen->getScrollingList("reflectionList")->getButton(reflectionId)->isHovered())
				{
					if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateReflection(reflectionId);
					}
					else
					{
						_dontResetSelectedCamera = true;
						_selectReflection(reflectionId);
					}

					break;
				}
			}
		}

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuReflection");
			return;
		}
	}
}