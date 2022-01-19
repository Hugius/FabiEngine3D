#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Text2dEditor::_updateMainMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "text2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("textCreate", "Create Text", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingText = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("textList", "Edit Text", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingText = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getLoadedIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui->getOverlay()->createChoiceForm("textList", "Delete Text", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingText = true;
			_isDeletingText = true;
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

void Text2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "text2dEditorMenuChoice")
	{
		auto color = _fe3d->text2d_getColor(_currentTextID);
		auto transparency = _fe3d->text2d_getTransparency(_currentTextID);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->text2d_setVisible(_currentTextID, false);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("textID")->getEntityID(), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("text2dEditorMenuMain");
			_currentTextID = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("fontMap")->isHovered())
		{
			if(_currentProjectID.empty())
			{
				Logger::throwError("Text2dEditor::_updateChoiceMenu");
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\image\\entity\\text2d\\font_map\\");

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

			if(filePath.size() > (rootPath.size() + targetDirectoryPath.size()) &&
			   filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
				return;
			}

			const string finalFilePath = filePath.substr(rootPath.size());
			_fe3d->misc_clearImageCache(finalFilePath);
			_fe3d->text2d_setFontMap(_currentTextID, finalFilePath);
			_fe3d->text2d_setContent(_currentTextID, TEXT_CONTENT);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->createValueForm("colorR", "R", (color.r * 255.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorG", "G", (color.g * 255.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("colorB", "B", (color.b * 255.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("transparency")->isHovered())
		{
			_gui->getOverlay()->createValueForm("transparency", "Transparency", (transparency * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("colorR", color.r, {}))
		{
			color.r /= 255.0f;
			_fe3d->text2d_setColor(_currentTextID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorG", color.g, {}))
		{
			color.g /= 255.0f;
			_fe3d->text2d_setColor(_currentTextID, color);
		}
		if(_gui->getOverlay()->checkValueForm("colorB", color.b, {}))
		{
			color.b /= 255.0f;
			_fe3d->text2d_setColor(_currentTextID, color);
		}
		if(_gui->getOverlay()->checkValueForm("transparency", transparency, {}))
		{
			transparency /= 100.0f;
			_fe3d->text2d_setTransparency(_currentTextID, transparency);
		}
	}
}