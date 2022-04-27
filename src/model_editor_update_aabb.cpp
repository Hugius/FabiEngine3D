#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>
#include "tools.hpp"

void ModelEditor::_updateMainAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createAabb", "Create AABB", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _fe3d->model_getChildAabbIds(_currentModelId);

			for(auto & id : ids)
			{
				id = id.substr((_currentModelId + "@").size());
			}

			sort(ids.begin(), ids.end());

			_gui->getOverlay()->openChoiceForm("editAabb", "Edit AABB", fvec2(-0.5f, 0.1f), ids);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _fe3d->model_getChildAabbIds(_currentModelId);

			for(auto & id : ids)
			{
				id = id.substr((_currentModelId + "@").size());
			}

			sort(ids.begin(), ids.end());

			_gui->getOverlay()->openChoiceForm("deleteAabb", "Delete AABB", fvec2(-0.5f, 0.1f), ids);
		}
	}
}

void ModelEditor::_updateChoiceAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbChoice")
	{
		const auto position = _fe3d->aabb_getLocalPosition((_currentModelId + "@" + _currentAabbId));
		const auto size = _fe3d->aabb_getLocalSize((_currentModelId + "@" + _currentAabbId));

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->aabb_setVisible((_currentModelId + "@" + _currentAabbId), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
			_gui->getOverlay()->getTextField("aabbId")->setVisible(false);
			_currentAabbId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->openValueForm("positionX", "X", (position.x * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("positionY", "Y", (position.y * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("positionZ", "Z", (position.z * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
			_gui->getOverlay()->openValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.0f, 0.1f), 5, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), fvec3((content / 100.0f), position.y, position.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), fvec3(position.x, (content / 100.0f), position.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), fvec3(position.x, position.y, (content / 100.0f)));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), fvec3((content / 100.0f), size.y, size.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), fvec3(size.x, (content / 100.0f), size.z));
		}
		if((_gui->getOverlay()->getValueFormId() == "sizeZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), fvec3(size.x, size.y, (content / 100.0f)));
		}
	}
}

void ModelEditor::_updateAabbCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "aabbCreate") && _gui->getOverlay()->isValueFormConfirmed())
	{
		const auto newAabbId = _gui->getOverlay()->getValueFormContent();

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
		_gui->getOverlay()->getTextField("aabbId")->setVisible(true);
	}
}

void ModelEditor::_updateAabbChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editAabb") || (_gui->getOverlay()->getChoiceFormId() == "deleteAabb"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredAabbId.empty())
			{
				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), false);

				_hoveredAabbId = "";
			}
		}
		else
		{
			if(_hoveredAabbId.empty())
			{
				_hoveredAabbId = selectedOptionId;

				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentAabbId = _hoveredAabbId;
				_hoveredAabbId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteAabb")
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", "Yes", "No", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");

					_gui->getOverlay()->getTextField("aabbId")->setTextContent("AABB: " + _currentAabbId);
					_gui->getOverlay()->getTextField("aabbId")->setVisible(true);
				}
			}
		}
	}
}

void ModelEditor::_updateAabbDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteAabb") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->aabb_delete((_currentModelId + "@" + _currentAabbId));
			_currentAabbId = "";
		}
		if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentAabbId = "";
		}
	}
}