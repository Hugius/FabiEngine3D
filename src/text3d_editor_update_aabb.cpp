#include "text3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include "tools.hpp"

void Text3dEditor::_updateAabbMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuAabb")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->aabb_isExisting(_currentText3dId))
			{
				_fe3d->aabb_setVisible(_currentText3dId, false);
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_fe3d->aabb_create(_currentText3dId, false);
			_fe3d->aabb_setParentId(_currentText3dId, _currentText3dId);
			_fe3d->aabb_setParentType(_currentText3dId, AabbParentType::TEXT3D);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->aabb_delete(_currentText3dId);
		}

		if(_fe3d->aabb_isExisting(_currentText3dId))
		{
			_fe3d->aabb_setVisible(_currentText3dId, true);
		}

		screen->getButton("create")->setHoverable(!_fe3d->aabb_isExisting(_currentText3dId));
		screen->getButton("delete")->setHoverable(_fe3d->aabb_isExisting(_currentText3dId));
	}
}