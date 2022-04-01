#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_updateMainAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("aabbCreate", "Create AABB", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAabb = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _fe3d->model_getChildAabbIds(_currentModelId);
			for(auto & id : ids)
			{
				id = id.substr((_currentModelId + "@").size());
			}
			sort(ids.begin(), ids.end());
			_gui->getOverlay()->createChoiceForm("aabbList", "Edit AABB", fvec2(-0.5f, 0.1f), ids);
			_isChoosingAabb = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _fe3d->model_getChildAabbIds(_currentModelId);
			for(auto & id : ids)
			{
				id = id.substr((_currentModelId + "@").size());
			}
			sort(ids.begin(), ids.end());
			_gui->getOverlay()->createChoiceForm("aabbList", "Delete AABB", fvec2(-0.5f, 0.1f), ids);
			_isChoosingAabb = true;
			_isDeletingAabb = true;
		}
	}
}

void ModelEditor::_updateChoiceAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbChoice")
	{
		auto position = _fe3d->aabb_getLocalPosition((_currentModelId + "@" + _currentAabbId));
		auto size = _fe3d->aabb_getLocalSize((_currentModelId + "@" + _currentAabbId));

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->aabb_setVisible((_currentModelId + "@" + _currentAabbId), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), false);
			_currentAabbId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->createValueForm("positionX", "X", (position.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionY", "Y", (position.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionZ", "Z", (position.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("positionX", position.x))
		{
			position.x /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), position);
		}
		if(_gui->getOverlay()->checkValueForm("positionY", position.y))
		{
			position.y /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), position);
		}
		if(_gui->getOverlay()->checkValueForm("positionZ", position.z))
		{
			position.z /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), position);
		}
		if(_gui->getOverlay()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), size);
		}
	}
}

void ModelEditor::_updateAabbCreating()
{
	if(_isCreatingAabb)
	{
		string newAabbId;

		if(_gui->getOverlay()->checkValueForm("aabbCreate", newAabbId, {}))
		{
			if(newAabbId.empty())
			{
				Logger::throwWarning("AABB ID cannot be empty");
				return;
			}

			if(any_of(newAabbId.begin(), newAabbId.end(), isspace))
			{
				Logger::throwWarning("AABB ID cannot contain any spaces");
				return;
			}

			if(!all_of(newAabbId.begin(), newAabbId.end(), isalnum))
			{
				Logger::throwWarning("AABB ID cannot contain any specials");
				return;
			}

			if(any_of(newAabbId.begin(), newAabbId.end(), isupper))
			{
				Logger::throwWarning("AABB ID cannot contain any capitals");
				return;
			}

			if(_fe3d->aabb_isExisting(_currentModelId + "@" + newAabbId))
			{
				Logger::throwWarning("AABB already exists");
				return;
			}

			_currentAabbId = newAabbId;

			_fe3d->aabb_create((_currentModelId + "@" + _currentAabbId), false);
			_fe3d->aabb_setVisible((_currentModelId + "@" + _currentAabbId), true);
			_fe3d->aabb_setParentId((_currentModelId + "@" + _currentAabbId), _currentModelId);
			_fe3d->aabb_setParentType((_currentModelId + "@" + _currentAabbId), AabbParentType::MODEL);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");
			_gui->getOverlay()->getTextField("aabbId")->setTextContent("AABB: " + _currentAabbId);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), true);

			_isCreatingAabb = false;
		}
	}
}

void ModelEditor::_updateAabbChoosing()
{
	if(_isChoosingAabb)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("aabbList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredAabbId.empty())
			{
				_hoveredAabbId = selectedButtonId;
				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAabbId = _hoveredAabbId;
				_hoveredAabbId = "";

				if(!_isDeletingAabb)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");

					_gui->getOverlay()->getTextField("aabbId")->setTextContent("AABB: " + _currentAabbId);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("aabbList");
				_isChoosingAabb = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("aabbList"))
		{
			_gui->getOverlay()->deleteChoiceForm("aabbList");
			_isChoosingAabb = false;
			_isDeletingAabb = false;
		}
		else
		{
			if(!_hoveredAabbId.empty())
			{
				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), false);
				_hoveredAabbId = "";
			}
		}
	}
}

void ModelEditor::_updateAabbDeleting()
{
	if(_isDeletingAabb && !_currentAabbId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->aabb_delete((_currentModelId + "@" + _currentAabbId));
			_isDeletingAabb = false;
			_currentAabbId = "";
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingAabb = false;
			_currentAabbId = "";
		}
	}
}