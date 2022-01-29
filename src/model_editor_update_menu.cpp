#include "model_editor.hpp"

void ModelEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("modelCreate", "Create Model", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingModel = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto Ids = getLoadedIds();
			for(auto& id : Ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Edit Model", fvec2(-0.5f, 0.1f), Ids);
			_isChoosingModel = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto Ids = getLoadedIds();
			for(auto& id : Ids)
			{
				id = id.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Delete Model", fvec2(-0.5f, 0.1f), Ids);
			_isChoosingModel = true;
			_isDeletingModel = true;
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void ModelEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			for(const auto& partId : _fe3d->model_getPartIds(_currentModelId))
			{
				_fe3d->model_setWireframed(_currentModelId, partId, false);
			}

			if(!_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_currentModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}

			_fe3d->model_setVisible(_currentModelId, false);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("modelId")->getEntityId(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuMain");
			_currentModelId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartId.empty())
			{
				auto Ids = _fe3d->model_getPartIds(_currentModelId);
				sort(Ids.begin(), Ids.end());
				_gui->getOverlay()->createChoiceForm("partList", "Select Part", fvec2(-0.5f, 0.1f), Ids);
				_isChoosingPart = true;
			}
			else
			{
				_fe3d->model_setOpacity(_currentModelId, _currentPartId, _originalPartOpacity);
				_currentPartId = "";
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("texturing")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuTexturing");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lighting")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuLighting");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("miscellaneous")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuMiscellaneous");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("aabb")->isHovered())
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
		}

		screen->getButton("part")->setHoverable(_fe3d->model_isMultiParted(_currentModelId));

		screen->getButton("part")->changeTextContent(_currentPartId.empty() ? "Select Part" : "Unselect Part");
	}
}