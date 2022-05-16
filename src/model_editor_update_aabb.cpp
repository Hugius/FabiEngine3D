#include "model_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void ModelEditor::_updateMainAabbMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createAabb", "Create AABB", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto modelIds = _fe3d->model_getChildAabbIds(_currentModelId);

			for(auto & modelId : modelIds)
			{
				modelId = modelId.substr((_currentModelId + "@").size());
			}

			sort(modelIds.begin(), modelIds.end());

			_gui->getOverlay()->openChoiceForm("editAabb", "Edit AABB", LEFT_CHOICE_FORM_POSITION, modelIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto modelIds = _fe3d->model_getChildAabbIds(_currentModelId);

			for(auto & modelId : modelIds)
			{
				modelId = modelId.substr((_currentModelId + "@").size());
			}

			sort(modelIds.begin(), modelIds.end());

			_gui->getOverlay()->openChoiceForm("deleteAabb", "Delete AABB", LEFT_CHOICE_FORM_POSITION, modelIds);
		}
	}
}

void ModelEditor::_updateChoiceAabbMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbChoice")
	{
		const auto position = _fe3d->aabb_getLocalPosition((_currentModelId + "@" + _currentAabbId));
		const auto size = _fe3d->aabb_getLocalSize((_currentModelId + "@" + _currentAabbId));

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->aabb_setVisible((_currentModelId + "@" + _currentAabbId), false);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");

			_gui->getOverlay()->getTextField(AABB_TITLE_ID)->setVisible(false);

			_currentAabbId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->openValueForm("positionX", "X", (position.x * POSITION_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("positionY", "Y", (position.y * POSITION_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("positionZ", "Z", (position.z * POSITION_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("sizeZ", "Z", (size.z * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), fvec3((value / POSITION_FACTOR), position.y, position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), fvec3(position.x, (value / POSITION_FACTOR), position.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), fvec3(position.x, position.y, (value / POSITION_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), fvec3((value / SIZE_FACTOR), size.y, size.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), fvec3(size.x, (value / SIZE_FACTOR), size.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), fvec3(size.x, size.y, (value / SIZE_FACTOR)));
		}
	}
}