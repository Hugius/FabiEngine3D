#include "quad3d_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include "tools.hpp"

void Quad3dEditor::_updateAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuAabb")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->aabb_isExisting(_currentQuadId))
			{
				_fe3d->aabb_setVisible(_currentQuadId, false);
			}

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_fe3d->aabb_create(_currentQuadId, false);
			_fe3d->aabb_setParentId(_currentQuadId, _currentQuadId);
			_fe3d->aabb_setParentType(_currentQuadId, AabbParentType::QUAD3D);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->aabb_delete(_currentQuadId);
		}

		if(_fe3d->aabb_isExisting(_currentQuadId))
		{
			_fe3d->aabb_setVisible(_currentQuadId, true);
		}

		screen->getButton("create")->setHoverable(!_fe3d->aabb_isExisting(_currentQuadId));
		screen->getButton("delete")->setHoverable(_fe3d->aabb_isExisting(_currentQuadId));
	}
}