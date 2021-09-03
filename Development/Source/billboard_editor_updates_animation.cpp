#include "billboard_editor.hpp"

void BillboardEditor::_updateAnimationMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "billboardEditorMenuAnimation")
	{
		// Temporary values
		auto animationRowCount = _fe3d.billboardEntity_getSpriteAnimationRows(_currentBillboardID);
		auto animationColumnCount = _fe3d.billboardEntity_getSpriteAnimationColumns(_currentBillboardID);
		auto animationFramestep = _fe3d.billboardEntity_getSpriteAnimationFramestep(_currentBillboardID);

		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
				return;
			}
			else if (screen->getButton("animate")->isHovered())
			{
				_fe3d.billboardEntity_startSpriteAnimation(_currentBillboardID, -1);
			}
			else if (screen->getButton("rows")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("rows", "Rows", animationRowCount, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("columns")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("columns", "Columns", animationColumnCount, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("speed", "Framestep", animationFramestep, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update buttons hoverability
		auto playing = _fe3d.billboardEntity_isSpriteAnimationStarted(_currentBillboardID);
		screen->getButton("animate")->setHoverable(!playing && animationRowCount != 0 && animationColumnCount != 0);

		// Update value forms
		if (_gui.getGlobalScreen()->checkValueForm("rows", animationRowCount, { 0 }) ||
			_gui.getGlobalScreen()->checkValueForm("columns", animationColumnCount, { 0 }) ||
			_gui.getGlobalScreen()->checkValueForm("speed", animationFramestep, {}))
		{
			// Only if animation is already playing
			if (playing)
			{
				_fe3d.billboardEntity_stopSpriteAnimation(_currentBillboardID);
				_fe3d.billboardEntity_startSpriteAnimation(_currentBillboardID, -1);
			}
		}

		// Update animation values
		_fe3d.billboardEntity_setSpriteAnimationRows(_currentBillboardID, animationRowCount);
		_fe3d.billboardEntity_setSpriteAnimationColumns(_currentBillboardID, animationColumnCount);
		_fe3d.billboardEntity_setSpriteAnimationFramestep(_currentBillboardID, animationFramestep);
	}
}