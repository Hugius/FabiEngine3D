#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Animation2dEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "animation2dEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused())) // Back button
		{
			_gui.getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getOverlay()->createValueForm("animationCreate", "Create Animation", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAnimation = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui.getOverlay()->createChoiceForm("animationList", "Edit Animation", fvec2(0.0f, 0.1f), getAnimationIDs());
			_isChoosingAnimation = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui.getOverlay()->createChoiceForm("animationList", "Delete Animation", fvec2(0.0f, 0.1f), getAnimationIDs());
			_isChoosingAnimation = true;
			_isDeletingAnimation = true;
		}

		// Update answer forms
		if(_gui.getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveToFile();
			unload();
			return;
		}
		if(_gui.getOverlay()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void Animation2dEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "animation2dEditorMenuChoice")
	{
		// Temporary values
		auto currentAnimation = _getAnimation(_currentAnimationID);
		auto rowCount = currentAnimation->getRowCount();
		auto columnCount = currentAnimation->getColumnCount();
		auto framestep = currentAnimation->getFramestep();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getOverlay()->isFocused()))
		{
			// Stop animation if playing
			if(isBillboardAnimationStarted(_currentAnimationID, PREVIEW_BILLBOARD_ID))
			{
				stopBillboardAnimation(_currentAnimationID, PREVIEW_BILLBOARD_ID);
			}

			// Hide preview billboard
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setWireframed(PREVIEW_BILLBOARD_ID, false);
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);

			// Miscellaneous
			_currentAnimationID = "";
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("animationID")->getEntityID(), false);
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animation2dEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("Animation2dEditor::_updateChoiceMenu");
			}

			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\texture\\diffuse_map\\");

			// Validate target directory
			if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
				return;
			}

			// Validate chosen file
			const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "PNG");
			if(filePath.empty())
			{
				return;
			}

			// Validate directory of file
			if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			// Set diffuse map
			const string finalFilePath = filePath.substr(rootDirectoryPath.size());
			_fe3d.misc_clear2dTextureCache(finalFilePath);
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, finalFilePath);
			currentAnimation->setPreviewTexturePath(finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rows")->isHovered())
		{
			_gui.getOverlay()->createValueForm("rows", "Rows", rowCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("columns")->isHovered())
		{
			_gui.getOverlay()->createValueForm("columns", "Columns", columnCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("framestep")->isHovered())
		{
			_gui.getOverlay()->createValueForm("framestep", "Framestep", framestep, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			startBillboardAnimation(_currentAnimationID, PREVIEW_BILLBOARD_ID, 1);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			stopBillboardAnimation(_currentAnimationID, PREVIEW_BILLBOARD_ID);
		}

		// Update value forms
		if(_gui.getOverlay()->checkValueForm("rows", rowCount, {0}))
		{
			currentAnimation->setRowCount(rowCount);
		}
		if(_gui.getOverlay()->checkValueForm("columns", columnCount, {0}))
		{
			currentAnimation->setColumnCount(columnCount);
		}
		if(_gui.getOverlay()->checkValueForm("framestep", framestep, {}))
		{
			currentAnimation->setFramestep(framestep);
		}

		// Update buttons hoverability
		auto hasPreviewTexture = !currentAnimation->getPreviewTexturePath().empty();
		auto isStarted = isBillboardAnimationStarted(_currentAnimationID, PREVIEW_BILLBOARD_ID);
		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("rows")->setHoverable(hasPreviewTexture && !isStarted);
		screen->getButton("columns")->setHoverable(hasPreviewTexture && !isStarted);
		screen->getButton("framestep")->setHoverable(hasPreviewTexture && !isStarted);
		screen->getButton("start")->setHoverable(hasPreviewTexture && !isStarted && (rowCount != 0) && (columnCount != 0));
		screen->getButton("stop")->setHoverable(hasPreviewTexture && isStarted);
	}
}