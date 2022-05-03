#include "model_editor.hpp"

void ModelEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createModel", "Create Model", "", fvec2(0.0f, 0.1f), 10, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto modelIds = _loadedModelIds;

			for(auto & modelId : modelIds)
			{
				modelId = modelId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editModel", "Edit Model", fvec2(-0.5f, 0.1f), modelIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto modelIds = _loadedModelIds;

			for(auto & modelId : modelIds)
			{
				modelId = modelId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteModel", "Delete Model", fvec2(-0.5f, 0.1f), modelIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveModelsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void ModelEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			for(const auto & partId : _fe3d->model_getPartIds(_currentModelId))
			{
				_fe3d->model_setWireframed(_currentModelId, partId, false);
			}

			if(!_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_currentModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}

			_fe3d->model_setVisible(_currentModelId, false);
			_gui->getOverlay()->getTextField("modelId")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuMain");
			_currentModelId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartId.empty())
			{
				auto partIds = _fe3d->model_getPartIds(_currentModelId);
				sort(partIds.begin(), partIds.end());
				_gui->getOverlay()->openChoiceForm("selectPart", "Select Part", fvec2(-0.5f, 0.1f), partIds);
			}
			else
			{
				_fe3d->model_setOpacity(_currentModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuLighting");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuMiscellaneous");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("aabb")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
		}

		screen->getButton("part")->setHoverable(_fe3d->model_isMultiParted(_currentModelId));

		screen->getButton("part")->setTextContent(_currentPartId.empty() ? "Select Part" : "Unselect Part");
	}
}