#include "sprite_animation_editor.hpp"

void SpriteAnimationEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "billboardEditorMenuAnimation")
	{
		// Temporary values
		auto animationRowCount = _fe3d.billboard_getSpriteAnimationRowCount(_currentBillboardID);
		auto animationColumnCount = _fe3d.billboard_getSpriteAnimationColumnCount(_currentBillboardID);
		auto animationFramestep = _fe3d.billboard_getSpriteAnimationFramestep(_currentBillboardID);
		auto isPlaying = _fe3d.billboard_isSpriteAnimationPlaying(_currentBillboardID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animate")->isHovered())
		{
			_fe3d.billboard_startSpriteAnimation(_currentBillboardID, -1);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rows")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rows", "Rows", animationRowCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("columns")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("columns", "Columns", animationColumnCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("framestep")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("framestep", "Framestep", animationFramestep, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("rows", animationRowCount, {0}) ||
		   _gui.getGlobalScreen()->checkValueForm("columns", animationColumnCount, {0}) ||
		   _gui.getGlobalScreen()->checkValueForm("framestep", animationFramestep, {}))
		{
			// Only if animation is already playing
			if(isPlaying)
			{
				_fe3d.billboard_stopSpriteAnimation(_currentBillboardID);
				_fe3d.billboard_startSpriteAnimation(_currentBillboardID, -1);
			}
		}

		// Update buttons hoverability
		screen->getButton("animate")->setHoverable(!isPlaying && (animationRowCount != 0) && (animationColumnCount != 0));

		// Update animation values
		_fe3d.billboard_setSpriteAnimationRowCount(_currentBillboardID, animationRowCount);
		_fe3d.billboard_setSpriteAnimationColumnCount(_currentBillboardID, animationColumnCount);
		_fe3d.billboard_setSpriteAnimationFramestep(_currentBillboardID, animationFramestep);
	}
}