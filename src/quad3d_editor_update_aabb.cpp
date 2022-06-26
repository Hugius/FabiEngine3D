#include "quad3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include "tools.hpp"

void Quad3dEditor::_updateAabbMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuAabb")
	{
		const auto aabbId = ("quad3d@" + _currentQuad3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->aabb_isExisting(aabbId))
			{
				_fe3d->aabb_setVisible(aabbId, false);
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_fe3d->aabb_create(aabbId, false);
			_fe3d->aabb_setParentId(aabbId, _currentQuad3dId);
			_fe3d->aabb_setParentType(aabbId, AabbParentType::QUAD3D);
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