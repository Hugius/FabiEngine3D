#include "text3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include "tools.hpp"

void Text3dEditor::_updateAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuAabb")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->aabb_isExisting(_currentTextId))
			{
				_fe3d->aabb_setVisible(_currentTextId, false);
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_fe3d->aabb_create(_currentTextId, false);
			_fe3d->aabb_setParentId(_currentTextId, _currentTextId);
			_fe3d->aabb_setParentType(_currentTextId, AabbParentType::TEXT);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->aabb_delete(_currentTextId);
		}

		if(_fe3d->aabb_isExisting(_currentTextId))
		{
			_fe3d->aabb_setVisible(_currentTextId, true);
		}

		screen->getButton("create")->setHoverable(!_fe3d->aabb_isExisting(_currentTextId));
		screen->getButton("delete")->setHoverable(_fe3d->aabb_isExisting(_currentTextId));
	}
}