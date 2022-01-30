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
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("animationCreate", "Create Animation", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("animationList", "Edit Animation", fvec2(0.0f, 0.1f), getAnimationIds());
			_isChoosingAnimation = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("animationList", "Delete Animation", fvec2(0.0f, 0.1f), getAnimationIds());
			_isChoosingAnimation = true;
			_isDeletingAnimation = true;
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

void Animation2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation2dEditorMenuChoice")
	{
		auto currentAnimation = _getAnimation(_currentAnimationId);
		auto rowCount = currentAnimation->getRowCount();
		auto columnCount = currentAnimation->getColumnCount();
		auto interval = currentAnimation->getInterval();

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(isQuad3dAnimationStarted(_currentAnimationId, PREVIEW_QUAD_ID))
			{
				stopQuad3dAnimation(_currentAnimationId, PREVIEW_QUAD_ID);
			}

			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD_ID, false);

			_currentAnimationId = "";
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("animationId")->getEntityId(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuMain");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			_gui->getOverlay()->createAnswerForm("preview", "Quad3d Entity?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rowCount")->isHovered())
		{
			_gui->getOverlay()->createValueForm("rowCount", "Row Count", rowCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("columnCount")->isHovered())
		{
			_gui->getOverlay()->createValueForm("columnCount", "Column Count", columnCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->createValueForm("interval", "Interval", interval, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			startQuad3dAnimation(_currentAnimationId, PREVIEW_QUAD_ID, 1);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			stopQuad3dAnimation(_currentAnimationId, PREVIEW_QUAD_ID);
		}

		const auto isConfirmed = _gui->getOverlay()->isAnswerFormConfirmed("preview");
		const auto isDenied = _gui->getOverlay()->isAnswerFormDenied("preview");
		if(isConfirmed || isDenied)
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto entityType = (isConfirmed ? "quad3d" : "quad2d");
			const auto targetDirectoryPath = string("projects\\" + getCurrentProjectId() + "\\assets\\image\\entity\\" + entityType + "\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			const auto filePath = Tools::chooseExplorerFile(string(rootPath + targetDirectoryPath), "TGA");
			if(filePath.empty())
			{
				return;
			}

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) && filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD_ID, finalFilePath);
			currentAnimation->setPreviewTexturePath(finalFilePath);
		}

		if(_gui->getOverlay()->checkValueForm("rowCount", rowCount, {0}))
		{
			currentAnimation->setRowCount(rowCount);
		}
		if(_gui->getOverlay()->checkValueForm("columnCount", columnCount, {0}))
		{
			currentAnimation->setColumnCount(columnCount);
		}
		if(_gui->getOverlay()->checkValueForm("interval", interval, {}))
		{
			currentAnimation->setInterval(interval);
		}

		auto hasPreviewTexture = !currentAnimation->getPreviewTexturePath().empty();
		auto isStarted = isQuad3dAnimationStarted(_currentAnimationId, PREVIEW_QUAD_ID);
		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("rowCount")->setHoverable(hasPreviewTexture && !isStarted);
		screen->getButton("columnCount")->setHoverable(hasPreviewTexture && !isStarted);
		screen->getButton("interval")->setHoverable(hasPreviewTexture && !isStarted);
		screen->getButton("start")->setHoverable(hasPreviewTexture && !isStarted && (rowCount != 0) && (columnCount != 0));
		screen->getButton("stop")->setHoverable(hasPreviewTexture && isStarted);
	}
}