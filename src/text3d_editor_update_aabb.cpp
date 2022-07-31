#include "text3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include "tools.hpp"

void Text3dEditor::_updateAabbMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "text3dEditorMenuAabb")
	{
		const auto aabbId = ("text3d@" + _currentText3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->aabb_isExisting(aabbId))
			{
				_fe3d->aabb_setVisible(aabbId, false);
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_bindToParent(aabbId, _currentText3dId, AabbParentType::TEXT3D);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->aabb_delete(aabbId);
		}

		if(_fe3d->aabb_isExisting(aabbId))
		{
			_fe3d->aabb_setVisible(aabbId, true);
		}

		screen->getButton("create")->setHoverable(!_fe3d->aabb_isExisting(aabbId), true);
		screen->getButton("delete")->setHoverable(_fe3d->aabb_isExisting(aabbId), true);
	}
}