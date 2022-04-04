#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("textCreate", "Create Text", "", fvec2(0.0f, 0.1f), 10, true, true, false);
			_isCreatingText = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("textList", "Edit Text", fvec2(-0.5f, 0.1f), ids);
			_isChoosingText = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedEntityIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->openChoiceForm("textList", "Delete Text", fvec2(-0.5f, 0.1f), ids);
			_isChoosingText = true;
			_isDeletingText = true;
		}

		if(_gui->getOverlay()->getAnswerFormId() == "back")
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				saveEntitiesToFile();
				unload();


			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
				unload();


			}
		}
	}
}

void Text2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text2dEditorMenuChoice")
	{
		auto color = _fe3d->text2d_getColor(_currentTextId);
		auto opacity = _fe3d->text2d_getOpacity(_currentTextId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->text2d_setVisible(_currentTextId, false);
			_gui->getOverlay()->getTextField("textId")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuMain");
			_currentTextId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			//_gui->getOverlay()->openValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			//_gui->getOverlay()->openValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			//_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		//if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->text2d_setColor(_currentTextId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->text2d_setColor(_currentTextId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->text2d_setColor(_currentTextId, color);
		}
		//if(_gui->getOverlay()->checkValueForm("opacity", opacity, {}))
		{
			opacity /= 100.0f;
			_fe3d->text2d_setOpacity(_currentTextId, opacity);
		}
	}
}