#include "sprite_animation_editor.hpp"

void SpriteAnimationEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "spriteAnimationEditorMenuChoice")
	{
		// Temporary values
		auto currentAnimation = _getAnimation(_currentAnimationID);
		auto rowCount = currentAnimation->getRowCount();
		auto columnCount = currentAnimation->getColumnCount();
		auto framestep = currentAnimation->getFramestep();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{

		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rows")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rows", "Rows", rowCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("columns")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("columns", "Columns", columnCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("framestep")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("framestep", "Framestep", framestep, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{

		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{

		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("rows", rowCount, {0}))
		{
			currentAnimation->setRowCount(rowCount);
		}
		if(_gui.getGlobalScreen()->checkValueForm("columns", columnCount, {0}))
		{
			currentAnimation->setColumnCount(columnCount);
		}
		if(_gui.getGlobalScreen()->checkValueForm("framestep", framestep, {}))
		{
			currentAnimation->setFramestep(framestep);
		}

		// Update buttons hoverability
		screen->getButton("preview")->setHoverable(!currentAnimation->isStarted());
		screen->getButton("rows")->setHoverable(!currentAnimation->isStarted());
		screen->getButton("columns")->setHoverable(!currentAnimation->isStarted());
		screen->getButton("framestep")->setHoverable(!currentAnimation->isStarted());
		screen->getButton("start")->setHoverable(!currentAnimation->isStarted());
		screen->getButton("stop")->setHoverable(currentAnimation->isStarted());
	}
}