#include "sprite_animation_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SpriteAnimationEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "spriteAnimationEditorMenuChoice")
	{
		// Temporary values
		auto currentAnimation = _getAnimation(_currentAnimationID);
		auto rowCount = currentAnimation->getRowCount();
		auto columnCount = currentAnimation->getColumnCount();
		auto framestep = currentAnimation->getFramestep();

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, "");
			_fe3d.billboard_setVisible(PREVIEW_BILLBOARD_ID, false);
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			// Get the chosen file name
			const auto rootDirectoryPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\textures\\diffuse_maps\\");

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
			_fe3d.misc_clearTextureCache2D(finalFilePath);
			_fe3d.billboard_setDiffuseMap(PREVIEW_BILLBOARD_ID, finalFilePath);
			currentAnimation->setPreviewTexturePath(finalFilePath);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rows")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rows", "Rows", rowCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("columns")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("columns", "Columns", columnCount, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("framestep")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("framestep", "Framestep", framestep, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			startAnimation(_currentAnimationID, PREVIEW_BILLBOARD_ID, 1);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			stopAnimation(_currentAnimationID, PREVIEW_BILLBOARD_ID);
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("rows", rowCount, {0}))
		{
			currentAnimation->setRowCount(rowCount);
		}
		if(_gui.getGlobalScreen()->checkValueForm("columns", columnCount, {0}))
		{
			currentAnimation->setColumnCount(columnCount);
		}
		if(_gui.getGlobalScreen()->checkValueForm("framestep", framestep, {}))
		{
			currentAnimation->setFramestep(framestep);
		}

		// Update buttons hoverability
		auto hasPreviewTexture = !currentAnimation->getPreviewTexturePath().empty();
		auto isPlaying = isAnimationStarted(_currentAnimationID, PREVIEW_BILLBOARD_ID);
		screen->getButton("preview")->setHoverable(!isPlaying);
		screen->getButton("rows")->setHoverable(hasPreviewTexture && !isPlaying);
		screen->getButton("columns")->setHoverable(hasPreviewTexture && !isPlaying);
		screen->getButton("framestep")->setHoverable(hasPreviewTexture && !isPlaying);
		screen->getButton("start")->setHoverable(hasPreviewTexture && !isPlaying && (rowCount != 0) && (columnCount != 0));
		screen->getButton("stop")->setHoverable(hasPreviewTexture && isPlaying);
	}
}