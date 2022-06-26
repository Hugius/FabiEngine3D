#include "model_editor.hpp"

void ModelEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("sky")->isHovered())
		{
			if(_fe3d->sky_getSelectedId().empty())
			{
				auto skyIds = _skyEditor->getLoadedSkyIds();

				for(auto & skyId : skyIds)
				{
					skyId = skyId.substr(1);
				}

				_gui->getOverlay()->openChoiceForm("selectSky", "Select Sky", CENTER_CHOICE_FORM_POSITION, skyIds);
			}
			else
			{
				_fe3d->sky_select("");
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createModel", "Create Model", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto modelIds = _loadedModelIds;

			for(auto & modelId : modelIds)
			{
				modelId = modelId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editModel", "Edit Model", LEFT_CHOICE_FORM_POSITION, modelIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto modelIds = _loadedModelIds;

			for(auto & modelId : modelIds)
			{
				modelId = modelId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteModel", "Delete Model", LEFT_CHOICE_FORM_POSITION, modelIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveModelsToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}

		screen->getButton("sky")->setTextContent(_fe3d->sky_getSelectedId().empty() ? "Select Sky" : "Unselect Sky");
	}
}

void ModelEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

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

			_gui->getOverlay()->getTextField(MODEL_TITLE_ID)->setVisible(false);

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

				_gui->getOverlay()->openChoiceForm("selectPart", "Select Part", LEFT_CHOICE_FORM_POSITION, partIds);
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

		screen->getButton("part")->setHoverable(_fe3d->model_isMultiParted(_currentModelId), true);
		screen->getButton("part")->setTextContent(_currentPartId.empty() ? "Select Part" : "Unselect Part");
	}
}