#include "model_editor.hpp"

void ModelEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "modelEditorMenuMain")
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
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Edit Model", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingModel = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("modelList", "Delete Model", fvec2(-0.5f, 0.1f), IDs);
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

	if(screen->getID() == "modelEditorMenuChoice")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			for(const auto& partID : _fe3d->model_getPartIDs(_currentModelID))
			{
				_fe3d->model_setWireframed(_currentModelID, partID, false);
			}

			for(const auto& partID : _fe3d->model_getPartIDs(_currentModelID))
			{
				_fe3d->model_setTransparency(_currentModelID, partID, 1.0f);
			}

			_fe3d->model_setVisible(_currentModelID, false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuMain");
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("modelID")->getEntityID(), false);
			_fe3d->text_setVisible(_gui->getOverlay()->getTextField("partID")->getEntityID(), false);
			_currentModelID = "";
			_currentPartID = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("part")->isHovered())
		{
			if(_currentPartID.empty())
			{
				auto IDs = _fe3d->model_getPartIDs(_currentModelID);
				sort(IDs.begin(), IDs.end());
				_gui->getOverlay()->createChoiceForm("partList", "Select Part", fvec2(-0.5f, 0.1f), IDs);
				_isChoosingPart = true;
			}
			else
			{
				_fe3d->model_setTransparency(_currentModelID, _currentPartID, 1.0f);
				_fe3d->text_setVisible(_gui->getOverlay()->getTextField("partID")->getEntityID(), false);
				_currentPartID = "";
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
			_fe3d->misc_enableAabbFrameRendering();
		}

		screen->getButton("part")->setHoverable(_fe3d->model_isMultiParted(_currentModelID));

		screen->getButton("part")->changeTextContent(_currentPartID.empty() ? "Select Part" : "Unselect Part");
	}
}