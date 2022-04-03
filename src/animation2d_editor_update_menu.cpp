#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Animation2dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("animationCreate", "Create Animation", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto ids = _loadedAnimationIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("animationList", "Edit Animation", fvec2(0.0f, 0.1f), ids);
			_isChoosingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto ids = _loadedAnimationIds;
			for(auto & id : ids)
			{
				id = id.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("animationList", "Delete Animation", fvec2(0.0f, 0.1f), ids);
			_isChoosingAnimation = true;
			_isDeletingAnimation = true;
		}

		if(_gui->getOverlay()->isAnswerFormAccepted("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveAnimationsToFile();
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

void Animation2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation2dEditorMenuChoice")
	{
		auto rowCount = _fe3d->animation2d_getRowCount(_currentAnimationId);
		auto columnCount = _fe3d->animation2d_getColumnCount(_currentAnimationId);
		auto interval = _fe3d->animation2d_getInterval(_currentAnimationId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->quad3d_isAnimationStarted(PREVIEW_QUAD_ID, _currentAnimationId))
			{
				_fe3d->quad3d_stopAnimation(PREVIEW_QUAD_ID, _currentAnimationId);
			}

			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, false);

			_currentAnimationId = "";
			_isPreviewTextureChosen = false;
			_gui->getOverlay()->getTextField("animationId")->setVisible(false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("preview", "Quad3D Entity?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rowCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rowCount", "Row Count", rowCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("columnCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("columnCount", "Column Count", columnCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->openValueForm("interval", "Interval", interval, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			_fe3d->quad3d_startAnimation(PREVIEW_QUAD_ID, _currentAnimationId, 1);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->quad3d_stopAnimation(PREVIEW_QUAD_ID, _currentAnimationId);
		}

		const auto isConfirmed = _gui->getOverlay()->isAnswerFormAccepted("preview");
		const auto isDenied = _gui->getOverlay()->isAnswerFormDenied("preview");
		if(isConfirmed || isDenied)
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto entityType = (isConfirmed ? "quad3d" : "quad2d");
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\" + entityType + "\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, finalFilePath);
			_isPreviewTextureChosen = true;
		}

		if(_gui->getOverlay()->checkValueForm("rowCount", rowCount, {0}))
		{
			_fe3d->animation2d_setRowCount(_currentAnimationId, rowCount);
		}
		if(_gui->getOverlay()->checkValueForm("columnCount", columnCount, {0}))
		{
			_fe3d->animation2d_setColumnCount(_currentAnimationId, columnCount);
		}
		if(_gui->getOverlay()->checkValueForm("interval", interval, {}))
		{
			_fe3d->animation2d_setInterval(_currentAnimationId, interval);
		}

		const auto isStarted = _fe3d->quad3d_isAnimationStarted(PREVIEW_QUAD_ID, _currentAnimationId);

		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("rowCount")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("columnCount")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("interval")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("start")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("stop")->setHoverable(_isPreviewTextureChosen && isStarted);
	}
}